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
    m_binDestinationPath = destinationPath;
    
    string::size_type const lastSlash(destinationPath.string().find_last_of("/\\"));    
    fs::path parentDirectory = destinationPath.string().substr(0, lastSlash);
    
    std::filesystem::create_directory(parentDirectory);
        
    auto directoryWasCreated = std::filesystem::create_directory(destinationPath);
    
    if (directoryWasCreated) {
        std::cout << "Directory created: " << destinationPath << endl;
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


void FileManager::setFileExt(string fileExt) {
    
    string filename = m_folderName + fileExt;
    m_binDestinationPath += "/" + filename;
}


void FileManager::setFilename(string orgName, string colourDepth, string sizePercent) {
    
    m_folderName = orgName + "_" + colourDepth + "_" + sizePercent;
    string filename = m_folderName + ".bmp";
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


void FileManager::writeBinFile(uint8_t* pxData, size_t byteLength) {
    
    setFileExt(".bin");
    
    fstream binFile;
    binFile.open(m_binDestinationPath, ios::app | ios::binary);
    
    binFile.write(reinterpret_cast<char*>(pxData), byteLength);
    binFile.close();
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
