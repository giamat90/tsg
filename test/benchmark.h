#pragma once

#include <chrono>

namespace tsg{
    namespace test{
        template <typename T, typename Fnc, typename ...Args>
        T do_benchmark(Fnc fun, Args... args){
            static_assert(std::is_invocable_v<Fnc, Args...>);
            static_assert(std::is_floating_point_v<T>);
            auto start = std::chrono::high_resolution_clock::now();
            fun(args...);
            auto end = std::chrono::high_resolution_clock::now();
            return std::chrono::duration<T>(end - start).count();
        }
    }
}