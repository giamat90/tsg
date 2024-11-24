#pragma once

#include <cstdint>

namespace tsg{
    using factorial_t = uint64_t;

    template <std::size_t N>
    inline factorial_t factorial(){
        return N * factorial<N-1>();
    }

    template<>
    inline factorial_t factorial<0u>(){
        return 1U;
    }

    inline factorial_t factorial(const int n){
        if(0 == n){
            return 1;
        } else {
            return n*factorial(n-1);
        }
    }

    
    using tartaglia_t = uint64_t;

    template<std::size_t N>
    inline void get_tartaglia_numbers(tartaglia_t values[N+1]){
        values[0] = 1;
        values[N] = 1;
        tartaglia_t previous[N];
        get_tartaglia_numbers<N-1>(previous);
        // for(int i = 0; i < N; ++i){
        //     std::cout << previous[i] << " ";
        // }
        // tsg::new_line();
        for(int i = 1; i < N; ++i){
            values[i] = previous[i] + previous[i-1]; 
        }
    }

    template<>
    inline void get_tartaglia_numbers<0U>(tartaglia_t values[1]){
            values[0] = 1;
    }

    template<>
    inline void get_tartaglia_numbers<1U>(tartaglia_t values[2]){
            values[0] = 1;
            values[1] = 1;
    }
}