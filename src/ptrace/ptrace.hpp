#pragma once

#include <sys/ptrace.h>
#include <sys/types.h>
#include <stdexcept>
#include <errno.h>
#include <format>
#include <string.h>
#include <iostream>
#include <sys/user.h>
#include "../Logger/Logger.hpp"
#include <signal.h>

void attach(pid_t pid);

user_regs_struct
get_registers_values(pid_t pid);

void 
continue_execution(pid_t pid);


uint64_t
peek(pid_t pid, uint64_t address);

siginfo_t 
get_signal_info(uint64_t pid);

void
poke(pid_t pid, uint64_t address, uint64_t word);


void
update_registers(uint64_t pid, user_regs_struct& regs);