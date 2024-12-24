#include "../io/io.h"
#include <iterator>
#include <algorithm>

template<typename T, std::size_t Size>
class Object {
public:
    Object(){
        tsg::print("Object ctor {}", this);        
    }
    ~Object(){
        tsg::print("Object dtor {}", this);
    }    
    bool push_back(const T value){
        if(m_index < Size){
            m_data[m_index++] = value;
            return true;
        } 
        return false;
    }
    std::size_t size() const { return m_index; }
    template<typename v>
    class Iterator {
    private:
        v* m_current{};
    public: // necessary aliases for use in stl algorithm            
        using value_type = v;
        using iterator_category = std::bidirectional_iterator_tag;
        using reference = v&;
        using pointer = v*;
        using difference_type = ptrdiff_t;
    public:
        Iterator(pointer pointer) : m_current(pointer){};
        bool operator==(const Iterator& other) const { 
            return other.m_current == m_current; 
        };
        bool operator!=(const Iterator& other) {
            return other.m_current != m_current;
        }
        // pre-increment
        Iterator& operator++(){
            ++m_current;
            return *this;
        };
        // post-increment
        Iterator& operator++(int){
            Iterator tmp = m_current;
            ++m_current;
            return *tmp;
        };
        // pre-decrement
        Iterator& operator--(){
            --m_current;
            return *this;
        };
        // post-decrement
        Iterator& operator--(int){
            Iterator tmp = m_current;
            --m_current;
            return *tmp;
        };
        value_type operator*() const {
            return *m_current;
        }        
        // pointer opearator->() const {
        //     return m_current;
        // }
        // difference_type operator+(const Iterator& other) const {
        //     return m_current + other.m_current;
        // }
        // Iterator operator+(difference_type diff) const {
        //     return Iterator(m_current + diff);
        // }
        // Iterator& operator+=(difference_type diff) {
        //     m_current += diff;
        //     return m_current;
        // }
        // difference_type operator-(const Iterator& other) const {
        //     return m_current - other.m_current;
        // }
        // Iterator operator-(difference_type diff) const {
        //     return Iterator(m_current - diff);
        // }
        // Iterator& operator-=(difference_type diff) const {
        //     m_current -= diff;
        //     return m_current;
        // }
        // bool operator<(const Iterator& other){
        //     return *m_current < *other.m_current;
        // }
    };
    // Methods to get iterators
    Iterator<T> begin() { return Iterator<T>(m_data); }
    Iterator<T> end() { return Iterator<T>(m_data + m_index); }
private:
    T m_data[Size];
    std::size_t m_index{};
};



int main(){
    tsg::print("Hello World");
    tsg::print("Goodbye");
    Object<int, 10> obj;
    obj.push_back(42);
    tsg::print("obj.size() = {}", obj.size());
    obj.push_back(21);
    tsg::print("obj.size() = {}", obj.size());
    obj.push_back(168);
    tsg::print("obj.size() = {}", obj.size());
    obj.push_back(84);
    tsg::print("obj.size() = {}", obj.size());
    for(auto el : obj){
        tsg::print("{}", el);
    }
    for(auto it = obj.begin(); it != obj.end(); ++it){
        tsg::print("{}", *it);
    }

    auto it = std::find(obj.begin(), obj.end(), 42);
    if(it != obj.end()){
        tsg::print("Element found!");
    } else {
        tsg::print("Element not found!");
    }

    // std::sort(obj.begin(), obj.end());
    // for(auto it = obj.begin(); it != obj.end(); ++it){
    //     tsg::print("{}", *it);
    // }


    return 0;
}