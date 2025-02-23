#include "leak_detector.h"

#if 0
#include "io.h"
#include <cstdlib>  // malloc, free
#include <new>      // new and delete operators, std::bad_alloc

#include <stacktrace>
// #include <execinfo.h>
//using tsg::print;

void* operator new(std::size_t size){    
    // void* array[10];
    // int size_stack = backtrace(array, 10);
    // char** strings = backtrace_symbols(array, size_stack);
    // for(int i = 0; i < size_stack; ++i){
    //     print("{}\n", strings[i]);
    // }
    void* ptr = malloc(size);
    //std::cout << std::stacktrace::current() << '\n';

    tsg::leak_detector::get_leak_detector().addStackInfo(ptr, std::stacktrace::current());
    if(ptr){
        tsg::leak_detector::get_leak_detector().allocate(ptr, size);
        return ptr;
    } else {
        throw std::bad_alloc();
    }
}

void* operator new[](std::size_t size, const char* file, int line){
    void* ptr = malloc(size);
    std::cout << std::stacktrace::current() << '\n';
    tsg::leak_detector::get_leak_detector().addStackInfo(ptr, std::stacktrace::current());
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
        free(ptr);
    }
}

void operator delete(void* ptr){
    if(ptr){
        tsg::leak_detector::get_leak_detector().deallocate(ptr);
        free(ptr);
    }
}

void operator delete[](void* ptr, std::size_t size){
    if(ptr){
        tsg::leak_detector::get_leak_detector().deallocate(ptr, size);
        free(ptr);
    }
}

void operator delete[](void* ptr){
    if(ptr){
        tsg::leak_detector::get_leak_detector().deallocate(ptr);
        free(ptr);
    }
}


tsg::leak_detector::~leak_detector(){    
    print("Memory allocated = {} bytes\n", m_allocated_bytes);
    print("Num allocations = {}\n", m_num_allocation);
    print("Memory deallocated = {} bytes\n", m_deallocated_bytes);
    print("Num deallocations = {}\n", m_num_deallocation);
    print("Memory leaked = {} bytes\n", m_allocated_bytes - m_deallocated_bytes);
    print("Memory leaked = {} times\n", m_num_allocation - m_num_deallocation);
    for(std::size_t i = 0u; i < m_list_size; ++i){
        // if(m_allocation_list[i]){
        if(m_stack_info_list[i].pointer){
            // print("Address leaked = {}\n", m_allocation_list[i]);
            print("Address leaked = {}\n", m_stack_info_list[i].pointer);
            print("Stack info = {}\n", m_stack_info_list[i].stack_description);
        }
    }

}

#endif
