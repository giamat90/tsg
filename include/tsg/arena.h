#pragma once

#include "memory_types.h"

#include <new>
#include <cstdint>

namespace tsg{
    using arena_size = std::size_t;
    template <arena_size S = 64u>
    class arena {
    public:
        arena(){}
        ~arena(){}
        template<typename T>
        void* allocate(){
            constexpr std::size_t size{sizeof(T)};
            if(S < size + m_used){
                throw std::bad_alloc();
            } else {
                m_used += size;
                return static_cast<void*>(m_buffer + m_used);
            }
        }        
        void* allocate(std::size_t size){
            if(S < size + m_used){
                throw std::bad_alloc();
            } else {
                m_used += size;
                return reinterpret_cast<void*>(m_buffer + m_used);
            }
        }
        arena_size get_size() {return S;}
    private:
        memory_chunck m_buffer[S];
        std::size_t m_used{};
    };
}