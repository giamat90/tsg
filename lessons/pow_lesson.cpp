#include "lesson.h"

#if POW_LESSON_ACTIVE

#include <tsg/io.h>
#include <tsg/math.h>
#include <tsg/benchmark.h>

constexpr int base{ 2 };
constexpr int expn{ 30 };

int constexpr_res{};
int runtime_res{1};

void constexpr_calculation(){
    constexpr_res = tsg::pow(2, expn);
}

void runtime_calculation(int b, int e){
    for (std::size_t i = 0u; i < e; ++i){
        runtime_res *= b;
    }
}

void lesson::run() {
    tsg::print("Hello World");
    tsg::print("{}", tsg::pow(2, expn));
    tsg::print("Goodbye");
}

#endif