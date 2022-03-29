#ifndef Bitmap_hpp
#define Bitmap_hpp

#include <stdio.h>
#include <cstdint>
#include <cstddef>

using namespace std;

class Bitmap {
    
private:
    
    size_t m_width, m_height, m_fileSize;
    uint8_t m_bitsPerPx;
    uint8_t* m_colourTable;
    int m_numberOfColours;
    int m_paddingAmount;
    
    void createHeader();
    void getPixels(const uint8_t* pxData);
    
    
public:
    
    uint8_t* m_header;
    uint8_t* m_pxData;
    size_t m_byteLength;
    size_t m_headerSize;
    
    Bitmap(size_t width, size_t height, size_t byteLength, uint8_t bitsPerPx, const uint8_t* pxData);
    ~Bitmap();
    

};

#endif /* Bitmap_hpp */
