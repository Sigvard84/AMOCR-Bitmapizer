#ifndef FileManager_hpp
#define FileManager_hpp

#include <stdio.h>
#include <iostream>
#include <filesystem>
#include <string>
#include <fstream>

namespace fs = std::filesystem;
using namespace std;


class FileManager {
    
private:
    
    fs::path m_srcPath;
    fs::path m_destinationPath;
    uint8_t* m_bytes = nullptr;
    streampos m_fileSize;
    string m_appendix = "";
    bool m_fileNameCreated = false;
    
    
public:
    
    FileManager(fs::path srcPath);
    FileManager(fs::path srcPath, fs::path destinationPath);
    ~FileManager();
    
    void readBinaryData();
    void setFilenameAppendix(string appendix="");
    void setFilename(string orgName, string colourDepth, string sizePercent);
    void writeBitmap(uint8_t* header, size_t headerSize, uint8_t* pxData, size_t byteLength);
    uint8_t* getBytes() { return m_bytes; }
    size_t getFilesize() { return (size_t)m_fileSize; }
};


#endif /* FileManager_hpp */
