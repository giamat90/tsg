#include "../io/io.h"
#include <vector>

// custom allocator
template <typename T>
class my_allocator {
public:
    using value_type = T;   // mandatory
    my_allocator(){};
    ~my_allocator(){};
    
    T* allocate(std::size_t n){
        tsg::print("my_allocator::allocate n = {} for size = {}", n, n * sizeof(T));
        return static_cast<T*>(::operator new(n*sizeof(T)));
    }
    void deallocate(T* ptr, std::size_t n){
        tsg::print("my_allocator::deallocate n = {} for size = {}", n, n * sizeof(T));
        ::operator delete(ptr, n*sizeof(T));
    }

    template <typename U>
    friend bool operator==(const my_allocator<T>& a, const my_allocator<U>& b)
    {
        return true;
    }

    template <typename U>
    friend bool operator!=(const my_allocator<T>& a, const my_allocator<U>& b)
    {
        return false;
    }
};

// utility functions
template <typename C>
void printContainer(const C& container){
    for(std::size_t i = 0u; i < container.size(); ++i){
        tsg::print("vec[{}] = ({}, {})", i, &container[i], container[i]);
    }
}

template <typename E, typename C>
void addAndPrint(E el, C& container){
    container.emplace_back(el);
    printContainer(container);
}

int main(){
    tsg::print("Hello World");
    {   // container with integer example
        std::vector<int, my_allocator<int>> vec;

        tsg::print("### std::vector::emplace_back ###");
        addAndPrint(21, vec);
        addAndPrint(42, vec);
        addAndPrint(84, vec);
        tsg::new_line();

        tsg::print("### std::vector::shrink_to_fit ###");
        vec.shrink_to_fit(); // operator==, operator!=
        printContainer(vec);
        tsg::new_line();

        tsg::print("### std::vector::reserve ###");
        vec.reserve(100);
        printContainer(vec);
        vec.shrink_to_fit(); // operator==, operator!=
        tsg::new_line();
        
        tsg::print("### std::vector::pop_back ###");
        vec.pop_back();
        printContainer(vec);
        tsg::print("vec.capacity = {}", vec.capacity());
        tsg::new_line();
        
        tsg::print("### std::vector::insert ###");
        vec.insert(vec.begin(), 168);
        printContainer(vec);
        tsg::new_line();

        tsg::print("### std::vector::swap ###");
        std::vector<int, my_allocator<int>> other_vec;
        addAndPrint(616, other_vec);
        vec.swap(other_vec); // operator==, operator!=
        tsg::print("### ### other_vec ### ###");
        printContainer(other_vec);
        tsg::print("### ### vec ### ###");
        printContainer(vec);
        tsg::new_line();

        tsg::print("### std::vector::erase ###");
        other_vec.erase(other_vec.begin());
        other_vec.erase(other_vec.begin());
        printContainer(other_vec);
        tsg::new_line();

        tsg::print("vec.capacity = {}", vec.capacity());
        tsg::print("other_vec.capacity = {}", other_vec.capacity());
    }
    tsg::print("Goodbye");    
    return 0;
}
