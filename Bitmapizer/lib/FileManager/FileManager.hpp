#ifndef FileManager_hpp
#define FileManager_hpp

#include <stdio.h>
#include <iostream>
#include <filesystem>
#include <string>
#include <fstream>
#include "Bitmap.hpp"

namespace fs = std::filesystem;
using namespace std;


class FileManager {
    
private:
    fs::path m_readFile;
    fs::path m_writePath;
    uint8_t* m_bytes;
    streampos m_fileSize;
    
public:
    
    FileManager(fs::path readPath, fs::path writePath);
    ~FileManager();
    
    void readBinaryData();
    void setFilenameAppendix(string appendix="");
    void writeBitmap(Bitmap* bmp);
    uint8_t* getBytes() { return m_bytes; }
    size_t getFilesize() { return (size_t)m_fileSize; }
};


#endif /* FileManager_hpp */
