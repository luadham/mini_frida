#include <iostream>
#include <unistd.h>
#include "quickjs.h"
#include "JSEngine/JSEngine.hpp"
#include "bindings/bindings.hpp"
#include <sstream>
#include <fstream>
#include "Logger/Logger.hpp"
#include <string>
#include "core/linux/procfs/ProcMaps.hpp"

std::string 
read_file(const std::string& path) {
    std::fstream file("script.js");
    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

void
init_bindings(const JSEngine& engine) {
    engine.add_binding("log", js_print, 100);
    engine.add_binding("pattach", js_pattach, 2);
    engine.add_binding("get_regs", js_get_registers, 0);
    engine.add_binding("get_base_address", js_get_base_address, 0);
    engine.add_binding("find_module", js_find_module, 1);
    engine.add_binding("attach", js_attach, 2);
    engine.add_binding("change_reg_value", js_change_register_value, 2);
}

int 
main(int argc, char* argv[]) {
    JSEngine engine;
    init_bindings(engine);
    std::string script = read_file("script.js");
    engine.execute(std::move(script));
    
    return 0;
}