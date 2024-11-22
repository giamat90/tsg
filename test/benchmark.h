#pragma once

#include <chrono>

namespace tsg{
    using time_t = float;
    using long_time_t = double;
    template <typename T, typename U, typename Fnc, typename ...Args>
    T get_execution_time(Fnc fun, U& output, Args... args){
        static_assert(std::is_invocable_v<Fnc, Args...>);
        static_assert(std::is_floating_point_v<T>);
        auto start = std::chrono::high_resolution_clock::now();
        output = fun(args...);
        auto end = std::chrono::high_resolution_clock::now();
        return std::chrono::duration<T>(end - start).count();
    }
    template <typename T, typename Fnc, typename ...Args>
    T get_execution_time(Fnc fun, Args... args){
        static_assert(std::is_invocable_v<Fnc, Args...>);
        static_assert(std::is_floating_point_v<T>);
        auto start = std::chrono::high_resolution_clock::now();
        fun(args...);
        auto end = std::chrono::high_resolution_clock::now();
        return std::chrono::duration<T>(end - start).count();
    }
}