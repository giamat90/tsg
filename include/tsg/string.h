#pragma once 

#include "tsg.h"
#include <string>
#include <concepts>
#include <format>

namespace tsg {
    template <typename T>
    concept Stringable = requires(T v) {
        { std::to_string(v) } -> std::convertible_to<std::string>;
    };

    class string : public std::string {
    public:
        /* Default c-tor */
        string() : std::string() {};
        /* Naive c-tor */
        string(const std::string& s) : std::string(s) {};
         /* convert a pointer to a string as a number */
        template<typename T>
        string(T* ptr) : std::string(std::format("{:p}", static_cast<void*>(ptr))) {};
        /* convert a Stringable */
        template <Stringable T>
        string(const T v) : std::string(std::to_string(v)) {};            
        /* standard c-tor */
        string(const char* str) : std::string(str) {};
        /* variadic c-tor */
        template<typename T, typename ...Args>
        string(const char* str, const T& value, Args... args) {
            while (str && *str) {
                if (('{' == *str) && ('}' == *(str + 1))) {
                    *this += string(value);
                    *this += string(++(++str), args...);
                    str = nullptr; // end
                }
                else {
                    *this += *str++;
                }
            }
        }
    public:
        string& replace_c(const char old_c, const char new_c) {
            for (char& c : *this) {
                if (old_c == c) {
                    c = new_c;
                }
            }
            return *this;
        }
        string& replace_c(const std::initializer_list<char> list, const char new_c) {
            for (char& c : *this) {
                for (auto it = list.begin(); it != list.end(); ++it) {
                    if (c == *it) {
                        c = new_c;
                        break;
                    }
                }
            }
            return *this;
        }
    };
}

