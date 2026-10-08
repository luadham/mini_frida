#pragma once

#include <array>
#include <cstddef>

struct Register {
    const char* name;
    std::size_t offset;
};


extern const std::array<Register, 27> g_registers;