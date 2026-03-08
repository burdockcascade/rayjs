// Auto-generated raylib bindings
#include "raylib.h"
#include "quickjs.h"
#include "raylib_autobind_structs.hpp"

// Binding for DrawPixel
static JSValue js_DrawPixel(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
	if (argc != 3) {
		return JS_ThrowTypeError(ctx, "DrawPixel expects at least 3 arguments, but got %d", argc);
	}
	
	// Validate Arguments
	if (!JS_IsNumber(argv[0])) {
		return JS_ThrowTypeError(ctx, "Argument 1 (posX): expected int");
	}
	if (!JS_IsNumber(argv[1])) {
		return JS_ThrowTypeError(ctx, "Argument 2 (posY): expected int");
	}
	if (!JS_IsObject(argv[2])) {
		return JS_ThrowTypeError(ctx, "Argument 3 (color): expected object of type Color");
	}
	
	// Extraction Values
	int posX;
	JS_ToInt32(ctx, &posX, argv[0]);
	int posY;
	JS_ToInt32(ctx, &posY, argv[1]);
	const auto color = static_cast<Color *>(JS_GetOpaque2(ctx, argv[2], js_Color_class_id));
	if (!color) return JS_EXCEPTION;
	
	DrawPixel(posX, posY, *color);
	const JSValue result = JS_UNDEFINED;
	return result;
}

// Binding for DrawLine
static JSValue js_DrawLine(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
	if (argc != 5) {
		return JS_ThrowTypeError(ctx, "DrawLine expects at least 5 arguments, but got %d", argc);
	}
	
	// Validate Arguments
	if (!JS_IsNumber(argv[0])) {
		return JS_ThrowTypeError(ctx, "Argument 1 (startPosX): expected int");
	}
	if (!JS_IsNumber(argv[1])) {
		return JS_ThrowTypeError(ctx, "Argument 2 (startPosY): expected int");
	}
	if (!JS_IsNumber(argv[2])) {
		return JS_ThrowTypeError(ctx, "Argument 3 (endPosX): expected int");
	}
	if (!JS_IsNumber(argv[3])) {
		return JS_ThrowTypeError(ctx, "Argument 4 (endPosY): expected int");
	}
	if (!JS_IsObject(argv[4])) {
		return JS_ThrowTypeError(ctx, "Argument 5 (color): expected object of type Color");
	}
	
	// Extraction Values
	int startPosX;
	JS_ToInt32(ctx, &startPosX, argv[0]);
	int startPosY;
	JS_ToInt32(ctx, &startPosY, argv[1]);
	int endPosX;
	JS_ToInt32(ctx, &endPosX, argv[2]);
	int endPosY;
	JS_ToInt32(ctx, &endPosY, argv[3]);
	const auto color = static_cast<Color *>(JS_GetOpaque2(ctx, argv[4], js_Color_class_id));
	if (!color) return JS_EXCEPTION;
	
	DrawLine(startPosX, startPosY, endPosX, endPosY, *color);
	const JSValue result = JS_UNDEFINED;
	return result;
}

// Binding for DrawCircle
static JSValue js_DrawCircle(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
	if (argc != 4) {
		return JS_ThrowTypeError(ctx, "DrawCircle expects at least 4 arguments, but got %d", argc);
	}
	
	// Validate Arguments
	if (!JS_IsNumber(argv[0])) {
		return JS_ThrowTypeError(ctx, "Argument 1 (centerX): expected int");
	}
	if (!JS_IsNumber(argv[1])) {
		return JS_ThrowTypeError(ctx, "Argument 2 (centerY): expected int");
	}
	if (!JS_IsNumber(argv[2])) {
		return JS_ThrowTypeError(ctx, "Argument 3 (radius): expected float");
	}
	if (!JS_IsObject(argv[3])) {
		return JS_ThrowTypeError(ctx, "Argument 4 (color): expected object of type Color");
	}
	
	// Extraction Values
	int centerX;
	JS_ToInt32(ctx, &centerX, argv[0]);
	int centerY;
	JS_ToInt32(ctx, &centerY, argv[1]);
	float radius;
	JS_ToFloat64(ctx, &radius, argv[2]);
	const auto color = static_cast<Color *>(JS_GetOpaque2(ctx, argv[3], js_Color_class_id));
	if (!color) return JS_EXCEPTION;
	
	DrawCircle(centerX, centerY, radius, *color);
	const JSValue result = JS_UNDEFINED;
	return result;
}

// Binding for DrawRectangle
static JSValue js_DrawRectangle(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
	if (argc != 5) {
		return JS_ThrowTypeError(ctx, "DrawRectangle expects at least 5 arguments, but got %d", argc);
	}
	
	// Validate Arguments
	if (!JS_IsNumber(argv[0])) {
		return JS_ThrowTypeError(ctx, "Argument 1 (posX): expected int");
	}
	if (!JS_IsNumber(argv[1])) {
		return JS_ThrowTypeError(ctx, "Argument 2 (posY): expected int");
	}
	if (!JS_IsNumber(argv[2])) {
		return JS_ThrowTypeError(ctx, "Argument 3 (width): expected int");
	}
	if (!JS_IsNumber(argv[3])) {
		return JS_ThrowTypeError(ctx, "Argument 4 (height): expected int");
	}
	if (!JS_IsObject(argv[4])) {
		return JS_ThrowTypeError(ctx, "Argument 5 (color): expected object of type Color");
	}
	
	// Extraction Values
	int posX;
	JS_ToInt32(ctx, &posX, argv[0]);
	int posY;
	JS_ToInt32(ctx, &posY, argv[1]);
	int width;
	JS_ToInt32(ctx, &width, argv[2]);
	int height;
	JS_ToInt32(ctx, &height, argv[3]);
	const auto color = static_cast<Color *>(JS_GetOpaque2(ctx, argv[4], js_Color_class_id));
	if (!color) return JS_EXCEPTION;
	
	DrawRectangle(posX, posY, width, height, *color);
	const JSValue result = JS_UNDEFINED;
	return result;
}

// Binding for DrawText
static JSValue js_DrawText(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
	if (argc != 5) {
		return JS_ThrowTypeError(ctx, "DrawText expects at least 5 arguments, but got %d", argc);
	}
	
	// Validate Arguments
	if (!JS_IsString(argv[0])) {
		return JS_ThrowTypeError(ctx, "Argument 1 (text): expected const char *");
	}
	if (!JS_IsNumber(argv[1])) {
		return JS_ThrowTypeError(ctx, "Argument 2 (posX): expected int");
	}
	if (!JS_IsNumber(argv[2])) {
		return JS_ThrowTypeError(ctx, "Argument 3 (posY): expected int");
	}
	if (!JS_IsNumber(argv[3])) {
		return JS_ThrowTypeError(ctx, "Argument 4 (fontSize): expected int");
	}
	if (!JS_IsObject(argv[4])) {
		return JS_ThrowTypeError(ctx, "Argument 5 (color): expected object of type Color");
	}
	
	// Extraction Values
	const char *text = JS_ToCString(ctx, argv[0]);
	if (!text) return JS_EXCEPTION;
	int posX;
	JS_ToInt32(ctx, &posX, argv[1]);
	int posY;
	JS_ToInt32(ctx, &posY, argv[2]);
	int fontSize;
	JS_ToInt32(ctx, &fontSize, argv[3]);
	const auto color = static_cast<Color *>(JS_GetOpaque2(ctx, argv[4], js_Color_class_id));
	if (!color) return JS_EXCEPTION;
	
	DrawText(text, posX, posY, fontSize, *color);
	const JSValue result = JS_UNDEFINED;
	JS_FreeCString(ctx, text);
	return result;
}

static constexpr JSCFunctionListEntry js_raylib_funcs[] = {
	JS_CFUNC_DEF("DrawPixel", 3, js_DrawPixel),
	JS_CFUNC_DEF("DrawLine", 5, js_DrawLine),
	JS_CFUNC_DEF("DrawCircle", 4, js_DrawCircle),
	JS_CFUNC_DEF("DrawRectangle", 5, js_DrawRectangle),
	JS_CFUNC_DEF("DrawText", 5, js_DrawText),
};

void js_define_raylib_draw2d_functions(JSContext *ctx, JSValue target) {
	JS_SetPropertyFunctionList(ctx, target, js_raylib_funcs, 5);
}
