// Auto-generated raylib bindings
#include "raylib.h"
#include "quickjs.h"
#include "raylib_autobind_structs.hpp"

// Binding for InitWindow
static JSValue js_InitWindow(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
	if (argc != 3) {
		return JS_ThrowTypeError(ctx, "InitWindow expects at least 3 arguments, but got %d", argc);
	}
	
	// Validate Arguments
	if (!JS_IsNumber(argv[0])) {
		return JS_ThrowTypeError(ctx, "Argument 1 (width): expected int");
	}
	if (!JS_IsNumber(argv[1])) {
		return JS_ThrowTypeError(ctx, "Argument 2 (height): expected int");
	}
	if (!JS_IsString(argv[2])) {
		return JS_ThrowTypeError(ctx, "Argument 3 (title): expected const char *");
	}
	
	// Extraction Values
	int width;
	JS_ToInt32(ctx, &width, argv[0]);
	int height;
	JS_ToInt32(ctx, &height, argv[1]);
	const char *title = JS_ToCString(ctx, argv[2]);
	if (!title) return JS_EXCEPTION;
	
	InitWindow(width, height, title);
	const JSValue result = JS_UNDEFINED;
	JS_FreeCString(ctx, title);
	return result;
}

// Binding for WindowShouldClose
static JSValue js_WindowShouldClose(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
	if (argc != 0) {
		return JS_ThrowTypeError(ctx, "WindowShouldClose expects at least 0 arguments, but got %d", argc);
	}
	
	const JSValue result = JS_NewBool(ctx, WindowShouldClose());
	return result;
}

// Binding for CloseWindow
static JSValue js_CloseWindow(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
	if (argc != 0) {
		return JS_ThrowTypeError(ctx, "CloseWindow expects at least 0 arguments, but got %d", argc);
	}
	
	CloseWindow();
	const JSValue result = JS_UNDEFINED;
	return result;
}

// Binding for IsWindowReady
static JSValue js_IsWindowReady(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
	if (argc != 0) {
		return JS_ThrowTypeError(ctx, "IsWindowReady expects at least 0 arguments, but got %d", argc);
	}
	
	const JSValue result = JS_NewBool(ctx, IsWindowReady());
	return result;
}

// Binding for SetWindowPosition
static JSValue js_SetWindowPosition(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
	if (argc != 2) {
		return JS_ThrowTypeError(ctx, "SetWindowPosition expects at least 2 arguments, but got %d", argc);
	}
	
	// Validate Arguments
	if (!JS_IsNumber(argv[0])) {
		return JS_ThrowTypeError(ctx, "Argument 1 (x): expected int");
	}
	if (!JS_IsNumber(argv[1])) {
		return JS_ThrowTypeError(ctx, "Argument 2 (y): expected int");
	}
	
	// Extraction Values
	int x;
	JS_ToInt32(ctx, &x, argv[0]);
	int y;
	JS_ToInt32(ctx, &y, argv[1]);
	
	SetWindowPosition(x, y);
	const JSValue result = JS_UNDEFINED;
	return result;
}

// Binding for SetWindowTitle
static JSValue js_SetWindowTitle(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
	if (argc != 1) {
		return JS_ThrowTypeError(ctx, "SetWindowTitle expects at least 1 arguments, but got %d", argc);
	}
	
	// Validate Arguments
	if (!JS_IsString(argv[0])) {
		return JS_ThrowTypeError(ctx, "Argument 1 (title): expected const char *");
	}
	
	// Extraction Values
	const char *title = JS_ToCString(ctx, argv[0]);
	if (!title) return JS_EXCEPTION;
	
	SetWindowTitle(title);
	const JSValue result = JS_UNDEFINED;
	JS_FreeCString(ctx, title);
	return result;
}

// Binding for GetScreenWidth
static JSValue js_GetScreenWidth(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
	if (argc != 0) {
		return JS_ThrowTypeError(ctx, "GetScreenWidth expects at least 0 arguments, but got %d", argc);
	}
	
	const JSValue result = JS_NewInt32(ctx, GetScreenWidth());
	return result;
}

// Binding for GetScreenHeight
static JSValue js_GetScreenHeight(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
	if (argc != 0) {
		return JS_ThrowTypeError(ctx, "GetScreenHeight expects at least 0 arguments, but got %d", argc);
	}
	
	const JSValue result = JS_NewInt32(ctx, GetScreenHeight());
	return result;
}

// Binding for SetTargetFPS
static JSValue js_SetTargetFPS(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
	if (argc != 1) {
		return JS_ThrowTypeError(ctx, "SetTargetFPS expects at least 1 arguments, but got %d", argc);
	}
	
	// Validate Arguments
	if (!JS_IsNumber(argv[0])) {
		return JS_ThrowTypeError(ctx, "Argument 1 (fps): expected int");
	}
	
	// Extraction Values
	int fps;
	JS_ToInt32(ctx, &fps, argv[0]);
	
	SetTargetFPS(fps);
	const JSValue result = JS_UNDEFINED;
	return result;
}

// Binding for GetFPS
static JSValue js_GetFPS(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
	if (argc != 0) {
		return JS_ThrowTypeError(ctx, "GetFPS expects at least 0 arguments, but got %d", argc);
	}
	
	const JSValue result = JS_NewInt32(ctx, GetFPS());
	return result;
}

// Binding for GetFrameTime
static JSValue js_GetFrameTime(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
	if (argc != 0) {
		return JS_ThrowTypeError(ctx, "GetFrameTime expects at least 0 arguments, but got %d", argc);
	}
	
	const JSValue result = JS_NewFloat64(ctx, GetFrameTime());
	return result;
}

// Binding for BeginDrawing
static JSValue js_BeginDrawing(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
	if (argc != 0) {
		return JS_ThrowTypeError(ctx, "BeginDrawing expects at least 0 arguments, but got %d", argc);
	}
	
	BeginDrawing();
	const JSValue result = JS_UNDEFINED;
	return result;
}

// Binding for EndDrawing
static JSValue js_EndDrawing(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
	if (argc != 0) {
		return JS_ThrowTypeError(ctx, "EndDrawing expects at least 0 arguments, but got %d", argc);
	}
	
	EndDrawing();
	const JSValue result = JS_UNDEFINED;
	return result;
}

// Binding for ClearBackground
static JSValue js_ClearBackground(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
	if (argc != 1) {
		return JS_ThrowTypeError(ctx, "ClearBackground expects at least 1 arguments, but got %d", argc);
	}
	
	// Validate Arguments
	if (!JS_IsObject(argv[0])) {
		return JS_ThrowTypeError(ctx, "Argument 1 (color): expected object of type Color");
	}
	
	// Extraction Values
	const auto color = static_cast<Color *>(JS_GetOpaque2(ctx, argv[0], js_Color_class_id));
	if (!color) return JS_EXCEPTION;
	
	ClearBackground(*color);
	const JSValue result = JS_UNDEFINED;
	return result;
}

// Binding for BeginMode2D
static JSValue js_BeginMode2D(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
	if (argc != 1) {
		return JS_ThrowTypeError(ctx, "BeginMode2D expects at least 1 arguments, but got %d", argc);
	}
	
	// Validate Arguments
	if (!JS_IsObject(argv[0])) {
		return JS_ThrowTypeError(ctx, "Argument 1 (camera): expected object of type Camera2D");
	}
	
	// Extraction Values
	const auto camera = static_cast<Camera2D *>(JS_GetOpaque2(ctx, argv[0], js_Camera2D_class_id));
	if (!camera) return JS_EXCEPTION;
	
	BeginMode2D(*camera);
	const JSValue result = JS_UNDEFINED;
	return result;
}

// Binding for EndMode2D
static JSValue js_EndMode2D(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
	if (argc != 0) {
		return JS_ThrowTypeError(ctx, "EndMode2D expects at least 0 arguments, but got %d", argc);
	}
	
	EndMode2D();
	const JSValue result = JS_UNDEFINED;
	return result;
}

// Binding for BeginMode3D
static JSValue js_BeginMode3D(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
	if (argc != 1) {
		return JS_ThrowTypeError(ctx, "BeginMode3D expects at least 1 arguments, but got %d", argc);
	}
	
	// Validate Arguments
	if (!JS_IsObject(argv[0])) {
		return JS_ThrowTypeError(ctx, "Argument 1 (camera): expected object of type Camera3D");
	}
	
	// Extraction Values
	const auto camera = static_cast<Camera3D *>(JS_GetOpaque2(ctx, argv[0], js_Camera3D_class_id));
	if (!camera) return JS_EXCEPTION;
	
	BeginMode3D(*camera);
	const JSValue result = JS_UNDEFINED;
	return result;
}

// Binding for EndMode3D
static JSValue js_EndMode3D(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
	if (argc != 0) {
		return JS_ThrowTypeError(ctx, "EndMode3D expects at least 0 arguments, but got %d", argc);
	}
	
	EndMode3D();
	const JSValue result = JS_UNDEFINED;
	return result;
}

// Binding for TakeScreenshot
static JSValue js_TakeScreenshot(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
	if (argc != 1) {
		return JS_ThrowTypeError(ctx, "TakeScreenshot expects at least 1 arguments, but got %d", argc);
	}
	
	// Validate Arguments
	if (!JS_IsString(argv[0])) {
		return JS_ThrowTypeError(ctx, "Argument 1 (fileName): expected const char *");
	}
	
	// Extraction Values
	const char *fileName = JS_ToCString(ctx, argv[0]);
	if (!fileName) return JS_EXCEPTION;
	
	TakeScreenshot(fileName);
	const JSValue result = JS_UNDEFINED;
	JS_FreeCString(ctx, fileName);
	return result;
}

static constexpr JSCFunctionListEntry js_raylib_funcs[] = {
	JS_CFUNC_DEF("InitWindow", 3, js_InitWindow),
	JS_CFUNC_DEF("WindowShouldClose", 0, js_WindowShouldClose),
	JS_CFUNC_DEF("CloseWindow", 0, js_CloseWindow),
	JS_CFUNC_DEF("IsWindowReady", 0, js_IsWindowReady),
	JS_CFUNC_DEF("SetWindowPosition", 2, js_SetWindowPosition),
	JS_CFUNC_DEF("SetWindowTitle", 1, js_SetWindowTitle),
	JS_CFUNC_DEF("GetScreenWidth", 0, js_GetScreenWidth),
	JS_CFUNC_DEF("GetScreenHeight", 0, js_GetScreenHeight),
	JS_CFUNC_DEF("SetTargetFPS", 1, js_SetTargetFPS),
	JS_CFUNC_DEF("GetFPS", 0, js_GetFPS),
	JS_CFUNC_DEF("GetFrameTime", 0, js_GetFrameTime),
	JS_CFUNC_DEF("BeginDrawing", 0, js_BeginDrawing),
	JS_CFUNC_DEF("EndDrawing", 0, js_EndDrawing),
	JS_CFUNC_DEF("ClearBackground", 1, js_ClearBackground),
	JS_CFUNC_DEF("BeginMode2D", 1, js_BeginMode2D),
	JS_CFUNC_DEF("EndMode2D", 0, js_EndMode2D),
	JS_CFUNC_DEF("BeginMode3D", 1, js_BeginMode3D),
	JS_CFUNC_DEF("EndMode3D", 0, js_EndMode3D),
	JS_CFUNC_DEF("TakeScreenshot", 1, js_TakeScreenshot),
};

void js_define_raylib_window_functions(JSContext *ctx, JSValue target) {
	JS_SetPropertyFunctionList(ctx, target, js_raylib_funcs, 19);
}
