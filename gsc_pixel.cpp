#include "gsc_pixel.hpp"
#include <iostream>

using namespace std;

// Copy constructor for a greyscaled pixel.
GSCPixel::GSCPixel(const GSCPixel& p) {
    this->brightness = p.brightness;
}

// Constructor with specific value for the brightness of the pixel.
GSCPixel::GSCPixel(unsigned char value) {
    this->brightness = value;
}

// Get the brightness value.
unsigned char GSCPixel::getValue() {
    return (this->brightness);
}

// Set the value of brightness.
void GSCPixel::setValue(unsigned char value) {
    this->brightness = value;
}