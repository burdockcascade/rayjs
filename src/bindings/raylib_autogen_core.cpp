// Auto-generated raylib bindings
#include "raylib.h"
#include "quickjs.h"
#include "raylib_autogen_structs.hpp"

// Binding for InitWindow
static JSValue js_InitWindow(JSContext *ctx, JSValueConst this_val, const int argc, JSValueConst *argv) {
	if (argc != 3) {
		return JS_ThrowTypeError(ctx, "Expected 3 arguments, got %d", argc);
	}

	// Argument 1: int width
	if (JS_IsNull(argv[0])) {
		return JS_ThrowTypeError(ctx, "Argument 1: value is null");
	}

	if (JS_IsUndefined(argv[0])) {
		return JS_ThrowTypeError(ctx, "Argument 1: value is undefined");
	}

	if (!JS_IsNumber(argv[0])) {
		return JS_ThrowTypeError(ctx, "Argument 1: expected int");
	}

	int width;
	if (JS_ToInt32(ctx, &width, argv[0]) < 0) {
		return JS_ThrowTypeError(ctx, "Argument 1: expected integer");
	}

	// Argument 2: int height
	if (JS_IsNull(argv[1])) {
		return JS_ThrowTypeError(ctx, "Argument 2: value is null");
	}

	if (JS_IsUndefined(argv[1])) {
		return JS_ThrowTypeError(ctx, "Argument 2: value is undefined");
	}

	if (!JS_IsNumber(argv[1])) {
		return JS_ThrowTypeError(ctx, "Argument 2: expected int");
	}

	int height;
	if (JS_ToInt32(ctx, &height, argv[1]) < 0) {
		return JS_ThrowTypeError(ctx, "Argument 2: expected integer");
	}

	// Argument 3: const char * title
	if (JS_IsNull(argv[2])) {
		return JS_ThrowTypeError(ctx, "Argument 3: value is null");
	}

	if (JS_IsUndefined(argv[2])) {
		return JS_ThrowTypeError(ctx, "Argument 3: value is undefined");
	}

	if (!JS_IsString(argv[2])) {
		return JS_ThrowTypeError(ctx, "Argument 3: expected const char *");
	}

	const char * title = JS_ToCString(ctx, argv[2]);
	if (!title) {
		return JS_ThrowTypeError(ctx, "Argument 3: expected string");
	}

	InitWindow(width, height, title);
	return JS_UNDEFINED;
}

// Binding for WindowShouldClose
static JSValue js_WindowShouldClose(JSContext *ctx, JSValueConst this_val, const int argc, JSValueConst *argv) {
	if (argc != 0) {
		return JS_ThrowTypeError(ctx, "Expected 0 arguments, got %d", argc);
	}

	const JSValue result = JS_NewBool(ctx, WindowShouldClose());
	return result;
}

// Binding for CloseWindow
static JSValue js_CloseWindow(JSContext *ctx, JSValueConst this_val, const int argc, JSValueConst *argv) {
	if (argc != 0) {
		return JS_ThrowTypeError(ctx, "Expected 0 arguments, got %d", argc);
	}

	CloseWindow();
	return JS_UNDEFINED;
}

// Binding for IsWindowReady
static JSValue js_IsWindowReady(JSContext *ctx, JSValueConst this_val, const int argc, JSValueConst *argv) {
	if (argc != 0) {
		return JS_ThrowTypeError(ctx, "Expected 0 arguments, got %d", argc);
	}

	const JSValue result = JS_NewBool(ctx, IsWindowReady());
	return result;
}

// Binding for SetWindowPosition
static JSValue js_SetWindowPosition(JSContext *ctx, JSValueConst this_val, const int argc, JSValueConst *argv) {
	if (argc != 2) {
		return JS_ThrowTypeError(ctx, "Expected 2 arguments, got %d", argc);
	}

	// Argument 1: int x
	if (JS_IsNull(argv[0])) {
		return JS_ThrowTypeError(ctx, "Argument 1: value is null");
	}

	if (JS_IsUndefined(argv[0])) {
		return JS_ThrowTypeError(ctx, "Argument 1: value is undefined");
	}

	if (!JS_IsNumber(argv[0])) {
		return JS_ThrowTypeError(ctx, "Argument 1: expected int");
	}

	int x;
	if (JS_ToInt32(ctx, &x, argv[0]) < 0) {
		return JS_ThrowTypeError(ctx, "Argument 1: expected integer");
	}

	// Argument 2: int y
	if (JS_IsNull(argv[1])) {
		return JS_ThrowTypeError(ctx, "Argument 2: value is null");
	}

	if (JS_IsUndefined(argv[1])) {
		return JS_ThrowTypeError(ctx, "Argument 2: value is undefined");
	}

	if (!JS_IsNumber(argv[1])) {
		return JS_ThrowTypeError(ctx, "Argument 2: expected int");
	}

	int y;
	if (JS_ToInt32(ctx, &y, argv[1]) < 0) {
		return JS_ThrowTypeError(ctx, "Argument 2: expected integer");
	}

	SetWindowPosition(x, y);
	return JS_UNDEFINED;
}

// Binding for SetWindowTitle
static JSValue js_SetWindowTitle(JSContext *ctx, JSValueConst this_val, const int argc, JSValueConst *argv) {
	if (argc != 1) {
		return JS_ThrowTypeError(ctx, "Expected 1 arguments, got %d", argc);
	}

	// Argument 1: const char * title
	if (JS_IsNull(argv[0])) {
		return JS_ThrowTypeError(ctx, "Argument 1: value is null");
	}

	if (JS_IsUndefined(argv[0])) {
		return JS_ThrowTypeError(ctx, "Argument 1: value is undefined");
	}

	if (!JS_IsString(argv[0])) {
		return JS_ThrowTypeError(ctx, "Argument 1: expected const char *");
	}

	const char * title = JS_ToCString(ctx, argv[0]);
	if (!title) {
		return JS_ThrowTypeError(ctx, "Argument 1: expected string");
	}

	SetWindowTitle(title);
	return JS_UNDEFINED;
}

// Binding for GetScreenWidth
static JSValue js_GetScreenWidth(JSContext *ctx, JSValueConst this_val, const int argc, JSValueConst *argv) {
	if (argc != 0) {
		return JS_ThrowTypeError(ctx, "Expected 0 arguments, got %d", argc);
	}

	const JSValue result = JS_NewInt32(ctx, GetScreenWidth());
	return result;
}

// Binding for GetScreenHeight
static JSValue js_GetScreenHeight(JSContext *ctx, JSValueConst this_val, const int argc, JSValueConst *argv) {
	if (argc != 0) {
		return JS_ThrowTypeError(ctx, "Expected 0 arguments, got %d", argc);
	}

	const JSValue result = JS_NewInt32(ctx, GetScreenHeight());
	return result;
}

// Binding for SetTargetFPS
static JSValue js_SetTargetFPS(JSContext *ctx, JSValueConst this_val, const int argc, JSValueConst *argv) {
	if (argc != 1) {
		return JS_ThrowTypeError(ctx, "Expected 1 arguments, got %d", argc);
	}

	// Argument 1: int fps
	if (JS_IsNull(argv[0])) {
		return JS_ThrowTypeError(ctx, "Argument 1: value is null");
	}

	if (JS_IsUndefined(argv[0])) {
		return JS_ThrowTypeError(ctx, "Argument 1: value is undefined");
	}

	if (!JS_IsNumber(argv[0])) {
		return JS_ThrowTypeError(ctx, "Argument 1: expected int");
	}

	int fps;
	if (JS_ToInt32(ctx, &fps, argv[0]) < 0) {
		return JS_ThrowTypeError(ctx, "Argument 1: expected integer");
	}

	SetTargetFPS(fps);
	return JS_UNDEFINED;
}

// Binding for GetFPS
static JSValue js_GetFPS(JSContext *ctx, JSValueConst this_val, const int argc, JSValueConst *argv) {
	if (argc != 0) {
		return JS_ThrowTypeError(ctx, "Expected 0 arguments, got %d", argc);
	}

	const JSValue result = JS_NewInt32(ctx, GetFPS());
	return result;
}

// Binding for GetFrameTime
static JSValue js_GetFrameTime(JSContext *ctx, JSValueConst this_val, const int argc, JSValueConst *argv) {
	if (argc != 0) {
		return JS_ThrowTypeError(ctx, "Expected 0 arguments, got %d", argc);
	}

	const JSValue result = JS_NewFloat64(ctx, GetFrameTime());
	return result;
}

// Binding for BeginDrawing
static JSValue js_BeginDrawing(JSContext *ctx, JSValueConst this_val, const int argc, JSValueConst *argv) {
	if (argc != 0) {
		return JS_ThrowTypeError(ctx, "Expected 0 arguments, got %d", argc);
	}

	BeginDrawing();
	return JS_UNDEFINED;
}

// Binding for EndDrawing
static JSValue js_EndDrawing(JSContext *ctx, JSValueConst this_val, const int argc, JSValueConst *argv) {
	if (argc != 0) {
		return JS_ThrowTypeError(ctx, "Expected 0 arguments, got %d", argc);
	}

	EndDrawing();
	return JS_UNDEFINED;
}

// Binding for ClearBackground
static JSValue js_ClearBackground(JSContext *ctx, JSValueConst this_val, const int argc, JSValueConst *argv) {
	if (argc != 1) {
		return JS_ThrowTypeError(ctx, "Expected 1 arguments, got %d", argc);
	}

	// Argument 1: Color color
	if (JS_IsNull(argv[0])) {
		return JS_ThrowTypeError(ctx, "Argument 1: value is null");
	}

	if (JS_IsUndefined(argv[0])) {
		return JS_ThrowTypeError(ctx, "Argument 1: value is undefined");
	}

	Color* color = static_cast<Color *>(JS_GetOpaque2(ctx, argv[0], js_Color_class_id));
	if (!color) {
		return JS_ThrowTypeError(ctx, "Argument 1: expected Color");
	}

	ClearBackground(*color);
	return JS_UNDEFINED;
}

// Binding for WaitTime
static JSValue js_WaitTime(JSContext *ctx, JSValueConst this_val, const int argc, JSValueConst *argv) {
	if (argc != 1) {
		return JS_ThrowTypeError(ctx, "Expected 1 arguments, got %d", argc);
	}

	// Argument 1: double seconds
	if (JS_IsNull(argv[0])) {
		return JS_ThrowTypeError(ctx, "Argument 1: value is null");
	}

	if (JS_IsUndefined(argv[0])) {
		return JS_ThrowTypeError(ctx, "Argument 1: value is undefined");
	}

	if (!JS_IsNumber(argv[0])) {
		return JS_ThrowTypeError(ctx, "Argument 1: expected double");
	}

	double seconds;
	if (JS_ToFloat64(ctx, &seconds, argv[0]) < 0) {
		return JS_ThrowTypeError(ctx, "Argument 1: expected number");
	}

	WaitTime(seconds);
	return JS_UNDEFINED;
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
	JS_CFUNC_DEF("WaitTime", 1, js_WaitTime),
};

void js_define_raylib_core_functions(JSContext *ctx, JSValue target) {
	JS_SetPropertyFunctionList(ctx, target, js_raylib_funcs, 15);
}
