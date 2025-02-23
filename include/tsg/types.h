#pragma once
#include <type_traits>

namespace tsg {

    template<typename T>
    class adapter {
    public:
        inline T* const get_adaptee() { return m_adaptee; }
        inline void set_adaptee(T* const a) { m_adaptee = a; }
    protected:
        T* m_adaptee{ nullptr };
    };

    class non_copyable {
    public:
        non_copyable() = default;
        ~non_copyable() = default;
        non_copyable(const non_copyable&) = delete;
        non_copyable& operator=(const non_copyable&) = delete;
    };

    class object {
    public:
        object() = default;
        ~object() = default;
    };

    template<typename T>
    class iterable_object {        
    public:
        class iterator {
        private:
           T* m_current{};
        public: // necessary aliases for use in stl algorithm            
            using value_type = T;
            using iterator_category = std::random_access_iterator_tag;  // the most generic one
            using reference = T&;
            using pointer = T*;
            using difference_type = ptrdiff_t;
        public: // ctors and dtors
            iterator(pointer pointer) : m_current(pointer) {};
            iterator(const iterator& other) {
                this->m_current = other.m_current;
            };
            iterator(iterator&& other) noexcept {
                this->m_current = other.m_current;
            };
        public: // methods            
            pointer base() const {
                return m_current; 
            }
        public: // operators
            iterator& operator=(const iterator& other) {
                this->m_current = other.m_current;
                return *this;
            }
            iterator& operator=(iterator&& other) noexcept {
                return *this;
            }
            bool operator==(const iterator& other) const {
                return other.m_current == m_current;
            };
            friend bool operator!=(const iterator& left, const iterator& right) {
                return left.m_current != right.m_current;
            }
            bool operator!=(const iterator& other) {
                return other.m_current != m_current;
            }
            // pre-increment
            iterator& operator++() {
                ++m_current;
                return *this;
            };
            // post-increment
            iterator operator++(int) {
                iterator tmp = m_current;
                ++m_current;
                return tmp;
            };
            // pre-decrement
            iterator& operator--() {
                --m_current;
                return *this;
            };
            // post-decrement
            iterator operator--(int) {
                iterator tmp = m_current;
                --m_current;
                return tmp;
            };
            value_type& operator*() const {
                return *m_current;
            }
            pointer operator->() const { 
                return m_current; 
            }
            difference_type operator+(const iterator& other) const {
                return m_current + other.m_current;
            }
            iterator operator+(difference_type diff) const {
                return iterator(m_current + diff);
            }
            iterator& operator+=(difference_type diff) {
                m_current += diff;
                return m_current;
            }
            difference_type operator-(const iterator& other) const {
                return m_current - other.m_current;
            }
            iterator operator-(difference_type diff) const {
                return iterator(m_current - diff);
            }
            iterator& operator-=(difference_type diff) const {
                m_current -= diff;
                return m_current;
            }
            bool operator<(const iterator& other){
                return this->base() < other.base();
            }
        };
    public:
        using tsg_iterator = iterable_object<T>::iterator;
        virtual tsg_iterator begin() = 0;
        virtual tsg_iterator end() = 0;
    };
};
