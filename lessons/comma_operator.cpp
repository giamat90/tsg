#include "lesson.h"

#if COMMA_OPERATOR_ACTIVE

#include <tsg/io.h>

void foo(int x){
    tsg::print("foo call {}", x);
}

void bar(int& x){
    tsg::print("bar call {}", ++x);
}

void lesson::run(){
    int value{42};

    // (foo(value), bar(value));
    
    tsg::print("{}", value);
    tsg::enable_boolean();

    bool res = (foo(value), value) > 42 ? true : false;
    tsg::print(res);
}

#endif