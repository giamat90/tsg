#include "../pattern/singleton.h"
#include "../io/io.h"

class A {
public:
    A(int a) : m_a(a){};
    ~A(){};
    void print(){
        tsg::print("Hello from object {} a = {}", this, m_a);
    }
private:
    int m_a{};
};

class B : public tsg::singleton<B> {
public:
    B(int b) : m_b(b) {
        tsg::print("B c-tor {}", this);
    }
    ~B(){
        tsg::print("B d-tor {}", this);
    }
private:
    int m_b;
};

int main(){
    // auto integer_istance = tsg::get_istance<int>(42);

    // tsg::print(integer_istance);

    // auto object_istance = tsg::get_istance<Object>(3, 1, 4);
    // object_istance.print();

    B myB = tsg::singleton<B>::get_istance(42);

    return 0;
}