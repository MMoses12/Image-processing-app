#include "rgb_pixel.hpp"

// Copy constructor for a rgb pixel.
RGBPixel::RGBPixel (const RGBPixel& p) {
    this->rgb[0] = p.rgb[0];
    this->rgb[1] = p.rgb[1];
    this->rgb[2] = p.rgb[2];
}

// Constructor with initialized values for red, green and blue.
RGBPixel::RGBPixel (unsigned char r, unsigned char g, unsigned char b) {
    this->rgb[0] = r;
    this->rgb[1] = g;
    this->rgb[2] = b;
}

// Get the red value from a pixel.
unsigned char RGBPixel::getRed () {
    return(this->rgb[0]);
}

// Get the green value from a pixel.
unsigned char RGBPixel::getGreen () {
    return(this->rgb[1]);
}

// Get the blue value from a pixel.
unsigned char RGBPixel::getBlue () {
    return(this->rgb[2]);
}

// Set the red value for the pixel.
void RGBPixel::setRed (int r) {
    rgb[0] = r;
}

// Set the green value for the pixel.
void RGBPixel::setGreen (int g) {
    rgb[1] = g;
}

// Set the blue value for the pixel.
void RGBPixel::setBlue (int b) {
    rgb[2] = b;
}
