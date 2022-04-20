#include "lib/functions.h"

constexpr int BITMAPIZE = 1;
constexpr int CONVERT = 2;


int main(int argc, const char * argv[]) {
    
    string arg = "";
    
    if (argc > 1) {
        arg = argv[1];
    }
    
    //arg = "-convert";
    
    int action = 0;
    
    if (arg == "-bitmapize") {
        action = BITMAPIZE;
    } else if (arg == "-convert") {
        action = CONVERT;
    }
        
    switch (action) {
            
        case BITMAPIZE:
            
            bitmapize();
            
            break;
            
        
        case CONVERT:
            
            convert();
            
            break;
            
        
        default:
        
            break;
    }
    return 0;
}
