#include "../io/io.h"
#include <vector>
#include <map>

static char buffer[64];

template <typename T>
class placement_allocator{
 public:
    using value_type = T;
    template <typename U>
    struct rebind { using other = placement_allocator<U>;};
    placement_allocator(){};
    ~placement_allocator(){};
    T* allocate(std::size_t size){
        tsg::print("my_allocator::allocate size = {}", size);
        return static_cast<T*>(::operator new(size*sizeof(T), buffer));
    }
    void deallocate(T* ptr, std::size_t size){
        tsg::print("my_allocator::deallocate");
        ptr->~T();
        ::operator delete(ptr, buffer);
    } 
private:
};

template <typename T>
class my_allocator {
public:
    using value_type = T;
    my_allocator(){};
    ~my_allocator(){};
    T* allocate(std::size_t size){
        tsg::print("my_allocator::allocate size = {}", size);
        return static_cast<T*>(::operator new(size*sizeof(T)));
    }
    void deallocate(T* ptr, std::size_t size){
        tsg::print("my_allocator::deallocate");
        ::operator delete(ptr);
    }
};

int main(){
    tsg::print("Hello World");
    {
        std::vector<int, my_allocator<int>> vec;
        vec.push_back(21);
        vec.push_back(42);
        vec.push_back(84);
        vec.push_back(168);
        vec.push_back(336);
        vec.push_back(672);
        for(auto v : vec){
            tsg::print("v in vec = {}", v);
        }
        vec.shrink_to_fit();
        vec.reserve(100);
    }
    {
        std::map<int,int, std::less<int>, my_allocator<std::pair<const int,int>>> map;
        map[0] = 21;
        map[1] = 42;
        map[2] = 84;
        map[3] = 168;
        tsg::print("Map size = {}", map.size());
        for(auto it = map.begin(); it != map.end(); ++it){
            tsg::print("it->first = {}, it->second = {}", it->first, it->second);
        }
        // for(auto p : map){
        //     tsg::print("p.first = {}, p.second = {}", p.first, p.second);
        // }
    }
    tsg::print("Goodbye");    
    return 0;
}
