#include <cstdlib>
#include "image.hpp"
#include "rgb_image.hpp"
#include "gsc_pixel.hpp"

using namespace std;

class GSCImage : public Image {
    private:
        GSCPixel** pixels;
    public:
        GSCImage();
        GSCImage(const GSCImage& img);
        GSCImage(const RGBImage& greyscaled);
        GSCImage(std::istream& stream);
        ~GSCImage();

        GSCImage& operator = (const GSCImage& img);
        virtual Image& operator += (int times) override;

        virtual Image& operator *= (double factor) override;
        virtual Image& operator !() override;
        virtual Image& operator ~() override;
        virtual Image& operator *() override;

        virtual Pixel& getPixel (int row, int col) const override;
};
