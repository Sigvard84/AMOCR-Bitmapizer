#include "Bitmap.hpp"


Bitmap::Bitmap(size_t width, size_t height, size_t byteLength, uint8_t bitsPerPx, const uint8_t* pxData) {
    
    m_width = width;
    m_height = height;
    m_bitsPerPx = bitsPerPx;
    
    m_paddingAmount = ((4 - (int(width) * (m_bitsPerPx/8)) % 4) % 4);
    m_byteLength = byteLength + (m_paddingAmount * m_height);
    
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
    
    getPixels(pxData);
}


Bitmap::~Bitmap() {
    
    if (m_pxData != nullptr)
        delete [] m_pxData;
    
    if (m_header != nullptr)
        delete [] m_header;
}


void Bitmap::getPixels(const uint8_t* pxData) {
    
    m_pxData = new uint8_t[m_byteLength];
    
    if (m_paddingAmount == 0) { // Just copy the array
        
        for (int i = 0; i < m_byteLength; i++) {
            m_pxData[i] = pxData[i];
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


void Bitmap::createHeader() {
    
    const int colourTableSize = m_numberOfColours * 4;
    m_headerSize = 54 + colourTableSize; // 54 = fileHeader(14) + infoHeader(40)
    
    m_fileSize = m_headerSize + m_byteLength;
    
    m_header = new uint8_t[m_headerSize];
    
    // FILE HEADER //
    
    // File type
    m_header[0] = 66; // B
    m_header[1] = 77; // M
    // File size
    m_header[2] = m_fileSize;
    m_header[3] = m_fileSize >> 8;
    m_header[4] = m_fileSize >> 16;
    m_header[5] = m_fileSize >> 24;
    // Reserved 1 (not used)
    m_header[6] = 0;
    m_header[7] = 0;
    // Reserved 1 (not used)
    m_header[8] = 0;
    m_header[9] = 0;
    // Pixel data offset
    m_header[10] = m_headerSize;
    m_header[11] = 0;
    m_header[12] = 0;
    m_header[13] = 0;
    
    // INFORMATION HEADER //
    
    // Header size
    m_header[14] = 40;
    m_header[15] = 0;
    m_header[16] = 0;
    m_header[17] = 0;
    // Image width
    m_header[18] = m_width;
    m_header[19] = m_width >> 8;
    m_header[20] = m_width >> 16;
    m_header[21] = m_width >> 24;
    // Image hieght
    m_header[22] = m_height;
    m_header[23] = m_height >> 8;
    m_header[24] = m_height >> 16;
    m_header[25] = m_height >> 24;
    // Planes
    m_header[26] = 1;
    m_header[27] = 0;
    // Bits per pixel
    m_header[28] = m_bitsPerPx;
    m_header[29] = 0;
    // Compression (no compression)
    m_header[30] = 0;
    m_header[31] = 0;
    m_header[32] = 0;
    m_header[33] = 0;
    // Image size (no compression)
    m_header[34] = 0;
    m_header[35] = 0;
    m_header[36] = 0;
    m_header[37] = 0;
    // X pixels per meter
    m_header[38] = 0;
    m_header[39] = 0;
    m_header[40] = 0;
    m_header[41] = 0;
    // X pixels per meter
    m_header[42] = 0;
    m_header[43] = 0;
    m_header[44] = 0;
    m_header[45] = 0;
    // Total colors
    m_header[46] = m_numberOfColours;
    m_header[47] = m_numberOfColours >> 8;
    m_header[48] = m_numberOfColours >> 16;
    m_header[49] = m_numberOfColours >> 24;
    // Important colors
    m_header[50] = 0;
    m_header[51] = 0;
    m_header[52] = 0;
    m_header[53] = 0;
    
    
    //Todo: colour table(s)
    
}



