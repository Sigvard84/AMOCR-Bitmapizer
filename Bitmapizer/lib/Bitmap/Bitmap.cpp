#include "Bitmap.hpp"


Bitmap::Bitmap(size_t width, size_t height, size_t byteLength, uint8_t bitsPerPx, const uint8_t* pxData) {
    
    m_width = width;
    m_height = height;
    m_bitsPerPx = bitsPerPx;
    
    m_paddingAmount = ((4 - (int(width) * (m_bitsPerPx/8)) % 4) % 4);
    
    // Determine number of colours used:
    switch(m_bitsPerPx) {
        case 8:
            m_numberOfColours = 256;
            break;
        case 4:
            m_numberOfColours = 16;
            break;
        case 2:
            m_numberOfColours = 4;
            break;
        case 1:
            m_numberOfColours = 2;
            break;
        default:
            m_numberOfColours = 0; // More than 256 colours
            break;
    }
    
    createHeader();

    m_byteLength = byteLength + (m_paddingAmount * m_height);
    
    
    getPixels(pxData);
    
}

Bitmap::~Bitmap() {
    if (m_pxData != nullptr)
        delete [] m_pxData;
}


void Bitmap::createHeader() {
    // Todo
}


void Bitmap::getPixels(const uint8_t* pxData) {
    
    if (m_paddingAmount == 0) { // Just copy the array
        
        for (int i = 0; i < m_byteLength; i++) {
            
        }
        
    } else { // Copy array and insert padding
        
        for (int i = 0; i < m_byteLength; i++) {

            if ((i+1) % m_width == 0) { // Add padding
                m_pxData[i] = pxData[i];
                
                for (int j = 1; j <= m_paddingAmount; j++) {
                    m_pxData[i + j] = 0;
                }
                
                i += m_paddingAmount;
                
            } else { // Only copy pixel data
                m_pxData[i] = pxData[i];
            }
        }
    }
    
    
}
