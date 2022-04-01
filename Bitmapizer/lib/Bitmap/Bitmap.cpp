#include "Bitmap.hpp"

Bitmap::Bitmap(fs::path srcFile) {
    
    // Open file and load its data:
    FileManager fm(srcFile);
    fm.readBinaryData();
    uint8_t* fileBytes = fm.getBytes();
    
    // Read data on pixel dimensions and colour depth:
    m_width = fileBytes[18] + (fileBytes[19] << 8) + (fileBytes[20] << 16) + (fileBytes[21] << 24);
    m_height = fileBytes[22] + (fileBytes[23] << 8) + (fileBytes[24] << 16) + (fileBytes[25] << 24);
    m_bitsPerPx = fileBytes[28];
    
    // Calculate how much padding the image has:
    m_paddingAmount = ((4 - (int(m_width) * (m_bitsPerPx/8)) % 4) % 4);
    
    setNumberOfColours();
    setHeaderData();
    
    // Read data on image file size and calculate byte length of the raster data:
    m_fileSize = fileBytes[2] + (fileBytes[3] << 8) + (fileBytes[4] << 16) + (fileBytes[5] << 24);
    m_byteLength = m_fileSize - m_headerSize;
        
    loadHeaderFromBmp(fileBytes);
    
    uint8_t* pxDataStart = &fileBytes[m_headerSize];
    getPixelsFromBmp(pxDataStart);
}


Bitmap::Bitmap(size_t width, size_t height, size_t byteLength, uint8_t bitsPerPx, const uint8_t* pxData) {
    
    m_width = width;
    m_height = height;
    m_bitsPerPx = bitsPerPx;
    
    m_paddingAmount = ((4 - (int(width) * (m_bitsPerPx/8)) % 4) % 4);
    m_byteLength = byteLength + (m_paddingAmount * m_height);
    
    setNumberOfColours();
    setHeaderData();
    
    m_fileSize = m_headerSize + m_byteLength;
    
    createHeader();
    
    getPixels(pxData);
}


Bitmap::~Bitmap() {
    
    if (m_pxData != nullptr)
        delete [] m_pxData;
    
    if (m_header != nullptr)
        delete [] m_header;
}


void Bitmap::setNumberOfColours() {
    
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
}


void Bitmap::getPixelsFromBmp(const uint8_t* pxData) {
    
    m_pxData = new uint8_t[m_byteLength];
    
    for (int i = 0; i < m_byteLength; i++) {
        m_pxData[i] = pxData[i];
    }
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


void Bitmap::setHeaderData() {
    
    const int colourTableSize = m_numberOfColours * 4;
    
    m_headerSize = 54 + colourTableSize; // 54 = fileHeader(14) + infoHeader(40)
    m_header = new uint8_t[m_headerSize];
}


void Bitmap::loadHeaderFromBmp(const uint8_t* bmpFile) {
    
    for (int i = 0; i < m_headerSize; i++) {
        m_header[i] = bmpFile[i];
    }
}


void Bitmap::createHeader() {
    
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
    m_header[10] = m_headerSize; //m_headerSize;
    m_header[11] = m_headerSize >> 8;
    m_header[12] = m_headerSize >> 16;
    m_header[13] = m_headerSize >> 24;
    
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
    
    createColourTable();
    
}


void Bitmap::convertFrom8To4Bit() {
    
    if (m_bitsPerPx != 8) {
        return;
    }
    
    const int bitsPerPx = 4;
    
    // Calculate new padding:
    const int newPaddingAmount = ((4 - (int(m_width) * (bitsPerPx/8)) % 4) % 4);
    size_t paddingBytes = m_paddingAmount * m_height;
    
    // Create new array to store the pixels in:
    uint8_t* newPxData;
    size_t extraByte = m_byteLength % 2 == 0 ? 0 : 1; // In case we need an extra half-byte (odd numbers)
    size_t newByteLength = (m_byteLength - paddingBytes)/2 + (newPaddingAmount * m_height) + extraByte;
    newPxData = new uint8_t[newByteLength];
    
    
    // Get the pixel data with added padding:
    for (int i = 0; i < newByteLength; i++) {
        
        int j = i * 2; // index for the old pxData
        
        uint8_t byte1 = m_pxData[j]/16;
        uint8_t byte2;
        
        if (newPaddingAmount != 0 && (j != 0 && j % m_width == 0)) {
            byte2 = 0; // Padding
        } else {
            byte2 = m_pxData[j+1]/16;
        }
        
        newPxData[i] = byte1 << 4 | byte2;
        
        int nextPxNumber = j + 2;
        
        if (nextPxNumber % m_width == 0) {
            for (int padPx = 1; padPx <= newPaddingAmount; padPx++) {
                newPxData[i+padPx] = 0;
            }
            i += newPaddingAmount;
        }
    }
    
    // Update member variables:
    m_bitsPerPx = bitsPerPx;
    m_paddingAmount = newPaddingAmount;
    m_byteLength = newByteLength;
    
    delete [] m_pxData;
    m_pxData = newPxData;
    
    setNumberOfColours();
    createHeader();
}


void Bitmap::createColourTable() {
    
    if (m_headerSize == 54) {
        return;
    }
    
    int startIndex = 54; // Header ends at index 53.
    int incrementSize = 256 / (m_numberOfColours - 1);
    uint8_t colorValue = 0;
    
    for (; startIndex < m_headerSize; startIndex++) {
        m_header[startIndex] = colorValue; // Red
        m_header[++startIndex] = colorValue; // Green
        m_header[++startIndex] = colorValue; // Blue
        m_header[++startIndex] = 0; // Reserved (= 0)
        
        colorValue += incrementSize;
    }
    
}
