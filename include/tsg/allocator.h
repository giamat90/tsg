#pragma once

#include "memory_types.h"
#include "io.h"

using tsg::print;

namespace tsg{
    template <typename T>
    class placement_allocator {
    public:
        // using size_type = std::size_t;
        // using difference_type = std::ptrdiff_t;
        // using pointer = T*;
        // using const_pointer = const T*;
        // using reference = T&;
        // using const_reference = const T&;
        using value_type = T;   // mandatory
        
         template <typename U>
         struct rebind { using other = placement_allocator<U>;};

         template< class U>
         constexpr placement_allocator(const placement_allocator<U>& other) noexcept
         {
         }

         template <typename U>
         friend bool operator==(const placement_allocator<T>& a, const placement_allocator<U>& b)
         {
             return true;
         }
         template <typename U>
         friend bool operator!=(const placement_allocator<T>& a, const placement_allocator<U>& b)
         {
             return false;
         }

        placement_allocator(){
            print("tsg::allocator that handle memory in {}", m_memory_pool);
        };
        
        T* allocate(std::size_t size){
            print("tsg::allocator::allocate");
            return static_cast<T*>(::operator new(size + sizeof(T), m_memory_pool));
        }
        void deallocate(T* p, std::size_t size){
            print("tsg::allocator::deallocate");
            // delete p;
        }
    private:
        memory_chunck m_memory_pool[1024u]; // 64 bytes
    };
}