#include "ptrace.hpp"

void 
attach(pid_t pid) {
    if (pid <= 0) {
        throw std::invalid_argument("[!] Must Supply Valid PID");
    }
    int ret = ptrace(PTRACE_ATTACH, pid, nullptr, nullptr);
    if (ret < 0) {
        throw std::runtime_error(std::format("[!] Can't Attach to PID = {} Error = {} ({})", pid, errno, strerror(errno)));
    }
    Logger::instance().info("Attached to PID = {}", pid);
    ptrace(PTRACE_SETOPTIONS, pid, nullptr, PTRACE_O_EXITKILL);
}

user_regs_struct
get_registers_values(pid_t pid) {
    user_regs_struct regs {};
    int ret = ptrace(PTRACE_GETREGS, pid, nullptr, &regs);
    if (ret < 0) {
        throw std::runtime_error(std::format("[!] Can't Get User Registers PID = {} Error {}", pid, strerror(errno)));
    }
    Logger::instance().info("Getting Registers for PID = {}", pid);
    return regs;
}

void 
continue_execution(pid_t pid) {
    if (pid <= 0) {
        throw std::invalid_argument("[!] Must Supply Valid PID");
    }
    int ret = ptrace(PTRACE_CONT, pid, nullptr, nullptr);
    if (ret < 0) {
        throw std::runtime_error(std::format("[!] Can't Continue to PID = {} Error = {} ({})", pid, errno, strerror(errno)));
    }
}

uint64_t
peek(pid_t pid, uint64_t address) {
    uint64_t word = ptrace(PTRACE_PEEKTEXT, pid, address, 0);
    if (word == 0xffull) {
        throw std::runtime_error(std::format("[!] Can't Peek to PID = {} Error = {} ({})", pid, errno, strerror(errno)));
    }
    return word;
}

void
poke(pid_t pid, uint64_t address, uint64_t word) {
    int ret = ptrace(PTRACE_POKETEXT, pid, address, word);
    if (ret < 0) {
        throw std::runtime_error(std::format("[!] Can't Poke to PID = {} Error = {} ({})", pid, errno, strerror(errno)));
    }
}

siginfo_t 
get_signal_info(uint64_t pid) {
    siginfo_t info;
    int ret = ptrace(PTRACE_GETSIGINFO, pid, nullptr, &info);
    if (ret < 0) {
        throw std::runtime_error(std::format("[!] Can't Get Signal to PID = {} Error = {} ({})", pid, errno, strerror(errno)));
    }
    return info;
}

void
update_registers(uint64_t pid, user_regs_struct& regs) {
    int ret = ptrace(PTRACE_SETREGS, pid, nullptr, &regs);
    if (ret < 0) {
        throw std::runtime_error(std::format("[!] Can't Update Registers to PID = {} Error = {} ({})", pid, errno, strerror(errno)));
    }
}