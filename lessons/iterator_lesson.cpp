#include "../io/io.h"

class Object {
    Object(){
        tsg::print("Object ctor {}", this);        
    }
    ~Object(){
        tsg::print("Object dtor {}". this);
    }    
    class Iterator {
        Iterator(){}
        Object* container;
        operator==();
        operator!=();
        operator++();
        operator--();
        
    };
    // Methods to get iterators
    Iterator begin() const { return Iterator(start_); }
    Iterator end() const { return Iterator(end_); }
};



int main(){
    tsg::print("Hello World");
    tsg::print("Goodbye");
    return 0;
}