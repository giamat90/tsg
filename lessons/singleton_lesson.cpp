#include "lesson.h"

#if SINGLETON_LESSON_ACTIVE

#include <tsg/io.h>
#include <tsg/types.h>

// Object that should be a singleton
class A : public tsg::non_copyable {
public:
    A(int a) : m_a(a){};
    ~A(){};
    void print(){
        tsg::print("Hello from object {} a = {}", this, m_a);
    }
    void do_something(){
        ++m_a;
    }
private:
    int m_a{};
};


// Getting i singleton istance
A& get_istance(){
    static A istance{42};
    return istance;
}

void lesson::run(){
    tsg::print("Hello World");
    tsg::new_line();

    tsg::print("### Dangerous use of singleton ###");
    {
        // A x = get_istance();     // error: use of deleted function 'A::A(const A&)'
        // auto y = get_istance();  // error: use of deleted function 'A::A(const A&)'
        A& x = get_istance();       // ok
        A& y = get_istance();       // ok
        // print the state of our singletons
        x.print();
        y.print();
        // change the internal state of our singleton 
        y.do_something();
        // print again the state of our singleton
        x.print();
        y.print();
    }
    tsg::print("### ### #### ###");
    tsg::new_line();

    tsg::print("### Correct use of singleton ###");
    {
        A& x = get_istance();       // ok
        A& y = get_istance();       // ok
        // print the state of our singletons
        x.print();
        y.print();
        // change the internal state of our singleton 
        y.do_something();
        // print again the state of our singleton
        x.print();
        y.print();
    }
    tsg::print("### ### #### ###");
    tsg::new_line();

    tsg::print("Goodbye");
}

#endif