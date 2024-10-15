#include "test/benchmark.h"
#include "io/io.h"

using tsg::io::printf;
using tsg::test::do_benchmark;

void foo(int x){
    for(int i = 0; i < x; ++i);
}

int main(){
    printf("Hello World {}", 616);

    auto time = do_benchmark<int>(foo, 100000000000);
    printf("Time elapsed = {}s", time);

    printf("Goodbye");
    return 0;
}