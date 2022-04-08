//
//  FileManager.cpp
//  Bitmapizer
//
//  Created by Fredrik Sjölander on 2022-03-29.
//

#include "FileManager.hpp"

FileManager::FileManager(fs::path srcPath) {
    
    m_srcPath = srcPath;
}

FileManager::FileManager(fs::path srcPath, fs::path destinationPath) {
    
    m_srcPath = srcPath;
    m_destinationPath = destinationPath;
        
    auto directoryWasCreated = std::filesystem::create_directory(destinationPath);
    
    if (not directoryWasCreated) {
        std::cout << "Directory not created" << endl;
    }
    
}


FileManager::~FileManager() {
    
    if (m_bytes != nullptr) {
        delete [] m_bytes;
    }
    
}

void FileManager::setFilenameAppendix(string appendix) {
    
    m_appendix = appendix;
    string srcPath = m_srcPath;
    
    // Get the name of the binary file:
    string srcFileName = srcPath.substr(srcPath.find_last_of("/\\") + 1);
    string::size_type const p(srcFileName.find_last_of('.'));
    
    // Set the name of the bmp file to save:
    string bmpFileName = srcFileName.substr(0, p) + m_appendix + ".bmp";
    
    // Update m_writePath:
    m_destinationPath += "/" + bmpFileName;
    
    m_fileNameCreated = true;
}


void FileManager::setFilename(string orgName, string colourDepth, string sizePercent) {
    
    string filename = orgName + "_" + colourDepth + "_" + sizePercent + ".bmp";
    m_destinationPath += "/" + filename;
    
    m_fileNameCreated = true;
}


void FileManager::readBinaryData() {
    
    ifstream srcFile(m_srcPath, ios::binary);
    
    // Get file size:
    srcFile.seekg(0, ios::end);
    m_fileSize = srcFile.tellg();
    srcFile.seekg(0, ios::beg);
    
    m_bytes = new uint8_t[(int)m_fileSize];
    
    // Store file contents in m_bytes:
    srcFile.read((char*)m_bytes, m_fileSize);
    
    srcFile.close();
}


void FileManager::writeBitmap(uint8_t* header, size_t headerSize, uint8_t* pxData, size_t byteLength) {
    
    if (!m_fileNameCreated) {
        setFilenameAppendix();
    }
    
    fstream bmpFile;
    bmpFile.open(m_destinationPath, ios::app | ios::binary);
    
    bmpFile.write(reinterpret_cast<char*>(header), headerSize);
    bmpFile.write(reinterpret_cast<char*>(pxData), byteLength);
    
    bmpFile.close();
    
}
