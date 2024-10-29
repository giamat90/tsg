#include <new>
#include <cstdlib>
#include <vector>

#include "io/io.h"

using tsg::io::print;

struct ICE {
    template <typename T>
    static constexpr bool is_ice(T v) {
        return true;
    };

    template <typename = std::enable_if<std::is_constant_evaluated(), int>>
    static constexpr bool is_ice(int& v){
        return false;
    }
};

int gx = ICE::is_ice(42);
int gy = ICE::is_ice(gx);

int main(){

    int x = ICE::is_ice(21);
    int y = ICE::is_ice(x);

    print("x {}\n", x);
    print("y {}\n", y);

    print("gx {}\n", gx);
    print("gy {}\n", gy);

    return 0;
}