#ifndef _RGBPIXEL_HPP_
#define _RGBPIXEL_HPP_

#include"pixel.hpp"

class RGBPixel : public Pixel {
    private:
        unsigned char rgb [3];
    public:
        RGBPixel() = default;
        RGBPixel(const RGBPixel& p);
        RGBPixel(unsigned char r, unsigned char g, unsigned char b);

        unsigned char getRed();
        unsigned char getGreen();
        unsigned char getBlue();
        void setRed(int r);
        void setGreen(int g);
        void setBlue(int b);
};

#endif