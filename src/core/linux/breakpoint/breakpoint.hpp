#pragma once
#include <stdint.h>
#include "Logger.hpp"
#include "ptrace.hpp"
#include "linux/procfs/ProcMaps.hpp"
#include <unordered_map>


class Breakpoint {
public:
    Breakpoint(uint64_t offset) 
        : m_offset(offset) {}
    
    void set(pid_t pid);
    void unset(pid_t pid);
private:
    uint64_t m_offset;
    uint64_t original_word;
};