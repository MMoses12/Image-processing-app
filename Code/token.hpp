#ifndef _TOKEN_HPP_
#define _TOKEN_HPP_
#include <string>
#include "image.hpp"

// Token is used to connect an Image with a name.
// Every token must start with the character '$'.
class Token {
    private:
        string name;
        Image* ptr;
    public:
        Token();
        Token (const string& string, Image* img);
        ~Token();
        string getName() const;
        Image* getPtr() const;
        void setName (const string& );
        void setPtr (Image* ptr);
};

#endif
