#pragma once 

#include <iostream>

namespace tsg
{
    namespace io {
        template <typename T>
        void print(const T& value){
            std::cout << value;
        }

        template <typename T, typename ...Args>
        void print(const char* str, const T& value, Args... args){
            while(str && *str){
                if(('{' == *str) && ('}' == *(str + 1))){
                    std::cout << value;
                    return print(++(++str), args...);
                } else if('\n' == *str) {
                    std::cout << std::endl;
                } else {
                    std::cout << *str++;
                }
            }
        }
    }
}