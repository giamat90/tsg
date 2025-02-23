#include "lesson.h"

#if POINTER_LESSON_ACTIVE

#include <iostream>

void lesson::run(){
    int v{42};
    std::cout << &v << std::endl; // address of v

    int * p{&v};
    std::cout << p << std::endl; // value of p

    // deferentiation
    *p = 21;
    std:: cout << v << std::endl;

    // nullptr
    if(p){
        std::cout << "p is a valid pointer" << std::endl;
        *p *= 2; // safe
    } else {
        std::cout << "p is an invalid pointer" << std::endl;
        *p *= 2; // unsafe
    }

    int * np{nullptr};
    //*np = v;    // crash!!!

    // pointer arithmetic 
    int v1{13};
    int v2{26};
    p = &v1;
    p--;
    *p = 0;
    std::cout << "v1 = " << v1 << std::endl;
    std::cout << "&v1 = " << &v1 << std::endl;
    std::cout << "v2 = " << v2 << std::endl;
    std::cout << "&v2 = " << &v2 << std::endl;

    // costant pointers
    int *const ccp{&v};
    // ccp = &w; // compiler error: assignment of read-only variable 'ccp'

}

#endif