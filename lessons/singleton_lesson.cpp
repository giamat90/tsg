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
    B(const int b = 0) : m_b(b) {
        tsg::print("B c-tor {}", this);
    }
    ~B(){
        tsg::print("B d-tor {}", this);
    }
    void print(){
        tsg::print("print from {},{}", m_b, this);
    }
private:
    int m_b;
};

int& get_istance(){
    static int istance{42};
    return istance;
}

int main(){
    tsg::print("Hello World");
    tsg::new_line();

    tsg::print("### Mayer's singleton pattern: wrong ###");
    {
        int x = get_istance();
        auto y = get_istance();
        tsg::print("x = {}", x);
        tsg::print("y = {}", y);
        y = 21;
        tsg::print("x = {}", x);
        tsg::print("y = {}", y);
    }
    tsg::print("### ### #### ###");
    tsg::new_line();

    tsg::print("### Mayer's singleton pattern: correct ###");
    {
        int& x = get_istance();
        int& y = get_istance();
        tsg::print("x = {}", x);
        tsg::print("y = {}", y);
        y = 21;
        tsg::print("x = {}", x);
        tsg::print("y = {}", y);
    }
    tsg::print("### ### #### ###");
    tsg::new_line();

    // B myB = B::get_istance(42); // error: use of deleted function ‘B::B(const B&)’
    B& myB = B::get_istance(42);   // ok
    tsg::print("### Class singleton ###");
    {
        B::get_istance(42).print();
        B::get_istance().print();
        tsg::new_line();
        tsg::print("checkpoint");
        tsg::new_line();
        B::get_istance(21).print();
    }
    tsg::print("### ### #### ###");
    tsg::new_line();

    tsg::print("Goodbye");
    return 0;
}