#ifndef Bitmap_hpp
#define Bitmap_hpp

#include <stdio.h>
#include <cstdint>
#include <cstddef>
#include <filesystem>
#include <cmath>
#include "FileManager.hpp"

namespace fs = std::filesystem;
using namespace std;

class Bitmap {
    
private:
    
    size_t m_width, m_height, m_fileSize;
    uint8_t m_bitsPerPx;
    uint8_t* m_colourTable;
    uint8_t* m_padFreePxData;
    int m_numberOfColours;
    int m_paddingAmount;
    
    void createHeader();
    void loadHeaderFromBmp(const uint8_t* bmpFile);
    void getPixels(const uint8_t* pxData);
    void getPixelsFromBmp(const uint8_t* pxData);
    void setNumberOfColours();
    void setHeaderData();
    void createColourTable();
    void getPadFreePxData();
        
    
public:
    
    uint8_t* m_header;
    uint8_t* m_pxData;
    size_t m_byteLength;
    size_t m_headerSize;
    
    Bitmap(fs::path srcFile);
    Bitmap(size_t width, size_t height, size_t byteLength, uint8_t bitsPerPx, const uint8_t* pxData);
    ~Bitmap();
    
    void convertFrom8To4Bit();
    void convertFrom8To2Bit();
    void convertFrom8To1Bit();

};

#endif /* Bitmap_hpp */
