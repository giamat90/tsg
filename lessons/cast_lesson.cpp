#include "../io/io.h"


class Obj1 {
public:
    Obj1(){};
    explicit Obj1(Obj2 other){};
    ~Obj1(){};
    void print(){
        tsg::print("Hello from Obj1");
    }
};

class Obj2 {
public:
    Obj2(){};
    explicit Obj2(Obj1 other){};
    ~Obj2(){};
    void print(){
        tsg::print("Hello from Obj2");
    }
};


int main(){

    {
        Obj2 obj2;
        Obj1 obj1 = static_cast<Obj1>(obj2);
    }
    {
        Obj1 obj1;
        Obj2 obj2 = static_cast<Obj2>(obj1);
    }
    {
        char* c;
        // int* p = c;                          // error
        int* p = (int*)c;                       // ok
        // int* p = static_cast<int*>(c);       // error
    }



    return 0;
}