#include "JSEngine.hpp"

void JSEngine::execute(const std::string& script) const {
    JSValue result = JS_Eval(m_ctx, script.c_str(), script.size(), "<inline>", JS_EVAL_TYPE_GLOBAL);
    if (JS_IsException(result)) {
        JSValue error = JS_GetException(m_ctx);
        const char* error_text = JS_ToCString(m_ctx, error);
        std::cerr << "JS Error: " << error_text << "\n";
        JS_FreeCString(m_ctx, error_text);
        JS_FreeValue(m_ctx, error);
    }
}

void JSEngine::add_binding(const std::string& name, JSCFunction* binding, uint8_t argc) const {
    JSValue global = JS_GetGlobalObject(m_ctx);
    JSValue fun = JS_NewCFunction(m_ctx, binding, name.c_str(), argc);
    JS_SetPropertyStr(m_ctx, global, name.c_str(), fun);
    JS_FreeValue(m_ctx, global);
}