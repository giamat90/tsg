#pragma once 

#include <iostream>

namespace tsg
{
    enum NUMERIC_TYPE{
        DEC = 0,
        OCT = 1,
        HEX = 2
    }

    template <typename T>
    void print(const T& value){
        std::cout << value << std::endl;
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

    void new_line(){
        std::cout << std::endl;
    }

    void numeric_mode(const NUMERIC_TYPE& type){
        std::cout << type;
    }
}