#include "leak_detector.h"

#include <cstdlib>  // malloc, free
#include <new>      // new and delete operators, std::bad_alloc
#include "../io/io.h"  // printf

using tsg::io::printf;

void* operator new(std::size_t size){
    void* ptr = std::malloc(size);
    if(ptr){
        tsg::leak_detector::get_leak_detector().allocate(size);
        return ptr;
    } else {
        throw std::bad_alloc();
    }
}

void* operator new[](std::size_t size){
    void* ptr = std::malloc(size);
    if(ptr){
        tsg::leak_detector::get_leak_detector().allocate(size);
        return ptr;
    } else {
        throw std::bad_alloc();
    }
}

void operator delete(void* ptr, std::size_t size){
    if(ptr){
        tsg::leak_detector::get_leak_detector().tsg::leak_detector::get_leak_detector().deallocate(size);
        std::free(ptr);
    }
}

void operator delete[](void* ptr, std::size_t size){
    if(ptr){
        tsg::leak_detector::get_leak_detector().deallocate(size);
        std::free(ptr);
    }
}

tsg::leak_detector::~leak_detector(){    
    printf("Memory allocated = {}", m_allocated_bytes);
    printf("Memory deallocated = {}", m_deallocated_bytes);
    printf("Memory leaked = {}", m_allocated_bytes - m_deallocated_bytes);
}