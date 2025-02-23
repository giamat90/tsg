#include "lesson.h"

#if OSTREAM_LESSON_ACTIVE

#include <tsg/io.h>
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
    tsg::print_output print() const override {
        return tsg::print("ObjectStreamable {}", this);
    }

};


void lesson::run(){
    Object obj;
    tsg::print(obj);

    ObjectStreamable objS;
    tsg::print(objS);
}

#endif