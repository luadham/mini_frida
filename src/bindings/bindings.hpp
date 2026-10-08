#pragma once

#include "helper.hpp"
#include "quickjs.h"
#include "ptrace.hpp"
#include <register.hpp>
#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <iostream>
#include <fstream>
#include "linux/procfs/ProcMaps.hpp"
#include "linux/breakpoint/breakpoint.hpp"
#include <sys/wait.h>
#include <signal.h>
#include <algorithm>
#include "register.hpp"

BINDING_FUN(js_print);
BINDING_FUN(js_pattach);
BINDING_FUN(js_get_registers);
BINDING_FUN(js_get_base_address);
BINDING_FUN(js_find_module);
BINDING_FUN(js_attach);
BINDING_FUN(js_change_register_value);