#pragma once

#include <cstdint>

#include "io.h"

namespace tsg{
    using factorial_t = uint64_t;

    template <size_t N>
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

    /* Computing N° tartaglia number */
    using tartaglia_t = uint64_t;

    template<size_t N>
    inline void get_tartaglia_numbers(tartaglia_t values[N+1]){
        values[0] = 1;
        values[N] = 1;
        tartaglia_t previous[N];
        get_tartaglia_numbers<N-1>(previous);
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
  
    template<typename T>
    inline constexpr T pow(const T base, const T exp){
        return exp > 0 ? base * pow(base, exp-1) : 1;
    }

    template <typename T, T M>
    class module {
    public:
        module(const T value) {
            if (value > M) {
                m_value += T(0);
            }
            if (value < 0) {
                m_value -= T(0);
            }
        }
        inline module<T,M>& operator+=(const module<T, M>& other) {
            m_value += other.m_value;
            if (m_value > M) {
                m_value -= M;
            }
        }
        inline friend module<T, M> operator+(module<T, M> lhs, const module<T, M>& rhs) {
            lhs += rhs;
            return lhs;
        }
        inline module<T, M>& operator-=(const module<T, M>& other) {
            m_value -= other.m_value;
            if (m_value < T(0)) {
                m_value = M - m_value;
            }
        }
        inline friend module<T, M> operator-(module<T, M> lhs, const module<T, M>& rhs) {
            lhs -= rhs;
            return lhs;
        }
    protected:
        T m_value;
    };

    template <typename T>
    class degree : public module<T, T(360)>{};

}