#include "../io/io.h"
#include <iterator>
#include <algorithm>
#include <vector>

#include "../types.h"

template<typename T, std::size_t Size>
class Object : public tsg::streamable {
public:
    Object() {
        tsg::print("Object ctor {}", this);
    }
    ~Object() {
        tsg::print("Object dtor {}", this);
    }
    tsg::print_output print() const override {
        // tsg::print("cp1");
        for(std::size_t i = 0u; i < Size; ++i){
            tsg::print("data[{}] = ({}, {})", i, m_data[i], &m_data[i]);
        }
        tsg::print("cp2");
    }
    bool push_back(const T value) {
        if (m_index < Size) {
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
        using iterator_category = std::random_access_iterator_tag;
        using reference = v&;
        using pointer = v*;
        using difference_type = ptrdiff_t;
    public:
        Iterator(pointer pointer) : m_current(pointer) {};
        // copy ctor
        Iterator(const Iterator& other) {
            this->m_current = other.m_current;
        };
        // move ctor
        Iterator(Iterator&& other) noexcept {
            this->m_current = other.m_current;
        };
        pointer base() const {
            return m_current; 
        }
    public: // operators
        // assignment operator
        Iterator& operator=(const Iterator& other) {
            this->m_current = other.m_current;
            return *this;
        }
        // move-assignment operator
        Iterator& operator=(Iterator&& other) noexcept {
            return *this;
        }
        bool operator==(const Iterator& other) const {
            return other.m_current == m_current;
        };
        friend bool operator!=(const Iterator& left, const Iterator& right) {
            return left.m_current != right.m_current;
        }
        bool operator!=(const Iterator& other) {
            return other.m_current != m_current;
        }
        // pre-increment
        Iterator& operator++() {
            ++m_current;
            return *this;
        };
        // post-increment
        Iterator operator++(int) {
            Iterator tmp = m_current;
            ++m_current;
            return tmp;
        };
        // pre-decrement
        Iterator& operator--() {
            --m_current;
            return *this;
        };
        // post-decrement
        Iterator operator--(int) {
            Iterator tmp = m_current;
            --m_current;
            return tmp;
        };
        value_type& operator*() const {
            return *m_current;
        }
        pointer operator->() const { 
            return m_current; 
        }
        difference_type operator+(const Iterator& other) const {
            return m_current + other.m_current;
        }
        Iterator operator+(difference_type diff) const {
            return Iterator(m_current + diff);
        }
        Iterator& operator+=(difference_type diff) {
            m_current += diff;
            return m_current;
        }
        difference_type operator-(const Iterator& other) const {
            return m_current - other.m_current;
        }
        Iterator operator-(difference_type diff) const {
            return Iterator(m_current - diff);
        }
        Iterator& operator-=(difference_type diff) const {
            m_current -= diff;
            return m_current;
        }
        bool operator<(const Iterator& other){
            return this->base() < other.base();
        }
    };
    // Methods to get iterators
    Iterator<T> begin() { return Iterator<T>(m_data); }
    Iterator<T> end() { return Iterator<T>(m_data + m_index); }
private:
    T m_data[Size];
    std::size_t m_index{};
};

class Stuff : public tsg::iterable_object<int> {
public:
    tsg_iterator begin() { return tsg_iterator(m_data); }
    tsg_iterator end() { return tsg_iterator(m_data + 100); }
private:
    int m_data[100];
};

int main() {
    tsg::print("Hello World");
    
    Object<int, 10> obj;
    obj.push_back(42);
    tsg::print("obj.size() = {}", obj.size());
    obj.push_back(21);
    tsg::print("obj.size() = {}", obj.size());
    obj.push_back(168);
    tsg::print("obj.size() = {}", obj.size());
    obj.push_back(84);
    tsg::print("obj.size() = {}", obj.size());

    tsg::print(obj);

    // range-loop for
    tsg::print("range-for loop");
    for (auto& el : obj) {
        tsg::print("el = {}, &el = {}", el++, &el);
    }
    // for loop
    tsg::print("for loop");
    for (auto it = obj.begin(); it != obj.end(); ++it) {
        tsg::print("*it = {}, it = {}", *it, it.operator->());
        (*it)++;
        ++(*it);
    }

    // std::find
    tsg::print("searching for 42");
    auto it = std::find(obj.begin(), obj.end(), 42);
    if (it != obj.end()) {
        tsg::print("Element found!");
    }
    else {
        tsg::print("Element not found!");
    }

    tsg::enable_boolean(true);
    tsg::print("begin() < end() ? {}", obj.begin() < obj.end());
    tsg::print("begin() = {} < ++begin() = {} ? {}", *obj.begin(), *(obj.begin()+1), obj.begin() < (obj.begin()+1));

    // std::sort
    tsg::print("sorting");
    std::sort(obj.begin(), obj.end());
    for(auto it = obj.begin(); it != obj.end(); ++it){
        tsg::print("{}", *it);
    }

    tsg::print("stuff");
    Stuff s;
    int val = 0;
    tsg::print("range-for loop");
    for(auto& el : s){
        el = val++; 
    }

    tsg::print("for loop");
    for(auto el : s){
        tsg::print("el = {}, &el = {}", el, &el);
    }

    tsg::print("Goodbye");
    return 0;
}