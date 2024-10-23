#include "io/io.h"
// #include "memory/leak_detector.h"

#include <new>
#include <cstdlib>

#include <vector>

using tsg::io::printf;


// void* operator new(std::size_t size){
//     void* ptr = malloc(size);
//     printf("Allocating {}bytes of memory on address {}", size, ptr);
//     return ptr;
// }

// void operator delete(void* ptr, std::size_t size){
//     printf("Deallocating memory in address {} for bytes {}", ptr, size);
//     free(ptr);
// }

// void* operator new[](std::size_t size){
//     void* ptr = malloc(size);
//     printf("Allocating array for {}bytes on address {}", size, ptr);
//     return ptr;
// }

// void operator delete[](void* ptr){
//     printf("Deallocating array in address {}", ptr);
//     free(ptr);
// }

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

int main(){
    printf("Hello World\n");

    int* p = new int{};
    int* q = new int{};
    int* r = new int{};


    printf("p = {}\n", p);
    printf("q = {}\n", q);
    printf("r = {}\n", r);

    delete r;

    printf("Goodbye\n");
    return 0;
}