#pragma once
#include "quickjs.h"
#include <string>
#include <iostream>

class JSEngine {
public:
    JSEngine() {
        m_rt = JS_NewRuntime();
        m_ctx = JS_NewContext(m_rt);
    }

    ~JSEngine() {
        JS_FreeContext(m_ctx);
        JS_FreeRuntime(m_rt);
    }
    void execute(const std::string& script) const;
    void add_binding(const std::string& name, JSCFunction* binding, uint8_t argc) const;
private:
    JSRuntime* m_rt;
    JSContext* m_ctx;
};