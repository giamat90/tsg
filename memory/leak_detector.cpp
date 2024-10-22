#include "leak_detector.h"

#include "../io/io.h"
#include <cstdlib>  // malloc, free
#include <new>      // new and delete operators, std::bad_alloc

using tsg::io::printf;

void* operator new(std::size_t size){
    void* ptr = std::malloc(size);
    if(ptr){
        tsg::leak_detector::get_leak_detector().allocate(ptr, size);
        return ptr;
    } else {
        throw std::bad_alloc();
    }
}

void* operator new[](std::size_t size){
    void* ptr = std::malloc(size);
    if(ptr){
        tsg::leak_detector::get_leak_detector().allocate(ptr, size);
        return ptr;
    } else {
        throw std::bad_alloc();
    }
}

void operator delete(void* ptr, std::size_t size){
    if(ptr){
        tsg::leak_detector::get_leak_detector().deallocate(ptr, size);
        std::free(ptr);
    }
}

void operator delete(void* ptr){
    if(ptr){
        tsg::leak_detector::get_leak_detector().deallocate(ptr);
        std::free(ptr);
    }
}

void operator delete[](void* ptr, std::size_t size){
    if(ptr){
        tsg::leak_detector::get_leak_detector().deallocate(ptr, size);
        std::free(ptr);
    }
}

void operator delete[](void* ptr){
    if(ptr){
        tsg::leak_detector::get_leak_detector().deallocate(ptr);
        std::free(ptr);
    }
}


tsg::leak_detector::~leak_detector(){    
    printf("Memory allocated = {} bytes\n", m_allocated_bytes);
    printf("Num allocations = {}\n", m_num_allocation);
    printf("Memory deallocated = {} bytes\n", m_deallocated_bytes);
    printf("Num deallocations = {}\n", m_num_deallocation);
    printf("Memory leaked = {} bytes\n", m_allocated_bytes - m_deallocated_bytes);
    printf("Memory leaked = {} times\n", m_num_allocation - m_num_deallocation);
    for(std::size_t i = 0u; i < m_list_size; ++i){
        if(m_allocation_list[i]){
            printf("Address leaked = {}\n", m_allocation_list[i]);
        }
    }

}
