#include <iostream>
#include <filesystem>
#include <vector>
#include <string>
#include <fstream>
#include "Bitmap.hpp"
#include "FileManager.hpp"

constexpr int WIDTH = 800;
constexpr int HEIGHT = 600;

namespace fs = std::filesystem;
using namespace std;


int main(int argc, const char * argv[]) {
    
    // From which folder to open the binary files:
    string binPath = fs::path("/Users/fsjolander/Documents/JTH/VT_2022/Bachelor_Thesis/Applications/AMOCR-Bitmapizer/bin-img");
    
    // To which folder to save the resulting bmp files:
    string bmpPath = fs::path("/Users/fsjolander/Documents/JTH/VT_2022/Bachelor_Thesis/Applications/AMOCR-Bitmapizer/bmp-img");
    
    
    for (const auto &binFile : fs::directory_iterator(binPath)) {
        
        FileManager fm(binFile, bmpPath);
        
        fm.readBinaryData();
        uint8_t* bytes = fm.getBytes();
        
        Bitmap bmp(WIDTH, HEIGHT, fm.getFilesize(), 24, bytes);
        fm.setFilenameAppendix("-test");
                
        fm.writeBitmap(&bmp);
    }
    
    
    return 0;
}
