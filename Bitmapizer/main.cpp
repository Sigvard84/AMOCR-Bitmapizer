#include <filesystem>
#include <vector>
#include <string>
#include "Bitmap.hpp"
#include "FileManager.hpp"

constexpr int WIDTH = 800;
constexpr int HEIGHT = 600;
constexpr int RGB888 = 24;

namespace fs = std::filesystem;
using namespace std;


int main(int argc, const char * argv[]) {
    
    // From which file to open test bmp:
    string bmpPath = fs::path("/Users/fsjolander/Documents/JTH/VT_2022/Bachelor_Thesis/Applications/AMOCR-desktop/bmp_images/grayscale/cropped/picture231.bmp");
    
    // From which folder to open the binary files:
    string srcPath = fs::path("/Users/fsjolander/Documents/JTH/VT_2022/Bachelor_Thesis/Applications/AMOCR-Bitmapizer/bin-img");
    
    // To which folder to save the resulting bmp files:
    string destinationPath = fs::path("/Users/fsjolander/Documents/JTH/VT_2022/Bachelor_Thesis/Applications/AMOCR-Bitmapizer/bmp-img");
    
    
//    for (const auto &srcFile : fs::directory_iterator(srcPath)) {
//
//        FileManager fm(srcFile, destinationPath);
//
//        fm.readBinaryData();
//        uint8_t* bytes = fm.getBytes();
//
//        Bitmap bmp(WIDTH, HEIGHT, fm.getFilesize(), RGB888, bytes);
//        fm.setFilenameAppendix("-test");
//
//        fm.writeBitmap(bmp.m_header, bmp.m_headerSize, bmp.m_pxData, bmp.m_byteLength);
//    }
    
    Bitmap bmp2(bmpPath);
    FileManager fm2(bmpPath, destinationPath);
    
    fm2.setFilenameAppendix("_2bit_139");
    bmp2.convertFrom8To2Bit();
    fm2.writeBitmap(bmp2.m_header, bmp2.m_headerSize, bmp2.m_pxData, bmp2.m_byteLength);
    
    
    return 0;
}
