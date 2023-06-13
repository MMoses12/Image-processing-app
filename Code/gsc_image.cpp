#include "gsc_image.hpp"
#include <cmath>

using namespace std;

// Default constructor for greyscaled image.
GSCImage::GSCImage () {
    width = 0;
    height = 0;
    max_luminocity = 0;
    pixels = nullptr;
}

// Copy constructor.
GSCImage::GSCImage (const GSCImage& img) {
    int pos, row, col;
    GSCPixel *imgPixel;
    
    // Set image characteristics.
    setWidth(img.getWidth());
    setHeight(img.getHeight());
    setMaxLuminocity(img.getMaxLuminocity());

    // Make a new heap array for the new copy.
    pixels = new (nothrow) GSCPixel* [img.getHeight()];

    for (pos = 0; pos < img.getHeight(); pos ++) {
        pixels[pos] = new (nothrow) GSCPixel [img.getWidth()];
    }

    // Copy the values of the original array.
    for (row = 0; row < img.getHeight(); row ++) {
        for (col = 0; col < img.getWidth(); col ++) {
            imgPixel = (GSCPixel* ) &img.getPixel(row, col);
            (pixels[row][col]).setValue(imgPixel->getValue());
        }
    }
}

// Constructor from rgb image to greyscaled.
GSCImage::GSCImage (const RGBImage& greyscaled) {
    int pos, row, col;
    RGBPixel *imgPixel;

    // Set image characteristics.
    setWidth(greyscaled.getWidth());
    setHeight(greyscaled.getHeight());
    setMaxLuminocity(greyscaled.getMaxLuminocity());

    // Make a new heap array.
    pixels = new (nothrow) GSCPixel* [greyscaled.getHeight()];

    for (pos = 0; pos < greyscaled.getHeight(); pos ++) {
        pixels[pos] = new (nothrow) GSCPixel [greyscaled.getWidth()];
    }

    // Calculate the value of each pixel for the new greyscaled image.
    for (row = 0; row < greyscaled.getHeight(); row ++) {
        for (col = 0; col < greyscaled.getWidth(); col ++) {
            imgPixel = (RGBPixel* ) &greyscaled.getPixel(row, col);
            (pixels[row][col]).setValue(imgPixel->getRed() * 0.3 + imgPixel->getGreen() * 0.59 + imgPixel->getBlue() * 0.11);
        }
    }
}

// Constructor using reading stream to get the pixels array.
GSCImage::GSCImage (std::istream& stream) {
    int height, width, max_lum, row, col, val;

    // Read the image characteristics.
    stream >> width;
    setWidth(width);

    stream >> height;
    setHeight(height);

    stream >> max_lum;
    setMaxLuminocity(max_lum);

    // Make the heap pixels array.
    this->pixels = new (nothrow) GSCPixel* [getHeight()];

    for (row = 0; row < getHeight(); row ++) {
        this->pixels[row] = new (nothrow) GSCPixel [getWidth()];
    }

    // Set the value for each pixel.
    for (row = 0; row < getHeight(); row ++) {
        for (col = 0; col < getWidth(); col ++) {
            stream >> val;
            this->pixels[row][col].setValue(val);
        }
    }
}

// Destructor of a GSCImage object.
GSCImage::~GSCImage () {
    int pos;
    
    // Delete each column.
    if (pixels != NULL) {
        for (pos = 0; pos < getHeight(); pos ++) {
            delete[] pixels[pos];
        }

        delete[] pixels;
    }

    this->pixels = nullptr;
}

// Copy the object into another object.
GSCImage& GSCImage::operator = (const GSCImage& img) {
    int pos, row, col;
    GSCPixel *imgPixel;
    
    // If pixels array is not null delete it to
    // make the new one with the same height and
    // width as the other one.
    if (pixels != NULL) {
        for (pos = 0; pos < getHeight(); pos ++) {
            delete[] this->pixels[pos];
        }

        delete[] this->pixels;
    }

    // Set image characteristics.
    setWidth(img.getWidth());
    setHeight(img.getHeight());
    setMaxLuminocity(img.getMaxLuminocity());

    // Make a new heap array for the copied object.
    this->pixels = new (nothrow) GSCPixel* [img.getHeight()];
    
    for (pos = 0; pos < img.getHeight(); pos ++) {
        this->pixels[pos] = new (nothrow) GSCPixel [img.getWidth()];
    }

    // Copy the values of the img array.
    for (row = 0; row < img.getHeight(); row ++) {
        for (col = 0; col < img.getWidth(); col ++) {
            imgPixel = (GSCPixel* ) &img.getPixel(row, col);
            (this->pixels[row][col]).setValue((int) imgPixel->getValue());
        }
    }

    return (*this);
}

// Rotate image by int times.
Image& GSCImage::operator += (int times) {
    int rotations, pos, row, col, newRow = 0, newCol = 0;
    GSCImage rotatedImg, img2;
    GSCPixel *imgPixel;

    // Calculate how many times the image will be rotated (with max of three).
    rotations = times % 4;

    // If the rotations are odd the image will change width and height.
    if (abs(rotations) == 1 || abs(rotations) == 3) {
        rotatedImg.pixels = new (nothrow) GSCPixel* [getWidth()];

        for (pos = 0; pos < getWidth(); pos ++) {
            rotatedImg.pixels[pos] = new (nothrow) GSCPixel [getHeight()];
        }
        // Set the characteristics.
        rotatedImg.setHeight(getWidth());
        rotatedImg.setWidth(getHeight());
        rotatedImg.setMaxLuminocity(getMaxLuminocity());
    }
    else if (abs(rotations) == 2) {
        rotatedImg.pixels = new (nothrow) GSCPixel* [getHeight()];

        for (pos = 0; pos < getHeight(); pos ++) {
            rotatedImg.pixels[pos] = new (nothrow) GSCPixel [getWidth()];
        }
        // Set the characteristics.
        rotatedImg.setHeight(getHeight());
        rotatedImg.setWidth(getWidth());
        rotatedImg.setMaxLuminocity(getMaxLuminocity());
    }

    // One clockwise rotation or three counter clockwise.
    if (rotations == 1 || rotations == -3) {
        for (col = 0; col < getWidth(); col ++) {
            for (row = getHeight() - 1; row >= 0; row --) {
                imgPixel = (GSCPixel* ) &getPixel(row, col);
                (rotatedImg.pixels[newRow][newCol]).setValue(imgPixel->getValue());

                newCol ++;
                if (newCol == rotatedImg.getWidth()) {
                    newRow ++;
                    newCol = 0;
                }
            }
        }
    }
    // Two clockwise or counter clockwise rotations.
    else if (rotations == 2 || rotations == -2) {
        for (row = 0; row < getHeight(); row ++) {
            for (col = 0; col < getWidth(); col ++) {
                imgPixel = (GSCPixel* ) &getPixel(row, col);
                (rotatedImg.pixels[getHeight()-1-row][getWidth()-1-col]).setValue(imgPixel->getValue());
            }
        }
    }
    // Three clockwise or one counter clockwise rotations.
    else if (rotations == 3 || rotations == -1) {
        newRow = 0;
        newCol = 0;
        
        for (col = getWidth()-1; col >= 0; col --) {
            for (row = 0; row < getHeight(); row ++) {
                imgPixel = (GSCPixel* ) &getPixel(row, col);
                (rotatedImg.pixels[newRow][newCol]).setValue(imgPixel->getValue());

                newCol ++;
                if (newCol == rotatedImg.getWidth()) {
                    newRow ++;
                    newCol = 0;
                }
            }
        }
    }

    *this = rotatedImg;

    return (*this);
}

// Scale the image by factor.
Image& GSCImage::operator *= (double factor) {
    GSCImage scaledImg;
    GSCPixel *P11, *P12, *P21, *P22;
    int r1, r2, c1, c2, row , col, sum, avg, newHeight, newWidth;

    // Get the new width and height.
    scaledImg.setHeight((int ) getHeight()*factor);
    scaledImg.setWidth((int) getWidth()*factor);
    scaledImg.setMaxLuminocity((int) getMaxLuminocity());

    newHeight = getHeight()*factor;
    newWidth = getWidth()*factor;

    scaledImg.pixels = new GSCPixel* [newHeight];

    for (row = 0; row < scaledImg.getHeight(); row ++) {
        scaledImg.pixels[row] = new GSCPixel [newWidth];
    }

    // Calculate the new pixels.
    for (row = 0; row < scaledImg.getHeight(); row ++) {
        for (col = 0; col < scaledImg.getWidth(); col ++) {
            r1 = (int) min (floor(row/factor), (double) getHeight()-1);
            r2 = (int) min (ceil(row/factor), (double) getHeight()-1);
            c1 = (int) min (floor(col/factor), (double) getWidth()-1);
            c2 = (int) min (ceil(col/factor), (double) getWidth()-1);

            P11 = (GSCPixel* ) &getPixel(r1, c1);
            P12 = (GSCPixel* ) &getPixel(r1, c2);
            P21 = (GSCPixel* ) &getPixel(r2, c1);
            P22 = (GSCPixel* ) &getPixel(r2, c2);

            sum = P11->getValue() + P12->getValue() + P21->getValue() + P22->getValue();
            avg = sum / 4;

            scaledImg.pixels[row][col].setValue(avg);
        }
    }
    
    *this = scaledImg;

    return (*this);
}

// Color inversion of the image.
Image& GSCImage::operator ! () {    
    int row, col, maxLum;
    GSCPixel* imgPixel;

    maxLum = getMaxLuminocity();

    for (row = 0; row < getHeight(); row ++) {
        for (col = 0; col < getWidth(); col ++) {
            imgPixel = (GSCPixel* ) &getPixel(row, col);
            imgPixel->setValue(maxLum - imgPixel->getValue());
        }
    }
    
    return (*this);
}

// Histogram equalization of the image.
Image& GSCImage::operator ~ () {
    double *histogram = new double [getMaxLuminocity() + 1];
    int *histogramInt = new int [getMaxLuminocity() + 1];
	int pos, row , col, C, D, E;
	GSCPixel* imgPixel;

    // Make the histogram array.
	for (pos = 0; pos < getMaxLuminocity() + 1; pos ++) {
		histogram[pos] = 0;
	}

	// Calculate the histogram.
	for (row = 0; row < getHeight(); row ++) {
		for (col = 0; col < getWidth(); col ++) {
			imgPixel = (GSCPixel* ) &getPixel(row, col);
			histogram[imgPixel->getValue()] ++;
		}
	}
    
	// Calculate probability distribution.
	for (pos = 0; pos < getMaxLuminocity() + 1; pos  ++) {
		histogram[pos] /= getWidth() * getHeight();
	}

	// Calculate total probability distribution.
	for (pos = 1; pos < getMaxLuminocity() + 1; pos ++) {
		histogram[pos] += histogram[pos-1];
	}

    for (pos = 0; pos < getMaxLuminocity(); pos ++) {
        histogram[pos] *= 235;
        histogramInt[pos] = histogram[pos];
    }

    for (row = 0; row < getHeight(); row ++) {
        for (col = 0; col < getWidth(); col ++) {
            imgPixel = (GSCPixel* ) &getPixel(row, col);
            imgPixel->setValue(histogramInt[imgPixel->getValue()]);
        }
    }

    delete[] histogram;
    delete[] histogramInt;

    return (*this);
}

// Mirror the image.
Image& GSCImage::operator * () {
	int row, col;
    GSCImage newImg;
    GSCPixel* imgPixel;

    // Make the new image object.
    newImg.setHeight(getHeight());
    newImg.setWidth(getWidth());
    newImg.setMaxLuminocity(getMaxLuminocity());

    newImg.pixels = new GSCPixel* [getHeight()];
    
    for (row = 0; row < getHeight(); row ++) {
        newImg.pixels[row] = new GSCPixel [getWidth()];
    }

    // Mirror the pixels.
    for (row = 0; row < getHeight(); row ++) {
        for (col = 0; col < getWidth(); col ++) {
            imgPixel = (GSCPixel* ) &getPixel(row, col);
            (newImg.pixels[row][getWidth() - col - 1]).setValue(imgPixel->getValue());
        }
    }

    *this = newImg;

    return (*this);
} 

// Get a specific pixel from the image.
Pixel& GSCImage::getPixel (int row, int col) const {
    return (pixels[row][col]);
}
