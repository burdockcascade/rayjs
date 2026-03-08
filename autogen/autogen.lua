local script_path = debug.getinfo(1).source:match("@?(.*[\\/])") or ""
package.path = package.path .. ";" .. script_path .. "?.lua"

local status, raylib = pcall(require, "raylib")

local script_path = debug.getinfo(1).source:match("@?(.*[\\/])") or ""
local project_root = script_path .. "../"
local output_dir = project_root .. "src/bindings/"

-- Check if the library loaded successfully
if not status then
    print("Error: Could not load the 'raylib' module.")
    return
else
    print("Successfully loaded the 'raylib' module.")
end

local cats = {
    core = {
        "InitWindow",
        "WindowShouldClose",
        "CloseWindow",
        "IsWindowReady",
        "SetWindowPosition",
        "SetWindowTitle",
        "GetScreenWidth",
        "GetScreenHeight",
        "SetTargetFPS",
        "GetFPS",
        "GetFrameTime",
        "BeginDrawing",
        "EndDrawing",
        "ClearBackground",
        "BeginMode2D",
        "EndMode2D",
        "BeginMode3D",
        "EndMode3D",
        "TakeScreenshot"
    }
}

-- 1. Define shared logic for common data types
local types = {
    int32 = {
        to_js = "JS_NewInt32",
        from_js = "JS_ToInt32",
        qjs_type = "int32_t",
        validation = "JS_IsNumber",
        friendly_name = "integer",
    },
    uint32 = {
        to_js = "JS_NewUint32",
        from_js = "JS_ToUint32",
        qjs_type = "uint32_t",
        validation = "JS_IsNumber",
        friendly_name = "unsigned integer",
    },
    float64 = {
        to_js = "JS_NewFloat64",
        from_js = "JS_ToFloat64",
        qjs_type = "double",
        validation = "JS_IsNumber",
        friendly_name = "number",
    },
    string = {
        to_js = "JS_NewString",
        from_js = "JS_ToCString",
        qjs_type = "const char *",
        validation = "JS_IsString",
        friendly_name = "string",
    },
    bool = {
        to_js = "JS_NewBool",
        from_js = "JS_ToBool",
        qjs_type = "bool",
        validation = "JS_IsBool",
        friendly_name = "boolean",
    }
}

-- 2. Map C types to the shared logic
local conversion_map = {
    ["int"]            = types.int32,
    ["char"]           = types.int32,
    ["short"]          = types.int32,
    ["short int"]      = types.int32,
    ["unsigned int"]   = types.uint32,
    ["unsigned char"]  = types.uint32,
    ["unsigned short"] = types.uint32,
    ["float"]          = types.float64,
    ["double"]         = types.float64,
    ["bool"]           = types.bool,
    ["const char *"]   = types.string,

    -- Longs remain separate as they use 64-bit QuickJS functions
    ["long"] = {
        to_js = "JS_NewInt64",
        from_js = "JS_ToInt64",
        qjs_type = "int64_t",
    },
    ["unsigned long"] = {
        to_js = "JS_NewUint64",
        from_js = "JS_ToUint64",
        qjs_type = "uint64_t",
    }
}

-- 3. Automatically ingest aliases from raylib.lua
if raylib.aliases then
    for _, alias in pairs(raylib.aliases) do
        if conversion_map[alias.type] then
            conversion_map[alias.name] = conversion_map[alias.type]
        end
    end
end

local function emit(indent_level, file, line)
    local indentation = string.rep("\t", indent_level)
    table.insert(file, indentation .. line)
end

local function write_structs()
    local header_file_path = output_dir .. "raylib_autogen_structs.hpp"
    local source_file_path = output_dir .. "raylib_autogen_structs.cpp"

    local h = {}
    emit(0, h, "// Auto-generated raylib bindings")
    emit(0, h, "#pragma once")
    emit(0, h, "#include \"quickjs.h\"")

    for _, struct in pairs(raylib.structs) do
        emit(0, h, string.format("inline JSClassID js_%s_class_id;", struct.name))
    end
    emit(0, h, "")
    emit(0, h, "void js_define_raylib_structs(JSContext *ctx, JSValue target);")

    local header_file = io.open(header_file_path, "w")
    if header_file then
        header_file:write(table.concat(h, "\n") .. "\n")
        header_file:close()
    end

    local cpp = {}
    emit(0, cpp, "// Auto-generated raylib bindings")
    emit(0, cpp, "#include \"raylib.h\"")
    emit(0, cpp, "#include \"quickjs.h\"")
    emit(0, cpp, "#include \"raylib_autogen_structs.hpp\"")
    emit(0, cpp, "")

    for _, struct in pairs(raylib.structs) do
        if struct.name ~= "Color" and struct.name ~= "Vector2" and struct.name ~= "Vector3" then
            goto continue
        end

        -- Finalizer
        emit(0, cpp, string.format("static void js_%s_finalizer(JSRuntime *rt, JSValue val) {", struct.name))
        emit(1, cpp, string.format("if (auto* ptr = static_cast<%s *>(JS_GetOpaque(val, js_%s_class_id))) {", struct.name, struct.name))
        emit(2, cpp, "js_free_rt(rt, ptr);")
        emit(1, cpp, "}")
        emit(0, cpp, "}")
        emit(0, cpp, "")

        -- Getters
        for _, prop in pairs(struct.fields) do
            local conversion = conversion_map[prop.type]
            emit(0, cpp, string.format("static JSValue js_%s_get_%s(JSContext *ctx, JSValueConst this_val) {", struct.name, prop.name))
            -- Data is only read, so we use const auto*
            emit(1, cpp, string.format("if (const auto* obj = static_cast<const %s *>(JS_GetOpaque2(ctx, this_val, js_%s_class_id))) {", struct.name, struct.name))

            if conversion then
                emit(2, cpp, string.format("return %s(ctx, obj->%s);", conversion.to_js, prop.name))
            else
                emit(2, cpp, string.format("if (auto* ret_ptr = static_cast<%s*>(js_malloc(ctx, sizeof(%s)))) {", prop.type, prop.type))
                emit(3, cpp, string.format("*ret_ptr = obj->%s;", prop.name))
                emit(3, cpp, string.format("auto ret = JS_NewObjectClass(ctx, js_%s_class_id);", prop.type))
                emit(3, cpp, "JS_SetOpaque(ret, ret_ptr);")
                emit(3, cpp, "return ret;")
                emit(2, cpp, "}")
            end
            emit(1, cpp, "}")
            emit(1, cpp, "return JS_EXCEPTION;")
            emit(0, cpp, "}")
            emit(0, cpp, "")
        end

        -- Setters
        for _, prop in pairs(struct.fields) do
            local conversion = conversion_map[prop.type]
            emit(0, cpp, string.format("static JSValue js_%s_set_%s(JSContext *ctx, JSValueConst this_val, JSValueConst val) {", struct.name, prop.name))
            emit(1, cpp, string.format("auto* obj = static_cast<%s *>(JS_GetOpaque2(ctx, this_val, js_%s_class_id));", struct.name, struct.name))
            emit(1, cpp, "if (!obj) return JS_EXCEPTION;")

            if conversion then
                emit(1, cpp, string.format("%s result;", conversion.qjs_type))
                emit(1, cpp, string.format("if (%s(ctx, &result, val) < 0) return JS_EXCEPTION;", conversion.from_js))
                emit(1, cpp, string.format("obj->%s = static_cast<%s>(result);", prop.name, prop.type))
            else
                emit(1, cpp, string.format("auto* val_ptr = static_cast<%s *>(JS_GetOpaque2(ctx, val, js_%s_class_id));", prop.type, prop.type, prop.type))
                emit(1, cpp, "if (!val_ptr) return JS_EXCEPTION;")
                emit(1, cpp, string.format("obj->%s = *val_ptr;", prop.name))
            end
            emit(1, cpp, "return JS_UNDEFINED;")
            emit(0, cpp, "}")
            emit(0, cpp, "")
        end

        -- Function List
        emit(0, cpp, string.format("static constexpr JSCFunctionListEntry js_%s_funcs[] = {", struct.name))
        for _, prop in pairs(struct.fields) do
            emit(1, cpp, string.format("JS_CGETSET_DEF(\"%s\", js_%s_get_%s, js_%s_set_%s),", prop.name, struct.name, prop.name, struct.name, prop.name))
        end
        emit(0, cpp, "};")
        emit(0, cpp, "")

        -- Class Def
        emit(0, cpp, string.format("static constexpr JSClassDef js_%s_class_def = {", struct.name))
        emit(1, cpp, string.format(".class_name = \"%s\",", struct.name))
        emit(1, cpp, string.format(".finalizer = js_%s_finalizer,", struct.name))
        emit(0, cpp, "};")
        emit(0, cpp, "")

        -- Constructor
        emit(0, cpp, string.format("static JSValue js_%s_constructor(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {", struct.name))
        emit(1, cpp, string.format("auto* obj = static_cast<%s *>(js_mallocz(ctx, sizeof(%s)));", struct.name, struct.name))
        emit(1, cpp, "if (!obj) return JS_EXCEPTION;")
        emit(1, cpp, "")

        for index, prop in ipairs(struct.fields) do
            local conversion = conversion_map[prop.type]
            emit(1, cpp, string.format("if (argc > %d) {", index - 1))
            if conversion then
                emit(2, cpp, string.format("%s val;", conversion.qjs_type))
                emit(2, cpp, string.format("if (%s(ctx, &val, argv[%d]) < 0) { js_free(ctx, obj); return JS_EXCEPTION; }", conversion.from_js, index - 1))
                emit(2, cpp, string.format("obj->%s = static_cast<%s>(val);", prop.name, prop.type))
            else
                -- Source pointers are const
                emit(2, cpp, string.format("if (const auto* ptr = static_cast<const %s*>(JS_GetOpaque2(ctx, argv[%d], js_%s_class_id))) {", prop.type, index - 1, prop.type))
                emit(3, cpp, string.format("obj->%s = *ptr;", prop.name))
                emit(2, cpp, "} else { js_free(ctx, obj); return JS_EXCEPTION; }")
            end
            emit(1, cpp, "}")
        end

        emit(1, cpp, string.format("auto ret = JS_NewObjectClass(ctx, js_%s_class_id);", struct.name))
        emit(1, cpp, "if (JS_IsException(ret)) { js_free(ctx, obj); return JS_EXCEPTION; }")
        emit(1, cpp, "JS_SetOpaque(ret, obj);")
        emit(1, cpp, "return ret;")
        emit(0, cpp, "}")
        emit(0, cpp, "")

        -- Init function
        emit(0, cpp, string.format("void js_define_raylib_%s_struct(JSContext *ctx, JSValue target) {", struct.name))
        emit(1, cpp, "JSRuntime *rt = JS_GetRuntime(ctx);")
        emit(1, cpp, string.format("JS_NewClassID(rt, &js_%s_class_id);", struct.name))
        emit(1, cpp, string.format("JS_NewClass(rt, js_%s_class_id, &js_%s_class_def);", struct.name, struct.name))
        emit(1, cpp, "")
        emit(1, cpp, "const JSValue proto = JS_NewObject(ctx);")
        emit(1, cpp, string.format("JS_SetPropertyFunctionList(ctx, proto, js_%s_funcs, %d);", struct.name, #struct.fields))
        emit(1, cpp, string.format("JS_SetClassProto(ctx, js_%s_class_id, proto);", struct.name))
        emit(1, cpp, "")
        emit(1, cpp, string.format("const JSValue constructor = JS_NewCFunction2(ctx, js_%s_constructor, \"%s\", 0, JS_CFUNC_constructor, 0);", struct.name, struct.name))
        emit(1, cpp, string.format("JS_SetPropertyStr(ctx, target, \"%s\", constructor);", struct.name))
        emit(0, cpp, "}")
        emit(0, cpp, "")

        ::continue::
    end

    emit(0, cpp, "void js_define_raylib_structs(JSContext *ctx, JSValue target) {")
    for _, struct in pairs(raylib.structs) do
        if struct.name == "Color" or struct.name == "Vector2" or struct.name == "Vector3" then
            emit(1, cpp, string.format("js_define_raylib_%s_struct(ctx, target);", struct.name))
        end
    end
    emit(0, cpp, "}")

    local source_file = io.open(source_file_path, "w")
    if source_file then
        source_file:write(table.concat(cpp, "\n") .. "\n")
        source_file:close()
    end
end

local function write_functions()

    local functions_by_category = {}
    for category, functions in pairs(cats) do

        if not functions_by_category[category] then
            functions_by_category[category] = {}
        end

        for _, func_name in pairs(functions) do
            for _, func in pairs(raylib.functions) do
                if func.name == func_name then
                    table.insert(functions_by_category[category], func)
                    break
                end
            end
        end
    end


    for category, functions in pairs(functions_by_category) do

       local header_file_path = output_dir .. "raylib_autogen_" .. category .. ".hpp"
       local source_file_path = output_dir .. "raylib_autogen_" .. category .. ".cpp"

       local h = {}
       local cpp = {}

        -- add header info
        emit(0, h, "// Auto-generated raylib bindings")
        emit(0, h, "#pragma once")

        -- add include
        emit(0, h, "#include \"quickjs.h\"")

        -- end header info
        emit(0, h, string.format("void js_define_raylib_%s_functions(JSContext *ctx, JSValue target);", category))

        -- Write header file
        local header_file = io.open(header_file_path, "w")
        if header_file then
            header_file:write(table.concat(h, "\n") .. "\n")
            header_file:close()
        end

        -- start cpp
        local cpp = {}
        emit(0, cpp, "// Auto-generated raylib bindings")
        emit(0, cpp, "#include \"raylib.h\"")
        emit(0, cpp, "#include \"quickjs.h\"")
        emit(0, cpp, "#include \"raylib_autogen_structs.hpp\"")
        emit(0, cpp, "")

        for _, func in pairs(functions) do
            local func_name = func.name
            local param_count = func.params and #func.params or 0

            emit(0, cpp, string.format("// Binding for %s", func_name))
            emit(0, cpp, string.format("static JSValue js_%s(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {", func_name))

            -- 1. Check Argument Count
            emit(1, cpp, string.format("if (argc != %d) {", param_count))
            emit(2, cpp, string.format("return JS_ThrowTypeError(ctx, \"%s expects at least %d arguments, but got %%d\", argc);", func_name, param_count))
            emit(1, cpp, "}")
            emit(1, cpp, "")

            -- Validation (Check types before allocating anything)
            if (func.params) then
                emit(1, cpp, "// Validate Arguments")
                for index, value in ipairs(func.params or {}) do
                    local conversion = conversion_map[value.type]
                    if conversion and conversion.validation then
                        emit(1, cpp, string.format("if (!%s(argv[%d])) {", conversion.validation, index - 1))
                        emit(2, cpp, string.format("return JS_ThrowTypeError(ctx, \"Argument %d (%s): expected %s\");", index, value.name, value.type))
                        emit(1, cpp, "}")
                    elseif not conversion then
                        -- Opaque object validation
                        emit(1, cpp, string.format("if (!JS_IsObject(argv[%d])) {", index - 1))
                        emit(2, cpp, string.format("return JS_ThrowTypeError(ctx, \"Argument %d (%s): expected object of type %s\");", index, value.name, value.type))
                        emit(1, cpp, "}")
                    end
                end
                emit(1, cpp, "")

                -- Extraction/Allocation
                emit(1, cpp, "// Extraction Values")
                for index, value in ipairs(func.params or {}) do
                    local conversion = conversion_map[value.type]
                    if value.type == "const char *" then
                        emit(1, cpp, string.format("const char *%s = JS_ToCString(ctx, argv[%d]);", value.name, index - 1))
                        emit(1, cpp, "if (!" .. value.name .. ") return JS_EXCEPTION;")
                    elseif conversion then
                        emit(1, cpp, string.format("%s %s;", value.type, value.name))
                        emit(1, cpp, string.format("%s(ctx, &%s, argv[%d]);", conversion.from_js, value.name, index - 1))
                    else
                        -- Opaque object extraction
                        emit(1, cpp, string.format("const auto %s = static_cast<%s *>(JS_GetOpaque2(ctx, argv[%d], js_%s_class_id));", value.name, value.type, index - 1, value.type))
                        emit(1, cpp, string.format("if (!%s) return JS_EXCEPTION;", value.name))
                    end
                end
                emit(1, cpp, "")
            end

            -- 4. Execution
            local call_params = {}
            for _, param in pairs(func.params or {}) do
                table.insert(call_params, conversion_map[param.type] and param.name or ("*" .. param.name))
            end
            local call_params_str = table.concat(call_params, ", ")

            if func.returnType ~= "void" then
                local ret_conv = conversion_map[func.returnType]
                emit(1, cpp, string.format("const JSValue result = %s(ctx, %s(%s));", ret_conv.to_js, func_name, call_params_str))
            else
                emit(1, cpp, string.format("%s(%s);", func_name, call_params_str))
                emit(1, cpp, "const JSValue result = JS_UNDEFINED;")
            end

            -- 5. Mandatory Cleanup
            for index, value in ipairs(func.params or {}) do
                if value.type == "const char *" then
                    emit(1, cpp, string.format("JS_FreeCString(ctx, %s);", value.name))
                end
            end

            emit(1, cpp, "return result;")
            emit(0, cpp, "}")
            emit(0, cpp, "")
        end

        emit(0, cpp, "static constexpr JSCFunctionListEntry js_raylib_funcs[] = {")
        for _, func in pairs(functions) do
            local param_count = func.params and #func.params or 0
            emit(1, cpp, string.format("JS_CFUNC_DEF(\"%s\", %d, js_%s),", func.name, param_count, func.name))
        end
        emit(0, cpp, "};")
        emit(0, cpp, "")

        emit(0, cpp, string.format("void js_define_raylib_%s_functions(JSContext *ctx, JSValue target) {", category))
        emit(1, cpp, "JS_SetPropertyFunctionList(ctx, target, js_raylib_funcs, " .. tostring(#functions) .. ");")
        emit(0, cpp, "}")

        -- Write source file
        local source_file = io.open(source_file_path, "w")
        if source_file then
            source_file:write(table.concat(cpp, "\n") .. "\n")
            source_file:close()
        end

    end

end

-- Write the functions
write_functions()

-- Write the structs
write_structs()