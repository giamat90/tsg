#include "../io/io.h"
#include <iostream>

class Object{
public:
    Object(){}
    ~Object(){}
private:
    friend std::ostream& operator<<(std::ostream& os, const Object& obj);
};

std::ostream& operator<<(std::ostream& os, const Object& obj){
    os << "Object " << &obj;
    return os;
}

class ObjectStreamable : public tsg::streamable {
public:
    ObjectStreamable() : streamable() {};
    ~ObjectStreamable(){};
private:
    print_output print() const override {
        return tsg::print("ObjectStreamable");
    }

};


int main(){
    Object obj;
    tsg::print(obj);

    ObjectStreamable objS;
    tsg::print(objS);

    return 0;
}