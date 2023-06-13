#include "rgb_image.hpp"
#include <cmath>

using namespace std;

// Default constructor for a rgb image.
RGBImage::RGBImage () {
	pixels = nullptr;
}

// Copy constructor.
RGBImage::RGBImage (const RGBImage& img) {
	int pos, row, col;
	RGBPixel* imgPixel;

	// Make a new heap array for the copy object.
	pixels = new (nothrow) RGBPixel* [img.getHeight()];

	for (pos = 0; pos < img.getHeight(); pos ++) {
		pixels[pos] = new (nothrow) RGBPixel [img.getWidth()];
	}

	// Copy each pixel value from the original to the copied object.
	for (row = 0; row < img.getHeight(); row ++) {
		for (col = 0; col < img.getWidth(); col ++) {
			imgPixel = (RGBPixel* ) &img.getPixel(row, col);
			(pixels[row][col]).setRed(imgPixel->getRed());
			(pixels[row][col]).setGreen(imgPixel->getGreen());
			(pixels[row][col]).setBlue(imgPixel->getBlue());
		}
	}
}

// Constructor using reading stream to get the pixels array.
RGBImage::RGBImage (std::istream& stream) {
    int height, width, max_lum, row, col, red, green, blue;

    // Read the image characteristics.
    stream >> width;
    setWidth(width);

    stream >> height;
    setHeight(height);

    stream >> max_lum;
    setMaxLuminocity(max_lum);

    // Make the heap pixels array.
    this->pixels = new (nothrow) RGBPixel* [getHeight()];

    for (row = 0; row < getHeight(); row ++) {
        this->pixels[row] = new (nothrow) RGBPixel [getWidth()];
    }

    // Set the value for each pixel.
    for (row = 0; row < getHeight(); row ++) {
        for (col = 0; col < getWidth(); col ++) {
            stream >> red;
			stream >> green;
			stream >> blue;
            this->pixels[row][col].setRed(red);
			this->pixels[row][col].setGreen(green);
			this->pixels[row][col].setBlue(blue);
        }
    }
}


// Destructor of a RGBImage object.
RGBImage::~RGBImage () {
    int pos;

    if (pixels != NULL) {
        for (pos = 0; pos < getHeight(); pos ++) {
            delete[] pixels[pos];
        }

        delete[] pixels;
    }

    this->pixels = nullptr;
}

// Copy the object into another object.
RGBImage& RGBImage::operator = (const RGBImage& img) {
    int pos, row, col;
    RGBPixel *imgPixel;
    
    if (pixels != NULL) {
        for (pos = 0; pos < getHeight(); pos ++) {
            delete[] pixels[pos];
        }

        delete[] pixels;
    }

    // Set image characteristics.
    setWidth(img.getWidth());
    setHeight(img.getHeight());
    setMaxLuminocity(img.getMaxLuminocity());

   	// Make a new heap array for the copied object.
	this->pixels = new (nothrow) RGBPixel* [img.getHeight()];

	for (pos = 0; pos < img.getHeight(); pos ++) {
		this->pixels[pos] = new (nothrow) RGBPixel [img.getWidth()];
	}

	// Copy each pixel value from the img object to the copied object.
	for (row = 0; row < img.getHeight(); row ++) {
		for (col = 0; col < img.getWidth(); col ++) {
			imgPixel = (RGBPixel* ) &img.getPixel(row, col);
			(this->pixels[row][col]).setRed(imgPixel->getRed());
			(this->pixels[row][col]).setGreen(imgPixel->getGreen());
			(this->pixels[row][col]).setBlue(imgPixel->getBlue());
		}
	}

    return (*this);
}

// Rotate image by int times.
Image& RGBImage::operator += (int times) {
    int rotations, pos, row, col, newRow = 0, newCol = 0;
    RGBImage rotatedImg, img2;
    RGBPixel *imgPixel;

    // Calculate how many times the image will be rotated (with max of three).
    rotations = times % 4;

    // If the rotations are odd the image will change width and height.
    if (abs(rotations) == 1 || abs(rotations) == 3) {
        rotatedImg.pixels = new (nothrow) RGBPixel* [getWidth()];

        for (pos = 0; pos < getWidth(); pos ++) {
            rotatedImg.pixels[pos] = new (nothrow) RGBPixel [getHeight()];
        }
        // Set the characteristics.
        rotatedImg.setHeight(getWidth());
        rotatedImg.setWidth(getHeight());
        rotatedImg.setMaxLuminocity(getMaxLuminocity());
    }
    else if (abs(rotations) == 2) {
        rotatedImg.pixels = new (nothrow) RGBPixel* [getHeight()];

        for (pos = 0; pos < getHeight(); pos ++) {
            rotatedImg.pixels[pos] = new (nothrow) RGBPixel [getWidth()];
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
                imgPixel = (RGBPixel* ) &getPixel(row, col);
                (rotatedImg.pixels[newRow][newCol]).setRed(imgPixel->getRed());
                (rotatedImg.pixels[newRow][newCol]).setGreen(imgPixel->getGreen());
                (rotatedImg.pixels[newRow][newCol]).setBlue(imgPixel->getBlue());

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
                imgPixel = (RGBPixel* ) &getPixel(row, col);
                (rotatedImg.pixels[getHeight()-1-row][getWidth()-1-col]).setRed(imgPixel->getRed());
                (rotatedImg.pixels[getHeight()-1-row][getWidth()-1-col]).setGreen(imgPixel->getGreen());
                (rotatedImg.pixels[getHeight()-1-row][getWidth()-1-col]).setBlue(imgPixel->getBlue());
            }
        }
    }
    // Three clockwise or one counter clockwise rotations.
    else if (rotations == 3 || rotations == -1) {
        newRow = 0;
        newCol = 0;
        
        for (col = getWidth()-1; col >= 0; col --) {
            for (row = 0; row < getHeight(); row ++) {
                imgPixel = (RGBPixel* ) &getPixel(row, col);
                (rotatedImg.pixels[newRow][newCol]).setRed(imgPixel->getRed());
                (rotatedImg.pixels[newRow][newCol]).setGreen(imgPixel->getGreen());
                (rotatedImg.pixels[newRow][newCol]).setBlue(imgPixel->getBlue());

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
Image& RGBImage::operator *= (double factor) {
    RGBImage scaledImg;
    RGBPixel *P11, *P12, *P21, *P22;
    int r1, r2, c1, c2, row , col, sum, avg, newHeight, newWidth;

    scaledImg.setHeight((int ) getHeight()*factor);
    scaledImg.setWidth((int) getWidth()*factor);
    scaledImg.setMaxLuminocity((int) getMaxLuminocity());

    newHeight = getHeight()*factor;
    newWidth = getWidth()*factor;

    scaledImg.pixels = new RGBPixel* [newHeight];

    for (row = 0; row < scaledImg.getHeight(); row ++) {
        scaledImg.pixels[row] = new RGBPixel [newWidth];
    }

    // Calculate the new pixels.
    for (row = 0; row < scaledImg.getHeight(); row ++) {
        for (col = 0; col < scaledImg.getWidth(); col ++) {
            r1 = (int) min (floor(row/factor), (double) getHeight()-1);
            r2 = (int) min (ceil(row/factor), (double) getHeight()-1);
            c1 = (int) min (floor(col/factor), (double) getWidth()-1);
            c2 = (int) min (ceil(col/factor), (double) getWidth()-1);

            P11 = (RGBPixel* ) &getPixel(r1, c1);
            P12 = (RGBPixel* ) &getPixel(r1, c2);
            P21 = (RGBPixel* ) &getPixel(r2, c1);
            P22 = (RGBPixel* ) &getPixel(r2, c2);

            sum = P11->getRed() + P12->getRed() + P21->getRed() + P22->getRed();
            avg = sum / 4;
            scaledImg.pixels[row][col].setRed(avg);
            
            sum = P11->getGreen() + P12->getGreen() + P21->getGreen() + P22->getGreen();
            avg = sum / 4;
            scaledImg.pixels[row][col].setGreen(avg);
            
            sum = P11->getBlue() + P12->getBlue() + P21->getBlue() + P22->getBlue();
            avg = sum / 4;
            scaledImg.pixels[row][col].setBlue(avg);
        }
    }
    
    *this = scaledImg;

    return (*this);
}

// Color inversion of the image.
Image& RGBImage::operator ! () {    
    int row, col, maxLum;
    RGBPixel* imgPixel;

    maxLum = getMaxLuminocity();

    for (row = 0; row < getHeight(); row ++) {
        for (col = 0; col < getWidth(); col ++) {
            imgPixel = (RGBPixel* ) &getPixel(row, col);
            imgPixel->setRed(maxLum - imgPixel->getRed());
            imgPixel->setGreen(maxLum - imgPixel->getGreen());
            imgPixel->setBlue(maxLum - imgPixel->getBlue());
        }
    }
    
    return (*this);
}

// Histogram equalization of the image.
Image& RGBImage::operator ~ () {
    double *histogram = new double [getMaxLuminocity() + 1];
    int *histogramInt = new int [getMaxLuminocity() + 1];
	int pos, row , col, C, D, E;
	RGBPixel* imgPixel;

    RGBPixel **yuv;

    // Make the histogram array.
    yuv = new RGBPixel* [getHeight()];
    for (pos = 0; pos < getHeight(); pos ++) {
        yuv[pos] = new RGBPixel [getWidth()];
    }

    // Make the YUV array.
    for (row = 0; row < getHeight(); row ++) {
        for (col = 0; col < getWidth(); col ++) {
			imgPixel = (RGBPixel* ) &getPixel(row, col);
            // Red is Y, Green is U, Blue is V.
            yuv[row][col].setRed(((66*imgPixel->getRed() + 129*imgPixel->getGreen() + 25*imgPixel->getBlue() + 128) >> 8) + 16);
            yuv[row][col].setGreen(((-38*imgPixel->getRed() - 74*imgPixel->getGreen() + 112*imgPixel->getBlue() + 128) >> 8) + 128);
            yuv[row][col].setBlue(((112*imgPixel->getRed() - 94*imgPixel->getGreen() - 18*imgPixel->getBlue() + 128) >> 8) + 128); 
        }
    }

    // Make the histogram array.
	for (pos = 0; pos < getMaxLuminocity(); pos ++) {
		histogram[pos] = 0;
	}

	// Calculate the histogram.
	for (row = 0; row < getHeight(); row ++) {
		for (col = 0; col < getWidth(); col ++) {
			imgPixel = (RGBPixel* ) &yuv[row][col];
            // Take the Y.
			histogram[imgPixel->getRed()] ++;
		}
	}

	// Calculate probability distribution.
	for (pos = 0; pos < getMaxLuminocity(); pos  ++) {
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
            yuv[row][col].setRed(histogramInt[yuv[row][col].getRed()]);
        }
    }

    for (row = 0; row < getHeight(); row ++) {
        for (col = 0; col < getWidth(); col ++) {
            C = yuv[row][col].getRed() - 16;
            D = yuv[row][col].getGreen() - 128;
            E = yuv[row][col].getBlue() - 128;
            
            imgPixel = (RGBPixel* ) &getPixel(row, col);
            imgPixel->setRed(std::max(0, std::min((int) ((298 * C + 409 * E + 128) >> 8), 255)));
            imgPixel->setGreen(std::max(0, std::min((int) ((298 * C - 100 * D - 208 * E + 128) >> 8), 255)));
            imgPixel->setBlue(std::max(0, std::min((int) ((298 * C + 516 * D + 128) >> 8), 255)));
        }
    }

    delete[] histogram;
    delete[] histogramInt;
    for (pos = 0; pos < getHeight(); pos ++) {
        delete[] yuv[pos];
    }
    delete[] yuv;

    
    return (*this);
}

// Mirror the image.
Image& RGBImage::operator * () {
	int row, col;
    RGBImage newImg;
    RGBPixel* imgPixel;

    newImg.setHeight(getHeight());
    newImg.setWidth(getWidth());
    newImg.setMaxLuminocity(getMaxLuminocity());
    
    newImg.pixels = new RGBPixel* [getHeight()];
    
    for (row = 0; row < getHeight(); row ++) {
        newImg.pixels[row] = new RGBPixel [getWidth()];
    }

    for (row = 0; row < getHeight(); row ++) {
        for (col = 0; col < getWidth(); col ++) {
            imgPixel = (RGBPixel* ) &getPixel(row, col);
            (newImg.pixels[row][getWidth() - col - 1]).setRed(imgPixel->getRed());
            (newImg.pixels[row][getWidth() - col - 1]).setGreen(imgPixel->getGreen());
            (newImg.pixels[row][getWidth() - col - 1]).setBlue(imgPixel->getBlue());
        }
    }

    *this = newImg;

    return (*this);
} 

// Get a specific pixel from the image.
Pixel& RGBImage::getPixel (int row, int col) const {
    return (pixels[row][col]);
}
