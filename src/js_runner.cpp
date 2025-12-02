#include "js_runner.hpp"
#include <iostream>
#include <fstream>
#include <sstream>

extern "C" {
    #include <quickjs.h>
}

std::string format_js_args(JSContext *ctx, const int argc, const JSValue *argv) {
    std::string output;
    for (int i = 0; i < argc; i++) {
        // Convert the JavaScript value to a string representation
        JSValue str_val = JS_ToString(ctx, argv[i]);
        const char *cstr = JS_ToCString(ctx, str_val);

        if (cstr) {
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

// C function signature for QuickJS host functions
static JSValue js_console_log(JSContext *ctx, JSValueConst this_val, const int argc, JSValueConst *argv) {
    // Cast JSValueConst* to JSValue* for use in format_js_args
    std::string output = format_js_args(ctx, argc, argv);

    // Print the output with a tag for clarity
    std::cout << "[JS LOG]: " << output << std::endl;

    // Return JS_UNDEFINED (no meaningful return value for console.log)
    return JS_UNDEFINED;
}

// C function for console.error
static JSValue js_console_error(JSContext *ctx, JSValueConst this_val, const int argc, JSValueConst *argv) {
    std::string output = format_js_args(ctx, argc, argv);

    // Print to standard error stream (std::cerr)
    std::cerr << "[JS ERROR]: " << output << std::endl;

    return JS_UNDEFINED;
}

// Array defining the methods of the 'console' object
static const JSCFunctionListEntry js_console_funcs[] = {
    JS_CFUNC_DEF("log", 1, js_console_log),   // 'log' method
    JS_CFUNC_DEF("error", 1, js_console_error) // 'error' method
};

// Function to install the 'console' object
void install_console_global(JSContext *ctx) {
    // 1. Create a new JavaScript object named 'console'
    const JSValue console = JS_NewObject(ctx);

    // 2. Add our C functions as methods to the 'console' object
    JS_SetPropertyFunctionList(
        ctx,
        console,
        js_console_funcs,
        sizeof(js_console_funcs) / sizeof(JSCFunctionListEntry)
    );

    // 3. Set the 'console' object as a global property
    JS_SetPropertyStr(
        ctx,
        JS_GetGlobalObject(ctx), // Get the global object (like 'window' in a browser)
        "console",
        console // Pass ownership of the console object to the global object
    );
}

// --- Internal Helper Function: Read File ---
std::string read_file(const std::string& filepath) {
    std::ifstream file(filepath);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file: " << filepath << std::endl;
        return "";
    }
    // Read the entire file stream into a string
    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

// --- Main Execution Function Implementation ---
int run_js_file(const std::string& filepath) {
    // 1. Read the file content
    std::string js_code = read_file(filepath);
    if (js_code.empty()) {
        // Error message already printed by read_file if it failed to open
        return 1;
    }

    // 2. Create a QuickJS Runtime and Context
    JSRuntime *rt = JS_NewRuntime();
    if (!rt) {
        std::cerr << "Error: Could not create QuickJS runtime." << std::endl;
        return 1;
    }
    JSContext *ctx = JS_NewContext(rt);
    if (!ctx) {
        std::cerr << "Error: Could not create QuickJS context." << std::endl;
        JS_FreeRuntime(rt);
        return 1;
    }

    // Install the 'console' global object
    install_console_global(ctx);

    // 3. Compile and Execute the JavaScript code
    JSValue val = JS_Eval(ctx, js_code.c_str(), js_code.length(), filepath.c_str(), JS_EVAL_FLAG_STRICT);

    // 4. Handle Execution Result (Success or Error)
    if (JS_IsException(val)) {
        std::cerr << "--- JavaScript Execution Error in " << filepath << " ---" << std::endl;

        // Get and print the exception object
        JSValue exception = JS_GetException(ctx);
        JSValue error_str = JS_ToString(ctx, exception);
        const char *err_msg = JS_ToCString(ctx, error_str);

        std::cerr << err_msg << std::endl;

        // Clean up
        JS_FreeCString(ctx, err_msg);
        JS_FreeValue(ctx, error_str);
        JS_FreeValue(ctx, exception);

        JS_FreeValue(ctx, val);
        JS_FreeContext(ctx);
        JS_FreeRuntime(rt);
        return 1; // Indicate failure
    } else {
        // Clean up successful execution value
        JS_FreeValue(ctx, val);
    }

    // 5. Clean up QuickJS resources
    JS_FreeContext(ctx);
    JS_FreeRuntime(rt);

    std::cout << "Successfully executed: " << filepath << std::endl;
    return 0; // Indicate success
}

