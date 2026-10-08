#include "bindings.hpp"


pid_t g_pid = -1;

static std::string 
get_js_error(JSContext* ctx) {
    JSValue value = JS_GetException(ctx);
    std::string exception_string = JS_ToCString(ctx, value);
    JS_FreeValue(ctx, value);
    return exception_string;
}

static void require_pid() {
    if (g_pid <= 0) {
        Logger::instance().error("Should Attach Before Do this Oprtaion");
        throw std::runtime_error("[!] You Should Attach First");
    }
}

static void 
wait_for_signal(uint64_t pid) {
    int status;
    waitpid(pid, &status, 0);
    siginfo_t signal = get_signal_info(pid);
    Logger::instance().info("Recived Signal ({})", strsignal(signal.si_signo));
}

static JSValue
get_register_object(user_regs_struct& regs, JSContext* ctx)  {
    JSValue registers_object = JS_NewObject(ctx);
    for (size_t i = 0; i < g_registers.size(); i++) {
        Register r = g_registers[i];
        uint64_t register_value = *reinterpret_cast<uint64_t*>(
            (reinterpret_cast<uint8_t*>(&regs) + r.offset)
        );
        JS_SetPropertyStr(ctx, registers_object, r.name, JS_NewBigUint64(ctx, register_value));
    }
    return registers_object;
}


BINDING_FUN(js_print) {
    for (int i = 0; i < argc; i++) {
        const char* value = JS_ToCString(ctx, argv[i]);
        std::printf(value);
        std::printf("\n");
    }
    return JS_UNDEFINED;
}

BINDING_FUN(js_pattach) {
    uint32_t pid;
    JS_ToUint32(ctx, &pid, argv[0]);
    g_pid = pid;
    attach(pid);
    wait_for_signal(pid);
    JSValue on_attach = JS_GetPropertyStr(ctx, argv[1], "onAttach");
    if (JS_IsNull(on_attach)) {
        return JS_NewInt32(ctx, 0);
    }
    JS_Call(ctx, on_attach, this_obj, 0, nullptr);
    JS_FreeValue(ctx, on_attach);
    return JS_UNDEFINED;
}

BINDING_FUN(js_get_registers) {
    require_pid();
    Logger::instance().debug("From Binding The PID = {}", g_pid);
    user_regs_struct regs = get_registers_values(g_pid);
    JSValue registers_object = get_register_object(regs, ctx);
    return registers_object;
}

BINDING_FUN(js_get_base_address) {
    require_pid();
    Logger::instance().debug("From Binding {} The PID = {}", __FUNCTION__, g_pid);
    ProcMaps maps { g_pid };
    uint64_t address = maps.get_module_base_address();
    return JS_NewBigUint64(ctx, address);
}

BINDING_FUN(js_find_module) {
    require_pid();
    JSValue module_value = JS_ToString(ctx, argv[0]);
    std::string module_name = JS_ToCString(ctx, module_value);
    Logger::instance().debug("Need {}", module_name);
    ProcMaps procfs { g_pid };
    uint64_t base = procfs.find_module_by_name(module_name);
    return JS_NewBigUint64(ctx, base);
}

BINDING_FUN(js_attach) {
    require_pid();
    // Get Offset
    int64_t signed_offset;
    int ret = JS_ToBigInt64(ctx, &signed_offset, argv[0]);
    if (ret < 0) {
        std::string exception = get_js_error(ctx);
        Logger::instance().error("Failed to extract BigInt offset ({})", exception);
        return JS_EXCEPTION;
    }
    uint64_t offset = static_cast<uint64_t>(signed_offset);
    Logger::instance().debug("User Need To Hook {:#x}", offset);
    // Set Breakpoint
    Breakpoint bp { offset };
    bp.set(g_pid);
    // Continue
    continue_execution(g_pid);
    // Listen For Signal
    wait_for_signal(g_pid);
    // Call OnEnter Handler and pass to it a register
    JSValueConst hooks = argv[1];
    JSValue on_enter = JS_GetPropertyStr(ctx, hooks, "onEnter");
    JSValue on_leave = JS_GetPropertyStr(ctx, hooks, "onLeave");
    
    user_regs_struct regs = get_registers_values(g_pid);
    JSValue register_object = get_register_object(regs, ctx);

    Logger::instance().debug("Calling onEnter Callback");
    JS_Call(ctx, on_enter, this_obj, 1, &register_object);
    
    // Leave Breakpoint
    bp.unset(g_pid);
    JS_Call(ctx, on_leave, this_obj, 1, &register_object);
    continue_execution(g_pid);

    // Clean
    JS_FreeValue(ctx, on_enter);
    JS_FreeValue(ctx, on_leave);
    JS_FreeValue(ctx, register_object);
    
    // Intercept toLeave
    return JS_UNDEFINED;
}   

BINDING_FUN(js_change_register_value) {
    require_pid();
    std::string register_name = JS_ToCString(ctx, argv[0]);
    int64_t register_value_signed;
    JS_ToBigInt64(ctx, &register_value_signed, argv[1]);
    uint64_t register_value = static_cast<uint64_t>(register_value_signed);
    auto it = std::find_if(g_registers.begin(), g_registers.end(), [register_name](const Register& reg) {
        return reg.name == register_name; 
    });
    if (it == nullptr) {
        return JS_ThrowInternalError(ctx, "Register Not Exist");
    }
    user_regs_struct regs = get_registers_values(g_pid);
    *reinterpret_cast<uint64_t*>(
        reinterpret_cast<uint8_t*>(&regs) + it->offset
    ) = register_value;
    update_registers(g_pid, regs);
    Logger::instance().debug("{} Is Updated", register_name);
    return JS_UNDEFINED;
}