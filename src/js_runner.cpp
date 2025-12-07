#include "js_runner.hpp"
#include <iostream>
#include <fstream>
#include <raylib.h>
#include <sstream>
#include <quickjs.h>
#include "bindings/raylib_autogen_core.hpp"
#include "bindings/raylib_autogen_structs.hpp"

// Helper function to format JavaScript arguments into a single string
std::string format_js_args(JSContext *ctx, const int argc, const JSValue *argv) {
    std::string output;
    for (int i = 0; i < argc; i++) {
        // Convert the JavaScript value to a string representation
        const JSValue str_val = JS_ToString(ctx, argv[i]);

        if (const char *cstr = JS_ToCString(ctx, str_val)) {
            output += cstr;
            if (i < argc - 1) {
                output += " "; // Add space between arguments
            }
            JS_FreeCString(ctx, cstr);
        }
        JS_FreeValue(ctx, str_val);
    }
    return output;
}

// function signature for QuickJS host functions
static JSValue js_console_log(JSContext *ctx, JSValueConst this_val, const int argc, JSValueConst *argv) {
    // Cast JSValueConst* to JSValue* for use in format_js_args
    const std::string output = format_js_args(ctx, argc, argv);

    // Print the output with a tag for clarity
    std::cout << "[JS LOG]: " << output << std::endl;

    // Return JS_UNDEFINED (no meaningful return value for console.log)
    return JS_UNDEFINED;
}

// function for console.error
static JSValue js_console_error(JSContext *ctx, JSValueConst this_val, const int argc, JSValueConst *argv) {
    const std::string output = format_js_args(ctx, argc, argv);

    // Print to standard error stream (std::cerr)
    std::cerr << "[JS ERROR]: " << output << std::endl;

    return JS_UNDEFINED;
}

// Array defining the methods of the 'console' object
static constexpr JSCFunctionListEntry js_console_funcs[] = {
    JS_CFUNC_DEF("log", 1, js_console_log),   // 'log' method
    JS_CFUNC_DEF("error", 1, js_console_error) // 'error' method
};

// Function to install the 'console' object
void install_console_global(JSContext *ctx) {

    // Create a new JavaScript object named 'console'
    const JSValue console = JS_NewObject(ctx);

    // Add our C functions as methods to the 'console' object
    JS_SetPropertyFunctionList(
        ctx,
        console,
        js_console_funcs,
        sizeof(js_console_funcs) / sizeof(JSCFunctionListEntry)
    );

    // Set the 'console' object as a global property
    JS_SetPropertyStr(
        ctx,
        JS_GetGlobalObject(ctx), // Get the global object (like 'window' in a browser)
        "console",
        console // Pass ownership of the console object to the global object
    );
}

std::string read_file(const std::string& filepath) {
    std::ifstream file(filepath);
    if (!file.is_open()) {
        TraceLog(LOG_ERROR, "Error: Could not open file '%s' for reading.", filepath.c_str());
        return "";
    }
    // Read the entire file stream into a string
    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

int run_js_file(const std::string& filepath) {

    // Read the file content
    std::string js_code = read_file(filepath);
    if (js_code.empty()) {
        return 1;
    }

    // Create a QuickJS Runtime and Context
    JSRuntime *rt = JS_NewRuntime();
    if (!rt) {
        TraceLog(LOG_ERROR, "Error: Could not create QuickJS runtime.");
        return 1;
    }

    JSContext *ctx = JS_NewContext(rt);
    if (!ctx) {
        TraceLog(LOG_ERROR, "Error: Could not create QuickJS context.");
        JS_FreeRuntime(rt);
        return 1;
    }

    // Install the 'console' global object
    install_console_global(ctx);

    // Install the 'Raylib' global object and its functions
    JSValue global_obj = JS_GetGlobalObject(ctx);

    JSValue raylib_obj = JS_NewObject(ctx);
    JS_SetPropertyStr(ctx, global_obj, "Raylib", raylib_obj);

    js_define_raylib_structs(ctx, raylib_obj);
    js_define_raylib_core_functions(ctx, raylib_obj);

    // Compile and Execute the JavaScript code
    const JSValue val = JS_Eval(ctx, js_code.c_str(), js_code.length(), filepath.c_str(), JS_EVAL_FLAG_STRICT);

    // Free the global object reference
    JS_FreeValue(ctx, global_obj);
    JS_FreeValue(ctx, raylib_obj);

    // Handle Execution Result (Success or Error)
    if (JS_IsException(val)) {

        // Get and print the exception object
        const JSValue exception = JS_GetException(ctx);
        const JSValue error_str = JS_ToString(ctx, exception);
        const char *err_msg = JS_ToCString(ctx, error_str);

        if (JS_IsError(exception)) {
            JSValue stack_val = JS_GetPropertyStr(ctx, exception, "stack");
            if (!JS_IsUndefined(stack_val)) {
                const char *stack_str = JS_ToCString(ctx, stack_val);
                if (stack_str) {
                    TraceLog(LOG_ERROR, "JavaScript Error: %s\nStack Trace:\n%s", err_msg, stack_str);
                    JS_FreeCString(ctx, stack_str);
                }
            }
            JS_FreeValue(ctx, stack_val);
        }

        // Clean up
        JS_FreeCString(ctx, err_msg);
        JS_FreeValue(ctx, error_str);
        JS_FreeValue(ctx, exception);

        JS_FreeValue(ctx, val);
        JS_FreeContext(ctx);
        JS_FreeRuntime(rt);
        return 1; // Indicate failure
    }

    // Clean up QuickJS resources
    JS_FreeValue(ctx, val);
    JS_FreeContext(ctx);
    JS_FreeRuntime(rt);

    TraceLog(LOG_INFO, "JavaScript file '%s' executed successfully.", filepath.c_str());
    return 0; // Indicate success
}

