#pragma one

#include <cstddef> 

namespace tsg{
    class leak_detector {
    public:
    ~leak_detector();
    static leak_detector& get_leak_detector(){
        static leak_detector detector;
        return detector;    
    }
        void allocate(std::size_t bytes){ m_allocated_bytes += bytes; };
        void deallocate(std::size_t bytes){m_deallocated_bytes += bytes; };
        std::size_t get_allocated_bytes() const { return m_allocated_bytes; }
        std::size_t get_deallocated_bytes() const { return m_deallocated_bytes; }
        bool is_memory_leaked() { return m_allocated_bytes > m_deallocated_bytes; }
        std::size_t get_leaked_bytes() { return (m_allocated_bytes - m_deallocated_bytes); }
    private:
        std::size_t m_allocated_bytes{};
        std::size_t m_deallocated_bytes{};
    };
}