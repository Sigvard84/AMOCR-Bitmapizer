//
//  FileManager.cpp
//  Bitmapizer
//
//  Created by Fredrik Sjölander on 2022-03-29.
//

#include "FileManager.hpp"

FileManager::FileManager(fs::path readFile, fs::path writePath) {
    
    m_readFile = readFile;
    m_writePath = writePath;
}


FileManager::~FileManager() {
    
    if (m_bytes != nullptr) {
        delete [] m_bytes;
    }
    
}

void FileManager::setFilenameAppendix(string appendix) {
    
    string binPath = m_readFile;
    
    // Get the name of the binary file:
    string binFilename = binPath.substr(binPath.find_last_of("/\\") + 1);
    string::size_type const p(binFilename.find_last_of('.'));
    
    // Set the name of the bmp file to save:
    string bmpFileName = binFilename.substr(0, p) + appendix + ".bmp";
    
    // Update m_writePath:
    m_writePath += "/" + bmpFileName;
}


void FileManager::readBinaryData() {
    
    ifstream file(m_readFile, ios::binary);
    
    // Get file size:
    file.seekg(0, ios::end);
    m_fileSize = file.tellg();
    file.seekg(0, ios::beg);
    
    m_bytes = new uint8_t[(int)m_fileSize];
    
    // Store file contents in m_bytes:
    file.read((char*)m_bytes, m_fileSize);
    
    file.close();
}


void FileManager::writeBitmap(Bitmap* bmp) {
    
    fstream bmpFile;
    bmpFile.open(m_writePath, ios::app | ios::binary);
    
    bmpFile.write(reinterpret_cast<char*>(bmp->m_header), bmp->m_headerSize);
    bmpFile.write(reinterpret_cast<char*>(bmp->m_pxData), bmp->m_byteLength);
    
    bmpFile.close();
    
}
