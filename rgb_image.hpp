#ifndef _RGBIMAGE_HPP_
#define _RGBIMAGE_HPP_
#include "image.hpp"
#include "rgb_pixel.hpp"

using namespace std;

class RGBImage : public Image {
    private:
        RGBPixel** pixels;
    public:
        RGBImage();
        RGBImage(const RGBImage& img);
        RGBImage(std::istream& stream);
        ~RGBImage();

        RGBImage& operator = (const RGBImage& img);

        virtual Image& operator += (int) override;
        virtual Image& operator *= (double factor) override;
        virtual Image& operator !() override;
        virtual Image& operator ~() override;
        virtual Image& operator *() override;

        virtual Pixel& getPixel (int row, int col) const override;
};  

#endif