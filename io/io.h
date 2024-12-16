#pragma once 

#include <iostream>
#include <bitset>

namespace tsg
{
    enum NUMERIC_TYPE{
        DEC = 0,
        OCT = 1,
        HEX = 2
    };
    
    using print_output = std::ostream&;

    template <typename T>
    void print_bit(const T& value){
        constexpr int size = sizeof(T)*sizeof(char);
        char bits[size];
        bits = reinterpret_cast<char*>(&value);
        std::cout << std::bitset<size>(bits) << std::endl;
    }

    template <typename T>
    print_output print(const T& value){
        return std::cout << value << std::endl;
    }

    template <typename T, typename ...Args>
    print_output print(const char* str, const T& value, Args... args){
        while(str && *str){
            if(('{' == *str) && ('}' == *(str + 1))){
                std::cout << value;
                return print(++(++str), args...);
            } else {
                std::cout << *str++;
            }
        }
        return std::cout;
    }

    void new_line() {
        std::cout << std::endl;
    };

    void numeric_mode(const NUMERIC_TYPE& type) {        
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

    void enable_boolean(const bool enable){
        if(enable){
            std::cout << std::boolalpha;
        } else {
            std::cout << std::noboolalpha;
        }
    }

    class streamable {
    protected:  
        virtual print_output print() const = 0;
        friend std::ostream& operator<<(std::ostream& os, const streamable& s);
    };

    std::ostream& operator<<(std::ostream& os, const streamable& s){
        return s.print();
    };
}