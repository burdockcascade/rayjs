local status, raylib = pcall(require, "raylib")

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
        --"BeginMode2D",
        --"EndMode2D",
        --"BeginMode3D",
        --"EndMode3D",
        --"TakeScreenshot",
        --"WaitTime",
    }
}

local conversion_map = {
    ["int"] = {
        to_js = "JS_NewInt32",
        from_js = "JS_ToInt32",
        qjs_type = "int32_t",
        validation = "JS_IsNumber",
        friendly_name = "integer",
    },
    ["float"] = {
        to_js = "JS_NewFloat64",
        from_js = "JS_ToFloat64",
        qjs_type = "double",
        validation = "JS_IsNumber",
        friendly_name = "number",
    },
    ["double"] = {
        to_js = "JS_NewFloat64",
        from_js = "JS_ToFloat64",
        qjs_type = "double",
        validation = "JS_IsNumber",
        friendly_name = "number",
    },
    ["bool"] = {
        to_js = "JS_NewBool",
        from_js = "JS_ToBool",
        qjs_type = "bool",
        validation = "JS_IsBool",
        friendly_name = "boolean",
    },
    ["char"] = {
        to_js = "JS_NewInt32",
        from_js = "JS_ToInt32",
        qjs_type = "int32_t",
        friendly_name = "number",
    },
    ["const char *"] = {
        to_js = "JS_NewString",
        from_js = "JS_ToCString",
        qjs_type = "const char *",
        validation = "JS_IsString",
        friendly_name = "string",
    },
    ["short int"] = {
        to_js = "JS_NewInt32",
        from_js = "JS_ToInt32",
        qjs_type = "int32_t",
    },
    ["short"] = {
        to_js = "JS_NewInt32",
        from_js = "JS_ToInt32",
        qjs_type = "int32_t",
    },
    ["long"] = {
        to_js = "JS_NewInt64",
        from_js = "JS_ToInt64",
        qjs_type = "int64_t",
    },
    ["unsigned int"] = {
        to_js = "JS_NewUint32",
        from_js = "JS_ToUint32",
        qjs_type = "uint32_t",
    },
    ["unsigned char"] = {
        to_js = "JS_NewUint32",
        from_js = "JS_ToUint32",
        qjs_type = "uint32_t",
    },
    ["unsigned short"] = {
        to_js = "JS_NewUint32",
        from_js = "JS_ToUint32",
        qjs_type = "uint32_t",
    },
    ["unsigned long"] = {
        to_js = "JS_NewUint64",
        from_js = "JS_ToUint64",
        qjs_type = "uint64_t",
    }
}

local function write_structs()

    -- create/open header file
    local header_file = "C:\\Workspace\\rayjs\\src\\bindings\\raylib_autogen_structs.hpp"
    print("Creating file: " .. header_file)
    local header = io.open(header_file, "w")

    if not header then
        print("Error: Could not open file for writing: " .. header_file)
        return
    end

    -- add header info
    header:write("// Auto-generated raylib bindings\n")
    header:write("#pragma once\n\n")

    -- add include
    header:write("#include \"quickjs.h\"\n\n")

    -- class id declarations
    for _, struct in pairs(raylib.structs) do
        header:write(string.format("inline JSClassID js_%s_class_id;\n", struct.name))
    end

    header:write("\n")

    -- end header info
    header:write(string.format("void js_define_raylib_structs(JSContext *ctx, JSValue target);\n"))

    header:close()

    -- create/open source file
    local source_file = "C:\\Workspace\\rayjs\\src\\bindings\\raylib_autogen_structs.cpp"
    print("Creating file: " .. source_file)
    local file = io.open(source_file, "w")

    if not file then
        print("Error: Could not open file for writing: " .. source_file)
        return
    end

    -- add headers
    file:write("// Auto-generated raylib bindings\n")
    file:write("#include \"raylib.h\"\n")
    file:write("#include \"quickjs.h\"\n")
    file:write("#include \"raylib_autogen_structs.hpp\"\n\n")

    -- for each struct
    for _, struct in pairs(raylib.structs) do

        -- skip unless its Color
        if struct.name ~= "Color" and struct.name ~= "Vector2" and struct.name ~= "Vector3" then
            goto continue
        end

        print("Generating bindings for struct: " .. struct.name)

        -- class finalizer
        file:write(string.format("static void js_%s_finalizer(JSRuntime *rt, const JSValue val) {\n", struct.name))
        file:write(string.format("\t%s *ptr = static_cast<%s *>(JS_GetOpaque(val, js_%s_class_id));\n", struct.name, struct.name, struct.name))
        file:write("\tif (ptr) { js_free_rt(rt, ptr); }\n")
        file:write("}\n\n")

        -- get each property
        for _, prop in pairs(struct.fields) do
            local conversion = conversion_map[prop.type]

            file:write(string.format("static JSValue js_%s_get_%s(JSContext *ctx, const JSValueConst val) {\n", struct.name, prop.name))
            file:write(string.format("\tconst %s *obj = static_cast<%s *>(JS_GetOpaque2(ctx, val, js_%s_class_id));\n", struct.name, struct.name, struct.name))
            file:write("\tif (!obj) { return JS_EXCEPTION; }\n\n")

            if conversion then
                file:write(string.format("\tconst JSValue ret = %s(ctx, obj->%s);\n", conversion.to_js, prop.name))
            else
                file:write(string.format("\tconst auto ret_ptr = static_cast<%s*>(js_malloc(ctx, sizeof(%s)));\n", prop.type, prop.type, prop.type))
                file:write("\tif (!ret_ptr) { return JS_EXCEPTION; }\n")
                file:write(string.format(string.format("\t*ret_ptr = obj->%s;\n", prop.name)))
                file:write(string.format("\tconst JSValue ret = JS_NewObjectClass(ctx, js_%s_class_id);\n", struct.name))
                file:write("\tJS_SetOpaque(ret, ret_ptr);\n\n")
            end


            file:write("\treturn ret;\n")
            file:write("}\n\n")
        end

        -- set each property
        for _, prop in pairs(struct.fields) do
            local conversion = conversion_map[prop.type]

            if conversion then
                file:write(string.format("static JSValue js_%s_set_%s(JSContext *ctx, const JSValueConst this_val, const JSValueConst val) {\n",struct.name, prop.name))
                file:write(string.format("\tconst auto obj = static_cast<%s *>(JS_GetOpaque(this_val, js_%s_class_id));\n", struct.name, struct.name, struct.name))
                file:write("\tif (!obj) { return JS_EXCEPTION; }\n")
                file:write(string.format("\t%s result;\n", conversion.qjs_type))
                file:write(string.format("\t%s(ctx, &result, val);\n", conversion.from_js))
                file:write(string.format("\tobj->%s = result;\n", prop.name))
                file:write("\treturn JS_UNDEFINED;\n")
                file:write("}\n\n")
            else
                file:write(string.format("static JSValue js_%s_set_%s(JSContext *ctx, const JSValueConst this_val, const JSValueConst val) {\n", struct.name, prop.name))
                file:write(string.format("\tconst auto obj = static_cast<%s *>(JS_GetOpaque(this_val, js_%s_class_id));\n", struct.name, struct.name))
                file:write("\tif (!obj) { return JS_EXCEPTION; }\n")
                file:write(string.format("\t%s* val_ptr = static_cast<%s *>(JS_GetOpaque2(ctx, val, js_%s_class_id));\n", prop.type, prop.type, prop.type))
                file:write("\tif (!val_ptr) { return JS_EXCEPTION; }\n")
                file:write(string.format("\tobj->%s = *val_ptr;\n", prop.name))
                file:write("\treturn JS_UNDEFINED;\n")
                file:write("}\n\n")
            end
        end

        -- create function list
        file:write(string.format("static constexpr JSCFunctionListEntry js_%s_funcs[] = {\n", struct.name))
        for _, prop in pairs(struct.fields) do
            file:write(string.format("\tJS_CGETSET_DEF(\"%s\", js_%s_get_%s, js_%s_set_%s),\n", prop.name, struct.name, prop.name, struct.name, prop.name))
        end
        file:write("};\n\n")

        file:write(string.format("static constexpr JSClassDef js_%s_class_def = {\n", struct.name))
        file:write(string.format("\t.class_name = \"%s\",\n", struct.name))
        file:write("\t.finalizer = js_" .. struct.name .. "_finalizer,\n")
        file:write("};\n\n")

        -- create constructor
        file:write(string.format("static JSValue js_%s_constructor(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {\n", struct.name))
        file:write(string.format("\tconst auto obj = static_cast<%s *>(js_malloc(ctx, sizeof(%s)));\n", struct.name, struct.name))
        file:write("\tif (!obj) { return JS_EXCEPTION; }\n\n")

        -- set fields
        for index, prop in pairs(struct.fields) do
            local conversion = conversion_map[prop.type]
            file:write(string.format("\t// Argument %d: %s %s\n", index, prop.type, prop.name))
            if conversion then
                file:write(string.format("\t%s %s;\n", conversion.qjs_type, prop.name))
                file:write(string.format("\tif (%s(ctx, &%s, argv[%d]) < 0) {\n", conversion.from_js, prop.name, index - 1))
                file:write(string.format("\t\tjs_free(ctx, obj);\n"))
                file:write(string.format("\t\treturn JS_ThrowTypeError(ctx, \"Argument %d: expected %s\");\n", index, prop.type))
                file:write("\t}\n")
                file:write(string.format("\tobj->%s = %s;\n\n", prop.name, prop.name))
            else
                file:write(string.format("\tconst auto %s = static_cast<%s *>(JS_GetOpaque2(ctx, argv[%d], js_%s_class_id));\n", prop.name, prop.type, index - 1, prop.type))
                file:write(string.format("\tif (!%s) {\n", prop.name))
                file:write(string.format("\t\tjs_free(ctx, obj);\n"))
                file:write(string.format("\t\treturn JS_ThrowTypeError(ctx, \"Argument %d: expected %s\");\n", index, prop.type))
                file:write("\t}\n")
                file:write(string.format("\tobj->%s = *%s;\n\n", prop.name, prop.name))
            end
        end

        file:write(string.format("\tconst JSValue ret = JS_NewObjectClass(ctx, js_%s_class_id);\n", struct.name))
        file:write("\tJS_SetOpaque(ret, obj);\n\n")
        file:write("\treturn ret;\n")
        file:write("}\n\n")

        -- declare init function
        file:write(string.format("void js_define_raylib_%s_struct(JSContext *ctx, JSValue target) {\n", struct.name))
        file:write(string.format("\tJSRuntime *rt = JS_GetRuntime(ctx);\n"))
        file:write(string.format("\tJS_NewClassID(rt, &js_%s_class_id);\n", struct.name))

        file:write(string.format("\tJS_NewClass(rt, js_%s_class_id, &js_%s_class_def);\n", struct.name, struct.name))
        file:write(string.format("\tconst JSValue proto = JS_NewObject(ctx);\n"))
        file:write(string.format("\tJS_SetPropertyFunctionList(ctx, proto, js_%s_funcs, %d);\n", struct.name, #struct.fields))
        file:write(string.format("\tJS_SetClassProto(ctx, js_%s_class_id, proto);\n", struct.name))
        file:write(string.format("\tconst JSValue constructor = JS_NewCFunction2(ctx, js_%s_constructor, \"%s\", 0, JS_CFUNC_constructor, 0);\n", struct.name, struct.name))
        file:write(string.format("\tJS_SetPropertyStr(ctx, target, \"%s\", constructor);\n", struct.name))
        file:write("}\n\n")

        ::continue::
    end

    -- write final function to initialize all structs
    file:write("void js_define_raylib_structs(JSContext *ctx, JSValue target) {\n")
    for _, struct in pairs(raylib.structs) do
        if struct.name ~= "Color" and struct.name ~= "Vector2" and struct.name ~= "Vector3" then
            goto continue2
        end
        file:write(string.format("\tjs_define_raylib_%s_struct(ctx, target);\n", struct.name))
        ::continue2::
    end
    file:write("}\n")

    -- close file
    file:close()

end

local function write_functions()

    local functions_by_caegory = {}
    for category, functions in pairs(cats) do

        if not functions_by_caegory[category] then
            functions_by_caegory[category] = {}
        end

        for _, func_name in pairs(functions) do
            for _, func in pairs(raylib.functions) do
                if func.name == func_name then
                    table.insert(functions_by_caegory[category], func)
                    break
                end
            end
        end
    end


    for category, functions in pairs(functions_by_caegory) do

        -- create/open header file
        local header_file = "C:\\Workspace\\rayjs\\src\\bindings\\raylib_autogen_" .. category .. ".hpp"
        print("Creating file: " .. header_file)
        local header = io.open(header_file, "w")

        if not header then
            print("Error: Could not open file for writing: " .. header_file)
            return
        end

        -- add header info
        header:write("// Auto-generated raylib bindings\n")
        header:write("#pragma once\n\n")

        -- add include
        header:write("#include \"quickjs.h\"\n\n")

        -- end header info
        header:write(string.format("void js_define_raylib_%s_functions(JSContext *ctx, JSValue target);\n", category))

        header:close()

        -- create/open source file
        local source_file = "C:\\Workspace\\rayjs\\src\\bindings\\raylib_autogen_" .. category .. ".cpp"
        print("Creating file: " .. source_file)
        local file = io.open(source_file, "w")

        if not file then
            print("Error: Could not open file for writing: " .. source_file)
            return
        end

        -- add headers
        file:write("// Auto-generated raylib bindings\n")
        file:write("#include \"raylib.h\"\n")
        file:write("#include \"quickjs.h\"\n")
        file:write("#include \"raylib_autogen_structs.hpp\"\n\n")


        for _, func in pairs(functions) do

            local func_name = func.name
            local param_count = 0

            if func.params then
                param_count = #func.params
            end

            -- Write the function binding to the file
            file:write(string.format("// Binding for %s\n", func_name))
            file:write(string.format("static JSValue js_%s(JSContext *ctx, JSValueConst this_val, const int argc, JSValueConst *argv) {\n", func_name))

            -- check arg count
            file:write(string.format("\tif (argc != %d) {\n", param_count))
            file:write(string.format("\t\treturn JS_ThrowTypeError(ctx, \"Expected %d arguments, got %%d\", argc);\n", param_count))
            file:write("\t}\n\n")

            -- for each parameter
            for index, value in ipairs(func.params or {}) do

                file:write(string.format("\t// Argument %d: %s %s\n", index, value.type, value.name))

                local conversion = conversion_map[value.type] and conversion_map[value.type]

                -- check for null
                file:write(string.format("\tif (JS_IsNull(argv[%d])) {\n", index - 1))
                file:write(string.format("\t\treturn JS_ThrowTypeError(ctx, \"Argument %d: value is null\");\n", index))
                file:write("\t}\n\n")

                -- check for undefined
                file:write(string.format("\tif (JS_IsUndefined(argv[%d])) {\n", index - 1))
                file:write(string.format("\t\treturn JS_ThrowTypeError(ctx, \"Argument %d: value is undefined\");\n", index))
                file:write("\t}\n\n")

                -- validate
                if conversion and conversion.validation then
                    file:write(string.format("\tif (!%s(argv[%d])) {\n", conversion.validation, index - 1))
                    file:write(string.format("\t\treturn JS_ThrowTypeError(ctx, \"Argument %d: expected %s\");\n", index, value.type))
                    file:write("\t}\n\n")
                end

                if value.type == "const char *" then
                    file:write(string.format("\t%s %s = JS_ToCString(ctx, argv[%d]);\n", value.type, value.name, index - 1))
                    file:write("\tif (!" .. value.name .. ") {\n")
                    file:write(string.format("\t\treturn JS_ThrowTypeError(ctx, \"Argument %d: expected string\");\n", index))
                    file:write("\t}\n\n")
                else
                    if conversion then
                        file:write(string.format("\t%s %s;\n", value.type, value.name))
                        file:write(string.format("\tif (%s(ctx, &%s, argv[%d]) < 0) {\n", conversion.from_js, value.name, index - 1))
                        file:write(string.format("\t\treturn JS_ThrowTypeError(ctx, \"Argument %d: expected %s\");\n", index, conversion.friendly_name))
                        file:write("\t}\n\n")
                    else
                        file:write(string.format("\t%s* %s = static_cast<%s *>(JS_GetOpaque2(ctx, argv[%d], js_%s_class_id));\n", value.type, value.name, value.type, index - 1, value.type))
                        file:write(string.format("\tif (!%s) {\n", value.name))
                        file:write(string.format("\t\treturn JS_ThrowTypeError(ctx, \"Argument %d: expected %s\");\n", index, value.type))
                        file:write("\t}\n\n")
                    end
                end
            end

            -- generate functon call
            local call_params = {}
            for _, param in pairs(func.params or {}) do
                local fname = param.name
                if conversion_map[param.type] == nil then
                    fname = "*" .. param.name
                end
                table.insert(call_params, fname)
            end
            local call_params_str = table.concat(call_params, ", ")

            -- call raylib function
            if func.returnType ~= "void" then
                local return_conversion = conversion_map[func.returnType] and conversion_map[func.returnType]
                file:write(string.format("\tconst JSValue result = %s(ctx, %s(%s));\n", return_conversion.to_js, func_name, call_params_str))
                file:write("\treturn result;\n")
            else
                file:write(string.format("\t%s(%s);\n", func_name, call_params_str))
                file:write("\treturn JS_UNDEFINED;\n")
            end

            file:write("}\n\n")

        end


        -- create array defining all functions
        file:write("static constexpr JSCFunctionListEntry js_raylib_funcs[] = {\n")
        for _, func in pairs(functions) do
            local param_count = 0
            if func.params then
                param_count = #func.params
            end
            file:write(string.format("\tJS_CFUNC_DEF(\"%s\", %d, js_%s),\n", func.name, param_count, func.name))
        end
        file:write("};\n\n")

        -- generate init function
        file:write(string.format("void js_define_raylib_%s_functions(JSContext *ctx, JSValue target) {\n", category))
        file:write("\tJS_SetPropertyFunctionList(ctx, target, js_raylib_funcs, " .. tostring(#functions) .. ");\n")
        file:write("}\n")

        -- close file
        file:close()

    end

end

-- Write the functions
write_functions()

-- Write the structs
write_structs()