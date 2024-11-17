#include "io.h"

namespace tsg{
    void new_line(){
        std::cout << std::endl;
    }

    void numeric_mode(const NUMERIC_TYPE& type){
        switch (type)
        {
        case NUMERIC_TYPE::DEC:
            std::cout << std::dec;
            break;
        case NUMERIC_TYPE::OCT:
            std::cout << std::oct;
            break;
        case NUMERIC_TYPE::HEX:
            std::cout << std::hex;
            break;        
        default:
            break;
        }
    }
}