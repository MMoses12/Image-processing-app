#include "token.hpp"
#include "rgb_image.hpp"
#include "gsc_image.hpp"

Token::Token() {
	setName("");
	setPtr(nullptr);
}

// Constructor for a token object.
Token::Token (const string& name, Image* img) {
	setName(name);
	setPtr(img);
}

// Destructor of a token object.
Token::~Token() {
	Image* imgPtr;
	RGBImage* rgbPtr;
	GSCImage* gscPtr;

    imgPtr = getPtr();

    if (imgPtr != nullptr) {
        if (typeid(*imgPtr) == typeid(RGBImage)) {
            rgbPtr = dynamic_cast<RGBImage*>(imgPtr);
			if (rgbPtr != nullptr) {
                delete rgbPtr;
				setPtr(nullptr);
            }
        } else if (typeid(*imgPtr) == typeid(GSCImage)) {
           	gscPtr = dynamic_cast<GSCImage*>(imgPtr);
            if (gscPtr != nullptr) {
           		delete gscPtr;
				setPtr(nullptr);
        	}	
        }
    }
}

// Get the name of the token.
string Token::getName() const {
	return (name);
}

// Get the Image of the token.
Image* Token::getPtr() const {
	return (ptr);
}

// Set the wanted name for the token.
void Token::setName (const string& newName) {
	name = string(newName);
}

// Set the Image for the token.
void Token::setPtr (Image* ptr) {
	this->ptr = ptr;
}
