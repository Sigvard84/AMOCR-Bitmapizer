
#include <filesystem>
#include <vector>
#include <string>
#include "Bitmap.hpp"
#include "FileManager.hpp"

#ifndef functions_h
#define functions_h

constexpr int WIDTH = 800;
constexpr int HEIGHT = 600;
constexpr int RGB888 = 24;

namespace fs = std::filesystem;
using namespace std;


void bitmapize() {
    
    // From which folder to open the binary files:
    string binPath = fs::path("/Users/fsjolander/Documents/JTH/VT_2022/Bachelor_Thesis/Applications/AMOCR-Bitmapizer/bin-img");

    // To which folder to save the resulting bmp files:
    string bitmapizedDestinationPath = fs::path("/Users/fsjolander/Documents/JTH/VT_2022/Bachelor_Thesis/Applications/AMOCR-desktop/bmp_images/input_folder");


    for (const auto &srcFile : fs::directory_iterator(binPath)) {

        FileManager fm(srcFile, bitmapizedDestinationPath);

        fm.readBinaryData();
        uint8_t* bytes = fm.getBytes();

        Bitmap bmp(WIDTH, HEIGHT, fm.getFilesize(), RGB888, bytes);

        fm.writeBitmap(bmp.m_header, bmp.m_headerSize, bmp.m_pxData, bmp.m_byteLength);
    }
}

void convert() {
    
    // Root folder where original images are located within subfolders:
    string imgRootPath = fs::path("/Users/fsjolander/Documents/JTH/VT_2022/Bachelor_Thesis/Applications/AMOCR-web/web-app/src/presentation-layer/public/meter-images/8bit");
    
    vector<fs::path> readPaths;
    
    string::size_type const lastSlash(imgRootPath.find_last_of("/\\"));
    string folderRootPath = fs::path(imgRootPath.substr(0, lastSlash));
    
    // Get the paths to all subfolders to read from:
    for (const auto &srcFolder : fs::directory_iterator(imgRootPath)) {
        if (srcFolder.is_directory())
            readPaths.push_back(srcFolder.path());
    }
    
    for (const auto &srcFolder : readPaths) {
        
        string sizePercent = srcFolder.string().substr(srcFolder.string().find_last_of("/\\") + 1);
        
        for (const auto &srcFile : fs::directory_iterator(srcFolder)) {
            
            string filePath = srcFile.path().string();
            string fileName = filePath.substr(filePath.find_last_of("/\\") + 1);
            string::size_type const dot(fileName.find_last_of('.'));
            
            if (fileName.substr(dot, 4) == ".bmp") {
                
                string::size_type const underscore(fileName.find_first_of("_"));
                string orgFilename = fileName.substr(0, underscore);
                
                //************************************** Convert to 4 bit bmp **************************************
                string colourDepth = "4bit";
                string destinationPath = fs::path(folderRootPath + "/" + colourDepth + "/" + sizePercent);
                
                Bitmap bmp4bit(srcFile);
                FileManager fm4bit(srcFile, destinationPath);
                
                fm4bit.setFilename(orgFilename, colourDepth, sizePercent);
                bmp4bit.convertFrom8To4Bit();
                fm4bit.writeBitmap(bmp4bit.m_header, bmp4bit.m_headerSize, bmp4bit.m_pxData, bmp4bit.m_byteLength);
                
                //************************************** Convert to 2 bit bmp **************************************
                colourDepth = "2bit";
                destinationPath = fs::path(folderRootPath + "/" + colourDepth + "/" + sizePercent);
                
                Bitmap bmp2bit(srcFile);
                FileManager fm2bit(srcFile, destinationPath);
                
                fm2bit.setFilename(orgFilename, colourDepth, sizePercent);
                bmp2bit.convertFrom8To2Bit();
                fm2bit.writeBitmap(bmp2bit.m_header, bmp2bit.m_headerSize, bmp2bit.m_pxData, bmp2bit.m_byteLength);
                
                //************************************** Convert to 1 bit bmp **************************************
                colourDepth = "1bit";
                destinationPath = fs::path(folderRootPath + "/" + colourDepth + "/" + sizePercent);
                
                Bitmap bmp1bit(srcFile);
                FileManager fm1bit(srcFile, destinationPath);
                
                fm1bit.setFilename(orgFilename, colourDepth, sizePercent);
                bmp1bit.convertFrom8To1Bit();
                fm1bit.writeBitmap(bmp1bit.m_header, bmp1bit.m_headerSize, bmp1bit.m_pxData, bmp1bit.m_byteLength);
            }
            
            
        }
    }
}

#endif /* functions_h */
