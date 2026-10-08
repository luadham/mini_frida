#include <array>
#include <stdint.h>
#include <cstddef>
#include <sys/user.h>
#include "register.hpp"

constexpr std::array<Register, 27> g_registers{{
    {"r15",    offsetof(user_regs_struct, r15)},
    {"r14",    offsetof(user_regs_struct, r14)},
    {"r13",    offsetof(user_regs_struct, r13)},
    {"r12",    offsetof(user_regs_struct, r12)},
    {"rbp",    offsetof(user_regs_struct, rbp)},
    {"rbx",    offsetof(user_regs_struct, rbx)},
    {"r11",    offsetof(user_regs_struct, r11)},
    {"r10",    offsetof(user_regs_struct, r10)},
    {"r9",     offsetof(user_regs_struct, r9)},
    {"r8",     offsetof(user_regs_struct, r8)},
    {"rax",    offsetof(user_regs_struct, rax)},
    {"rcx",    offsetof(user_regs_struct, rcx)},
    {"rdx",    offsetof(user_regs_struct, rdx)},
    {"rsi",    offsetof(user_regs_struct, rsi)},
    {"rdi",    offsetof(user_regs_struct, rdi)},
    {"orig_rax", offsetof(user_regs_struct, orig_rax)},
    {"rip",    offsetof(user_regs_struct, rip)},
    {"cs",     offsetof(user_regs_struct, cs)},
    {"eflags", offsetof(user_regs_struct, eflags)},
    {"rsp",    offsetof(user_regs_struct, rsp)},
    {"ss",     offsetof(user_regs_struct, ss)},
    {"fs_base", offsetof(user_regs_struct, fs_base)},
    {"gs_base", offsetof(user_regs_struct, gs_base)},
    {"ds",     offsetof(user_regs_struct, ds)},
    {"es",     offsetof(user_regs_struct, es)},
    {"fs",     offsetof(user_regs_struct, fs)},
    {"gs",     offsetof(user_regs_struct, gs)},
}};