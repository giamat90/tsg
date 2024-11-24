#pragma once
#include <type_traits>

namespace tsg {
    template <typename T, typename = std::enable_if_t<std::is_same<T, int>::value>>
    static constexpr bool is_ice(T v) {
        return true;
    };

    static constexpr bool is_ice(int& v){
        return false;
    }
};
