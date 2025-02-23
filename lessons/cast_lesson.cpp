#include "lesson.h"

#if CAST_LESSON_ACTIVE

#include <tsg/io.h>


class Base
{
public:
    Base() {};
    ~Base() {};
    virtual void print()
    {
        tsg::print("Hello from Base");
    }
};

class Derived1 : public Base
{
public:
    Derived1() {};
    ~Derived1() {};
    void print() override
    {
        tsg::print("Hello from Derived1");
    }
    void derived1_stuff()
    {
        tsg::print("Derived1 stuff {}", m_y);
    }

private:
    const int m_y{21};
};

class Derived2 : public Base
{
public:
    Derived2() {};
    explicit Derived2(Derived1 other)
    {
        tsg::print("Derived2 conversion from Derived1");
    };
    ~Derived2() {};
    void print() override
    {
        tsg::print("Hello from Derived2");
    }
    void derived2_stuff()
    {
        tsg::print("Derived2 stuff {}", m_x);
    };

private:
    int m_x{42};
};

class Derived3 : public Derived2
{
public:
    Derived3() {};
    ~Derived3() {};
};

void lesson::run()
{
    tsg::print("Hello World");
    tsg::new_line();

    tsg::print("### static cast ###");
    {
        float f_pi = 3.14;
        int i_pi = (int)f_pi;
        tsg::print(i_pi);
        char *c;
        // int* p = static_cast<int*>(c);       // error: invalid 'static_cast' from type 'char*' to type 'int*'
        int *p = (int *)c; // ok
        Derived1 d1;
        d1.print();
        Derived2 d2 = static_cast<Derived2>(d1); // ok, Derived2 has an explicit c-tor for Derived1 type
        d2.print();
        // Derived1 dd1 = static_cast<Derived1>(d2);       // error: no matching function for call to 'Derived1::Derived1(Derived2&)
    }
    tsg::print("### ### ### ### ###");
    tsg::new_line();

    tsg::print("### reinterpret cast ###");
    {
        float pi = 3.14;
        int x = *reinterpret_cast<int *>(&pi);
        tsg::print(x);
        float tmp = *reinterpret_cast<float *>(&x);
        tsg::print(tmp);
    }
    tsg::print("### ### ### ### ###");    
    tsg::new_line();

    tsg::print("### const cast ###");
    {
        const int value{42};
        tsg::print(value);
        // value = 21;                      // error: assignment of read-only variable 'value'
        (*const_cast<int *>(&value)) = 21;
        tsg::print(value);
    }
    tsg::print("### ### ### ### ###");
    tsg::new_line();

    tsg::print("### dynamic cast ###");
    {
        Base *obj = new Derived2;
        obj->print();                                   // Derived2::print
        static_cast<Derived1 *>(obj)->derived1_stuff(); // Ok but dangerous!
        if (auto p = dynamic_cast<Derived2 *>(obj))
        {
            p->derived2_stuff();
        }
        if (auto p = dynamic_cast<Derived1 *>(obj))
        {
            p->derived1_stuff();
        }
        delete obj;
    }
    tsg::print("### ### ### ### ###");
    tsg::new_line();

    tsg::print("Goodbye!");
}

#endif