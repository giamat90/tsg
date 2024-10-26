#include "io/io.h"
// #include "memory/leak_detector.h"

#include <new>
#include <cstdlib>
#include <stacktrace>
#include <vector>

using tsg::io::printf;

void consume_memory(){
    try{
        std::vector<int> vec;
        for(;;){
            vec.push_back(42);
        }        
    } catch(std::exception& e){
        printf("Exception catched {}", e.what());
    }
}

void foo(){
    
    std::cout << std::stacktrace::current() << '\n';
}

int main(){
    printf("Hello World\n");

    // int* p = new int{};
    // int* q = new int{};
    // int* r = new int{};

    foo();

    // printf("p = {}\n", p);
    // printf("q = {}\n", q);
    // printf("r = {}\n", r);

    // delete r;

    printf("Goodbye\n");
    return 0;
}