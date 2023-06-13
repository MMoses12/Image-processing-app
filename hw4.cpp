#include <fstream>
#include <vector>
#include "image.hpp"
#include "rgb_image.hpp"
#include "gsc_image.hpp"
#include "token.hpp"

// Operator << for image objects.
// Output the image object into the out stream.
std::ostream& operator << (std::ostream& out, Image& image) {
    int row, col;
    RGBImage* rgbPtr;
    GSCImage* gscPtr;

    // Export image into the file.
    rgbPtr = dynamic_cast<RGBImage *>(&image);
    if (rgbPtr == nullptr) {
        gscPtr = dynamic_cast<GSCImage *>(&image);
        
        out << "P2" << endl;
        out << gscPtr->getWidth() << " " << gscPtr->getHeight() << " " << gscPtr->getMaxLuminocity() << endl;
        for (row = 0; row < gscPtr->getHeight(); row ++) {
            for (col = 0; col < gscPtr->getWidth(); col ++) {
                out << (int) ((GSCPixel* ) &gscPtr->getPixel(row, col))->getValue();
                out << endl;   
            }
        }
    }
    else {
        out << "P3" << endl;
        out << rgbPtr->getWidth() << " " << rgbPtr->getHeight() << " " << rgbPtr->getMaxLuminocity() << endl;
        for (row = 0; row < rgbPtr->getHeight(); row ++) {
            for (col = 0; col < rgbPtr->getWidth(); col ++) {
                out << (int) ((RGBPixel* ) &rgbPtr->getPixel(row, col))->getRed() << " ";
                out << (int) ((RGBPixel* ) &rgbPtr->getPixel(row, col))->getGreen() << " ";
                out << (int) ((RGBPixel* ) &rgbPtr->getPixel(row, col))->getBlue() << " ";
                out << endl;   
            }
        }
    }

    return (out);
}

// Read the image file and decide if the image is greyscaled or rgb.
// Then make a new object of it.
Image* readNetpbmImage (const char* filename) {
    ifstream f (filename);
    if (!f.is_open()) {
        std::cout << "[ERROR] Unable to open " << filename << std::endl;
    }

    Image* img_ptr = nullptr;
    string type;

    if (f.good() && !f.eof())
        f >> type;
    if (!type.compare("P3")) {
        img_ptr = new RGBImage(f);
    }
    else if (!type.compare("P2")) {
        img_ptr = new GSCImage(f);
    }
    else if (f.is_open()) {
        std::cout << "[ERROR] Invalid file format" << std::endl;
    }

    return (img_ptr);
}

// Print the options for the user.
void print_message () {
    cout << "Import image: i <filename> as <$token>" << endl;
    cout << "Export image: e <$token> as <filename>" << endl;
    cout << "Delete: d <$token>" << endl;
    cout << "Color inversion: n <$token>" << endl;
    cout << "Equalize: z <$token>" << endl;
    cout << "Mirror: m <$token>" << endl;
    cout << "Greyscale image: g <$token>" << endl;
    cout << "Scale: s <$token> by <factor>  " << endl;
    cout << "Rotate: r <$token> clockwise <X> times" << endl;
    cout << "Quit: q" << endl;
}

int main () {
    int pos, found = 0, row, col, rotates;
    double factor;
    ifstream fileO;
    ofstream fileC;
    string string, fileName, tokenName, string2;
    char command;
    vector<Token*> tokens;
    Image* imgPtr;
    GSCImage* gscPtr, ptr2;
    RGBImage* rgbPtr;
    Token token("", nullptr), *tokenPtr;

    do {
        print_message();
        cin >> command;

        switch (command) {
            // Import an Image to a token.
            case 'i':
                found = 0;

                cin >> fileName;
                cin >> string;
                cin >> tokenName;
                
                fileO.open(fileName);
                // Check if the file opened successfully.
                if (!fileO.good() || !fileO.is_open()) {
                    cout << "[ERROR] Unable to open " << fileName << endl;
                    fileO.close();
                    break;
                }

                // If "as" is not following filename the command is invalid.
                if (string.compare("as") != 0) {
                    cout << "\n-- Invalid command! --" << endl;
                    fileO.close();
                    break;
                }

                // If token's name does not start with $ the name is invalid.
                if (tokenName[0] != '$') {
                    cout << "\n-- Invalid command! --" << endl;
                    fileO.close();
                    break;
                }

                // Check if the token name already exists.
                for (pos = 0; pos < tokens.size(); pos ++) {
                    if (tokens[pos]->getName().compare(tokenName) == 0) {
                        found = 1;
                        break;
                    }
                }

                if (found == 1) {
                    cout << "[ERROR] Token " << tokenName << " exists" << endl;
                    fileO.close();
                    break;
                }
                imgPtr = readNetpbmImage(fileName.c_str());

                // Get the returned Image and put it as a token.
                tokenPtr = new Token();
                tokenPtr->setName(tokenName);
                tokenPtr->setPtr(imgPtr);
                tokens.push_back(tokenPtr);

                imgPtr = nullptr;

                fileO.close();
                cout << "[OK] Import " << tokenName << endl;

                break;
            
            // Export token to a file.
            case 'e':
                found = 0;

                cin >> tokenName;            
                cin >> string;
                cin >> fileName;
                
                // If token's name does not start with $ the name is invalid.
                if (tokenName[0] != '$') {
                    cout << "\n-- Invalid command! --" << endl;
                    break;
                }

                // Check if the token name already exists.
                for (pos = 0; pos < tokens.size(); pos ++) {
                    if (tokens[pos]->getName().compare(tokenName) == 0) {
                        found = 1;
                        break;
                    }
                }

                if (found == 0) {
                    cout << "[ERROR] Token " << tokenName << " not found!" << endl;
                    break;
                }
                                
                // If "as" is not following filename the command is invalid.
                if (string.compare("as") != 0) {
                    cout << "\n-- Invalid command! --" << endl;
                    continue;
                }

                // Check if the file exists.
                fileO.open(fileName);
                if (fileO.good() || fileO.is_open()) {
                    cout << "[ERROR] File exists" << endl;
                    fileO.close();
                    break;
                }
                fileO.close();
                   
                // Check if the file is able to create.
                fileC.open(fileName);
                if (!fileC) {
                    cout << "[ERROR] Unable to create file" << endl;
                    fileC.close();
                    break;
                }

                // Export image into the file.
                imgPtr = tokens[pos]->getPtr();
                fileC << *imgPtr;
                fileC.close();

                cout << "[OK] Export " << tokenName << endl;

                break;
            
            // Delete token.
            case 'd':
                found = 0;

                cin >> tokenName;

                for (pos = 0; pos < tokens.size(); pos ++) {
                    if (tokens[pos]->getName().compare(tokenName) == 0) {
                        found = 1;
                        break;
                    }
                }

                if (found == 0) { 
                    cout << "[ERROR] Token " << tokenName << " not found!" << endl;
                    break;
                }

                delete tokens[pos];
                tokens.erase(tokens.begin() + pos);

                cout << "[OK] Delete " << tokenName << endl;

                break;

            // Color invertion of a specific image.
            case 'n':
                found = 0;

                cin >> tokenName;

                // Search for the token name.
                for (pos = 0; pos < tokens.size(); pos ++) {
                    if (tokens[pos]->getName().compare(tokenName) == 0) {
                        found = 1;
                        break;
                    }
                }

                if (found == 0) { 
                    cout << "[ERROR] Token " << tokenName << " not found!" << endl;
                    break;
                }

                imgPtr = tokens[pos]->getPtr();
                !(*imgPtr);

                tokens[pos]->setPtr(imgPtr);

                cout << "[OK] Color Inversion " << tokenName << endl;

                break;

            // Equalize image.
            case 'z':
                found = 0;

                cin >> string;

                for (pos = 0; pos < tokens.size(); pos ++) {
                    if (tokens[pos]->getName().compare(string) == 0) {
                        found = 1;
                        break;
                    }
                }

                if (found == 0) { 
                    cout << "[ERROR] " << string << " not found!" << endl;
                    break;
                }

                imgPtr = tokens[pos]->getPtr();
                ~(*imgPtr);

                tokens[pos]->setPtr(imgPtr);

                cout << "[OK] Equalize " << string << endl;

                break;

            // Mirror image.
            case 'm':
                found = 0;

                cin >> tokenName;

                // Search for the token name.
                for (pos = 0; pos < tokens.size(); pos ++) {
                    if (tokens[pos]->getName().compare(tokenName) == 0) {
                        found = 1;
                        break;
                    }
                }

                if (found == 0) { 
                    cout << "[ERROR] " << tokenName << " not found!" << endl;
                    break;
                }

                imgPtr = tokens[pos]->getPtr();
                *(*imgPtr);

                tokens[pos]->setPtr(imgPtr);

                cout << "[OK] Mirror " << tokenName << endl;

                break;

            // Greyscale an image. If the image is already greyscaled no operation is needed.
            case 'g':
                found = 0;

                cin >> tokenName;

                // Search for the token name.
                for (pos = 0; pos < tokens.size(); pos ++) {
                    if (tokens[pos]->getName().compare(tokenName) == 0) {
                        found = 1;
                        break;
                    }
                }

                if (found == 0) { 
                    cout << "[ERROR] " << tokenName << " not found!" << endl;
                    break;
                }

                imgPtr = tokens[pos]->getPtr();
                 if (typeid(*imgPtr) == typeid(RGBImage)) {
                    rgbPtr = dynamic_cast<RGBImage*>(imgPtr);
                    if (rgbPtr != nullptr) {
                        GSCImage* gscImg = new GSCImage(*rgbPtr);
                        imgPtr = gscImg;
                        delete rgbPtr;

                        cout << "[OK] Grayscale " << tokenName << endl;
                        tokens[pos]->setPtr(imgPtr);
                    }
                } else if (typeid(*imgPtr) == typeid(GSCImage)) {
                    gscPtr = dynamic_cast<GSCImage*>(imgPtr);
                    if (gscPtr != nullptr) {
                        cout << "[NOP] Already grayscale " << tokenName << endl;
                    }    
                }

                break;
            
            // Scale image.
            case 's':
                found = 0;

                cin >> tokenName >> string >> factor;

                // Search for the token name.
                for (pos = 0; pos < tokens.size(); pos ++) {
                    if (tokens[pos]->getName().compare(tokenName) == 0) {
                        found = 1;
                        break;
                    }
                }

                if (found == 0) { 
                    cout << "[ERROR] " << tokenName << " not found!" << endl;
                    break;
                }

                // If "by" is not following token name the command is invalid.
                if (string.compare("by") != 0) {
                    cout << "\n-- Invalid command! --" << endl;
                    continue;
                }

                imgPtr = tokens[pos]->getPtr();
                *imgPtr *= factor;

                tokens[pos]->setPtr(imgPtr);

                cout << "[OK] Scale " << tokenName << endl;

                break;
            
            // Rotate image.
            case 'r':
                found = 0;

                cin >> tokenName >> string >> rotates >> string2;

                // Search for the token name.
                for (pos = 0; pos < tokens.size(); pos ++) {
                    if (tokens[pos]->getName().compare(tokenName) == 0) {
                        found = 1;
                        break;
                    }
                }

                if (found == 0) { 
                    cout << "[ERROR] " << tokenName << " not found!" << endl;
                    break;
                }

                // If "clockwise" is not following token name the command is invalid.
                if (string.compare("clockwise") != 0) {
                    cout << "\n-- Invalid command! --" << endl;
                    continue;
                }

                // If "times" is not following token name the command is invalid.
                if (string2.compare("times") != 0) {
                    cout << "\n-- Invalid command! --" << endl;
                    continue;
                }

                imgPtr = tokens[pos]->getPtr();
                *imgPtr += rotates;

                tokens[pos]->setPtr(imgPtr);

                cout << "[OK] Rotate " << tokenName << endl;

                break;
            
            // Exit the program.
            case 'q':
                for (pos = 0; pos < tokens.size(); pos ++) {
                    delete tokens[pos];
                }

                break;

            // Invalid command.
            default:
                cout << "\n-- Invalid command! --" << endl;
                break;
        }

    } while (command != 'q');
}
