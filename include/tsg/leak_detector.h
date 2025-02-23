#pragma once

#if 0
#include "tsg.h"
#include <cstddef> 
#include <array>
#include <algorithm>
#include <string>

#include <stacktrace>


namespace tsg{    
    class TSG_API leak_detector {
    public:
        ~leak_detector();
        static leak_detector& get_leak_detector(){
            static leak_detector detector;
            return detector;    
        };
        void allocate(std::size_t bytes){ 
            m_allocated_bytes += bytes; 
            ++m_num_allocation;
        };
        void allocate(void* ptr, std::size_t bytes){
            // m_allocation_list[m_allocation_index++] = static_cast<int*>(ptr);
            m_allocated_bytes += bytes; 
            ++m_num_allocation;
        };
        void deallocate(void* ptr, std::size_t bytes){
            std::size_t index{};
            for(index = 0u; index < m_list_size; ++index){
                // if(m_allocation_list[index] == ptr){
                if(m_stack_info_list[index].pointer == ptr){
                    break;
                }
            }
            if(index < m_list_size){
                // m_allocation_list[index] = nullptr;
                m_stack_info_list[index].pointer = nullptr;                m_deallocated_bytes += bytes;
                ++m_num_deallocation;
            } 
        };
        void deallocate(std::size_t bytes){
            m_deallocated_bytes += bytes;
            ++m_num_deallocation;
        };
        void deallocate(void* ptr){
            std::size_t index{};
            for(index = 0u; index < m_list_size; ++index){
                // if(m_allocation_list[index] == ptr){
                if(m_stack_info_list[index].pointer == ptr){
                    break;
                }
            }
            if(index < m_list_size){
                // m_allocation_list[index] = nullptr;
                m_stack_info_list[index].pointer = nullptr;
                ++m_num_deallocation;
            } 
        };
        void deallocate(){ ++m_num_deallocation; };
        std::size_t get_allocated_bytes() const { return m_allocated_bytes; }
        std::size_t get_deallocated_bytes() const { return m_deallocated_bytes; }
        bool is_memory_leaked() { return m_allocated_bytes > m_deallocated_bytes; }
        std::size_t get_leaked_bytes() { return (m_allocated_bytes - m_deallocated_bytes); }
        void addStackInfo(void* ptr, const std::stacktrace& info){
            m_stack_info_list[m_allocation_index].pointer = ptr;
            m_stack_info_list[m_allocation_index].stack_description = info;
            ++m_allocation_index;
        }
    private:
        std::size_t m_allocated_bytes{};
        std::size_t m_deallocated_bytes{};
        std::size_t m_num_allocation{};
        std::size_t m_num_deallocation{};
    private:
        struct stack_info
        {
            using address = void*;
            using description = std::stacktrace;
            address pointer;
            description stack_description;
        };
        stack_info m_stack_info_list[0xffffff];
        const std::size_t m_list_size{0xffffff};
        std::size_t m_allocation_index{};
        // void* m_allocation_list[0xffffff];
        // char* m_allocation_list_string[0xffffff];
    };
}

#endif
