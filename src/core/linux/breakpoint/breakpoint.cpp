#include "breakpoint.hpp"

void Breakpoint::set(pid_t pid) {
    ProcMaps maps { pid };
    uint64_t base = maps.get_module_base_address();
    uint64_t v_address = base + m_offset;
    Logger::instance().debug("Setting Break Point {:#x}", v_address);
    uint64_t word = peek(pid, v_address);
    original_word = word;
    uint64_t patched_instruction = (word & ~0xffULL) | 0xcc; 
    Logger::instance().debug("Current Word {:#x}", word);
    Logger::instance().debug("Patched Instruction {:#x}", patched_instruction);
    poke(pid, v_address, patched_instruction);
}

void Breakpoint::unset(pid_t pid) {
    Logger::instance().debug("Un Setting Break Point {:#x}", m_offset);
    ProcMaps maps { pid };
    uint64_t base = maps.get_module_base_address();
    uint64_t v_address = base + m_offset;
    Logger::instance().debug("Clear Break Point {:#x}", v_address);
    poke(pid, v_address, original_word);
    // Restore the PC 
    user_regs_struct regs = get_registers_values(pid);
    regs.rip -= 1;
    update_registers(pid, regs);
}