#include "lesson.h"

#if TARTAGLIA_LESSON_ACTIVE

#include <tsg/io.h>
#include <tsg/benchmark.h>
#include <tsg/math.h>

template <std::size_t N>
void print_tartaglia_numbers(tsg::tartaglia_t numbers[N+1]){
    for(int i = 0; i < N + 1; ++i){
        std::cout << numbers[i] << " ";
    }
    tsg::new_line();    
}

template <typename T>
constexpr int find_max_tartaglia_degree(){
    // tsg::enable_boolean(true);
    int n = 0;
    // constexpr T max = std::numeric_limits<T>::max();
    constexpr int max = std::numeric_limits<int>::max();
    tsg::factorial_t max_factor{}; 
    while(max_factor < max){
        auto num = tsg::factorial(n);
        auto den = tsg::factorial(n/2)*tsg::factorial(n - n/2);
        max_factor = num / den;
        ++n;
        // tsg::print("n = {}, factor = {}, num = {}, den = {}", n, max_factor, num, den);
        tsg::print("n = {}, max = {}, max_factor = {}\n", n, max, max_factor);
    }
    return --n;
}

void lesson::run(){
    tsg::print("Hello World");

    // tsg::print("max uint8_t = {}", find_max_tartaglia_degree<uint8_t>());
    // tsg::print("max uint16_t = {}", find_max_tartaglia_degree<uint16_t>());
    auto max = find_max_tartaglia_degree<int>();
    tsg::print("max uint16_t = {}", max);
    // tsg::print("max uint32_t = {}", find_max_tartaglia_degree<uint32_t>());
    // tsg::print("max uint64_t = {}", find_max_tartaglia_degree<uint64_t>());
    {
        // massimo N per cui sono riuscito a calcolare sulla mia macchina è 712 ma con integer overflow.
        // massimo N per cui sono riuscito a calcolare senza integer overflow è 57 
        // 57 è calcolabile come il max N tale che N!/K!(N-K)! sia più piccolo di 2^b dove b è 
        // il numero di bit con cui si rappresenta il calcolo.        
        constexpr int N{57};
        uint64_t values[N+1];        
        auto start = std::chrono::high_resolution_clock::now();
        auto time = tsg::get_execution_time<double>(tsg::get_tartaglia_numbers<N>, values);   // too time        
        auto end = std::chrono::high_resolution_clock::now();
        print_tartaglia_numbers<N>(values);
        tsg::print("execution time for tartaglia number {}: {}s", N, time);
    }

    {
        // constexpr std::size_t degree{3};
        // int numbers[degree+1];
        // auto values = get_tartaglia_values(degree, numbers);
        // for(std::size_t i = 0u; i < degree+1; ++i){
        //     std::cout << values[i] << " ";
        // }
        // tsg::new_line();
    }

    {
        // constexpr std::size_t n{20}; // 20 is the maximum befor have a uint64_t overflow
        // uint64_t fact_n{};
        // float time = tsg::get_execution_time<float>(tsg::factorial<n>, fact_n);
        // tsg::print("{}! = {}, execution time = {}", n, fact_n, time);
    }

    tsg::new_line();
    tsg::print("Goodbye");
}

#endif