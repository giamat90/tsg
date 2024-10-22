#pragma once 

#include <iostream>

namespace tsg
{
    namespace io {
        template <typename T>
        void printf(const T& value){
            std::cout << value;
        }

        template <typename T, typename ...Args>
        void printf(const char* str, const T& value, Args... args){
            while(str && *str){
                if(('{' == *str) && ('}' == *(str + 1))){
                    std::cout << value;
                    return printf(++(++str), args...);
                } else if('\n' == *str) {
                    std::cout << std::endl;
                } else {
                    std::cout << *str++;
                }
            }
        }
    }
}