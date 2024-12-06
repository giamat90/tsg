#include "../io/io.h"


class Iterable {
    template<typename T>
    class iterator {
    private:
        T* ptr;
        size_t index;
        size_t count;
        Iterable* container;

    public:
        // Iterator traits required by STL
        using iterator_category = std::forward_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = T*;
        using reference = T&;

        Iterator(Iterable* buf, size_t idx, size_t cnt = 0) 
            : container(container), index(idx), count(cnt) {
            ptr = &container->data[index];
        }

        // Iterator operations
        reference operator*() { return *ptr; }
        pointer operator->() { return ptr; }

        Iterator& operator++() {
            count++;
            index = (index + 1) % buffer->capacity;
            ptr = &buffer->data[index];
            return *this;
        }

        Iterator operator++(int) {
            Iterator tmp = *this;
            ++(*this);
            return tmp;
        }

        bool operator==(const Iterator& other) const {
            return count == other.count;
        }

        bool operator!=(const Iterator& other) const {
            return count != other.count;
        }
    };
};

class Object : public Iterable {
public:
    Object(){};
    ~Object(){};
};

int main(){

    return 0;
}