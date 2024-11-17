#pragma once 
#include <iostream>

namespace tsg
{
    enum NUMERIC_TYPE{
        DEC = 0,
        OCT = 1,
        HEX = 2
    };

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
            } else {
                std::cout << *str++;
            }
        }
    }

    void new_line();

    void numeric_mode(const NUMERIC_TYPE& type);

    class streamable {
    protected:     
        virtual const char* print() const = 0;
        friend std::ostream& operator<<(std::ostream& os, const streamable& s);
    };

    std::ostream& operator<<(std::ostream& os, const streamable& s){
        return os << s.print();;
    }
}