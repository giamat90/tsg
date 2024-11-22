#include "../io/io.h"
#include "../test/benchmark.h"

int* get_tartaglia_values(const std::size_t size, int * values){
    tsg::print("size = {}", size);
    if(0u == size){
        tsg::print("Case 0");
        values[0u] = 1u;
    } else if (1u == size) {
        tsg::print("Case 1");
        values[0u] = 1u;
        values[1u] = 1u;
    } else {
        tsg::print("Else case size = {}", size);
        values[0u] = 1u;
        values[size] = 1u;
        for(std::size_t i = 1u; i < size - 1u; ++i){
            tsg::print("calling {} case to compute {} value", size-1u, i);
            int * previous = get_tartaglia_values(size - 1u, values);
            values[i] = previous[i] + previous[i-1];
            tsg::print("values[{}] = {}", i, values[i]);
        }
    }
    tsg::print("ending");
    return values;
}

template<std::size_t N>
int* get_tartaglia_number(int values[N+1]){
    values[0] = 1;
    values[N] = 1;
    for(int i = 1; i < N; ++i){
        int previous[N];
        get_tartaglia_number<N-1>(previous);
        values[i] = previous[i] + previous[i-1]; 
    }
    tsg::print("Done step N = {}", N);
    return values;
}


template<>
int* get_tartaglia_number<0U>(int values[1]){
        values[0] = 1;
        return values;
}

template<>
int* get_tartaglia_number<1U>(int values[2]){
        values[0] = 1;
        values[1] = 1;
        return values;
}

template <std::size_t N>
void print_tartaglia_numbers(){
    constexpr std::size_t degree{N};
    int numbers[degree+1];
    auto values = get_tartaglia_number<degree>(numbers);
    for(std::size_t i = 0u; i < degree+1 / 2; ++i){
        std::cout << values[i] << " ";
    }
    tsg::new_line();
}

template <std::size_t N>
int factorial(){
    return N * factorial<N-1>();
}

template<>
int factorial<0u>(){
    return 1U;
}

int main(){
    tsg::print("Hello World");
    {
        print_tartaglia_numbers<50>();
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
        constexpr std::size_t n{15};
        int fact_n{};
        float time = tsg::get_execution_time<float>(factorial<n>, fact_n);
        tsg::print("{}! = {}, execution time = {}", n, fact_n, time);
    }

    tsg::new_line();
    tsg::print("Goodbye");
    return 0;
}