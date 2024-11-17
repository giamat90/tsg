#include "../pattern/singleton.h"
#include "../io/io.h"

class Object {
public:
    Object(int x, int y, int z) : m_x(x), m_y(y), m_z(z){};
    ~Object(){};
    void print(){
        tsg::print("Hello from object {} x={} y={} z={}", this, m_x, m_y, m_z);
    }
private:
    int m_x{};
    int m_y{};
    int m_z{};
};

int main(){
    auto integer_istance = tsg::singleton::get_istance<int>(42);

    tsg::print(integer_istance);

    auto object_istance = tsg::singleton::get_istance<Object>(3, 1, 4);
    object_istance.print();

    return 0;
}