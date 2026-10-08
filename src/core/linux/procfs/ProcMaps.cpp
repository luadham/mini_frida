#include "ProcMaps.hpp"

uint64_t 
ProcMaps::find_module_by_name(const std::string& module_name) const {
    std::ifstream maps {"/proc/" + std::to_string(m_pid) + "/maps"};
    Logger::instance().debug("/proc/" + std::to_string(m_pid) + "/maps");
    std::string line;
    uint64_t base_module_address = UINT64_MAX;
    while (std::getline(maps, line)) {
        std::vector<std::string> tokens = split(line);
        std::string full_address = tokens[0];
        std::string pathname = tokens.back();
        uint64_t start_address = std::stoull(full_address.substr(0, full_address.find("-")), nullptr, 16);
        if (pathname.find(module_name) != std::string::npos) {
            base_module_address = std::min(base_module_address, start_address);
        }
    }
    maps.close();
    return base_module_address;
}

uint64_t
ProcMaps::get_module_base_address() const {
    std::string maps = "/proc/" + std::to_string(m_pid) + "/maps";
    std::ifstream maps_f(maps);
    std::string address;
    std::getline(maps_f, address, '-');
    maps_f.close();
    return std::stoull(address, nullptr, 16);
}

std::vector<std::string> 
ProcMaps::split(const std::string& line) const {
    std::vector<std::string> tokens;
    std::istringstream stream { line };
    std::string token;
    while (stream >> token) {
        tokens.push_back(token);
    }
    return tokens; 
}