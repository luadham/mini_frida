#pragma once
#include <sys/types.h>
#include <string>
#include <stdint.h>
#include <fstream>
#include <iostream>
#include "Logger.hpp"
#include <string_view>
#include <string>
#include <ranges>
#include <string.h>
#include <vector>
#include <sstream>

class ProcMaps {
public:
    ProcMaps(pid_t pid) 
        : m_pid{pid} {

        }
    uint64_t find_module_by_name(const std::string& name) const;
    uint64_t get_module_base_address() const;
private:
    pid_t m_pid;
    std::vector<std::string> split(const std::string& line) const;  
}; 