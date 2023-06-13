#ifndef _GSCPIXEL_HPP_
#define _GSCPIXEL_HPP_

#include "pixel.hpp"

class GSCPixel : public Pixel {
    private: 
        unsigned char brightness;
    public:
        // Constructors.
        GSCPixel() = default;
        GSCPixel(const GSCPixel& p);
        GSCPixel(unsigned char value);
        
        // Greyscale pixel methods.
        unsigned char getValue();
        void setValue(unsigned char value);
};

#endif
