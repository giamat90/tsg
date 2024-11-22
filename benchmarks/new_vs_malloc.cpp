#include "../test/benchmark.h"
#include "../io/io.h"
#include <cstdlib>

void new_test(const std::size_t  times){
    for(std::size_t i = 0u; i < times; ++i){
        int* tmp = new int{};
        delete tmp;
    }
}

void new_array_test(const std::size_t size){
    // int* tmp = new int[size]{};
    int* tmp = static_cast<int*>(::operator new[](size * sizeof(int)));
    delete[] tmp;    
}

void malloc_test(const std::size_t  times){
    for(std::size_t i = 0u; i < times; ++i){
        int* tmp = static_cast<int*>(std::malloc(sizeof(int)));
        std::free(tmp);
    }
}

void malloc_array_test(const std::size_t size){
    int* tmp = static_cast<int*>(std::calloc(size, sizeof(int)));
    std::free(tmp);
}

int main(){
    tsg::print("Hello World");

#ifdef SCALAR
    constexpr std::size_t times = 1'000'000'000u;
    double new_res = tsg::get_execution_time<double>(new_test, times);
    tsg::print("New result = {}", new_res);
    double malloc_res = tsg::get_execution_time<double>(malloc_test, times);
    tsg::print("Malloc result = {}", malloc_res);
    tsg::print("New(t)/Malloc(t) = {}", new_res / malloc_res);
#endif

#ifdef ARRAY
    constexpr std::size_t size = 1'000'000'000u;
    double new_array_res = tsg::get_execution_time<double>(new_array_test, size);
    tsg::print("New-array result = {}", new_array_res);
    double malloc_array_res = tsg::get_execution_time<double>(malloc_array_test, size);
    tsg::print("Malloc-array result = {}", malloc_array_res);
    tsg::print("New(t)/Malloc(t) = {}", new_array_res / malloc_array_res);
#endif

    tsg::print("Goodbye");
    return 0;
}