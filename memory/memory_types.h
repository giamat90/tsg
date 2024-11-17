#pragma once

#include <cstdint>

namespace tsg {
    using memory_chunck = char*;
    using buffer_size = std::size_t; 

    template <buffer_size S>
    class buffer{
    public:
        memory_chunck memory[S];
    };
}