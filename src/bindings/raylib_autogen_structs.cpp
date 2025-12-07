// Auto-generated raylib bindings
#include "raylib.h"
#include "quickjs.h"
#include "raylib_autogen_structs.hpp"

static void js_Vector2_finalizer(JSRuntime *rt, const JSValue val) {
	Vector2 *ptr = static_cast<Vector2 *>(JS_GetOpaque(val, js_Vector2_class_id));
	if (ptr) { js_free_rt(rt, ptr); }
}

static JSValue js_Vector2_get_x(JSContext *ctx, const JSValueConst val) {
	const Vector2 *obj = static_cast<Vector2 *>(JS_GetOpaque2(ctx, val, js_Vector2_class_id));
	if (!obj) { return JS_EXCEPTION; }
	const JSValue ret = JS_NewFloat64(ctx, obj->x);
	return ret;
}

static JSValue js_Vector2_get_y(JSContext *ctx, const JSValueConst val) {
	const Vector2 *obj = static_cast<Vector2 *>(JS_GetOpaque2(ctx, val, js_Vector2_class_id));
	if (!obj) { return JS_EXCEPTION; }
	const JSValue ret = JS_NewFloat64(ctx, obj->y);
	return ret;
}

static JSValue js_Vector2_set_x(JSContext *ctx, const JSValueConst this_val, const JSValueConst val) {
	Vector2 *obj = static_cast<Vector2 *>(JS_GetOpaque(this_val, js_Vector2_class_id));
	if (!obj) { return JS_EXCEPTION; }
	double result;
	JS_ToFloat64(ctx, &result, val);
	obj->x = result;
	return JS_UNDEFINED;
}

static JSValue js_Vector2_set_y(JSContext *ctx, const JSValueConst this_val, const JSValueConst val) {
	Vector2 *obj = static_cast<Vector2 *>(JS_GetOpaque(this_val, js_Vector2_class_id));
	if (!obj) { return JS_EXCEPTION; }
	double result;
	JS_ToFloat64(ctx, &result, val);
	obj->y = result;
	return JS_UNDEFINED;
}

static constexpr JSCFunctionListEntry js_Vector2_funcs[] = {
	JS_CGETSET_DEF("x", js_Vector2_get_x, js_Vector2_set_x),
	JS_CGETSET_DEF("y", js_Vector2_get_y, js_Vector2_set_y),
};

static constexpr JSClassDef js_Vector2_class_def = {
	.class_name = "Vector2",
	.finalizer = js_Vector2_finalizer,
};

static JSValue js_Vector2_constructor(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
	Vector2 *obj = static_cast<Vector2 *>(js_malloc(ctx, sizeof(Vector2)));
	if (!obj) { return JS_EXCEPTION; }

	double x_val;
	if (JS_ToFloat64(ctx, &x_val, argv[0]) < 0) {
		js_free(ctx, obj);
		return JS_ThrowTypeError(ctx, "Argument 1: expected float");
	}
	obj->x = x_val;

	double y_val;
	if (JS_ToFloat64(ctx, &y_val, argv[1]) < 0) {
		js_free(ctx, obj);
		return JS_ThrowTypeError(ctx, "Argument 2: expected float");
	}
	obj->y = y_val;

	JSValue ret = JS_NewObjectClass(ctx, js_Vector2_class_id);
	JS_SetOpaque(ret, obj);
	return ret;
}

void js_define_raylib_Vector2_struct(JSContext *ctx, JSValue target) {
	JSRuntime *rt = JS_GetRuntime(ctx);
	JS_NewClassID(rt, &js_Vector2_class_id);
	JS_NewClass(rt, js_Vector2_class_id, &js_Vector2_class_def);
	const JSValue proto = JS_NewObject(ctx);
	JS_SetPropertyFunctionList(ctx, proto, js_Vector2_funcs, 2);
	JS_SetClassProto(ctx, js_Vector2_class_id, proto);
	const JSValue constructor = JS_NewCFunction2(ctx, js_Vector2_constructor, "Vector2", 0, JS_CFUNC_constructor, 0);
	JS_SetPropertyStr(ctx, target, "Vector2", constructor);
}

static void js_Color_finalizer(JSRuntime *rt, const JSValue val) {
	Color *ptr = static_cast<Color *>(JS_GetOpaque(val, js_Color_class_id));
	if (ptr) { js_free_rt(rt, ptr); }
}

static JSValue js_Color_get_r(JSContext *ctx, const JSValueConst val) {
	const Color *obj = static_cast<Color *>(JS_GetOpaque2(ctx, val, js_Color_class_id));
	if (!obj) { return JS_EXCEPTION; }
	const JSValue ret = JS_NewUint32(ctx, obj->r);
	return ret;
}

static JSValue js_Color_get_g(JSContext *ctx, const JSValueConst val) {
	const Color *obj = static_cast<Color *>(JS_GetOpaque2(ctx, val, js_Color_class_id));
	if (!obj) { return JS_EXCEPTION; }
	const JSValue ret = JS_NewUint32(ctx, obj->g);
	return ret;
}

static JSValue js_Color_get_b(JSContext *ctx, const JSValueConst val) {
	const Color *obj = static_cast<Color *>(JS_GetOpaque2(ctx, val, js_Color_class_id));
	if (!obj) { return JS_EXCEPTION; }
	const JSValue ret = JS_NewUint32(ctx, obj->b);
	return ret;
}

static JSValue js_Color_get_a(JSContext *ctx, const JSValueConst val) {
	const Color *obj = static_cast<Color *>(JS_GetOpaque2(ctx, val, js_Color_class_id));
	if (!obj) { return JS_EXCEPTION; }
	const JSValue ret = JS_NewUint32(ctx, obj->a);
	return ret;
}

static JSValue js_Color_set_r(JSContext *ctx, const JSValueConst this_val, const JSValueConst val) {
	Color *obj = static_cast<Color *>(JS_GetOpaque(this_val, js_Color_class_id));
	if (!obj) { return JS_EXCEPTION; }
	uint32_t result;
	JS_ToUint32(ctx, &result, val);
	obj->r = result;
	return JS_UNDEFINED;
}

static JSValue js_Color_set_g(JSContext *ctx, const JSValueConst this_val, const JSValueConst val) {
	Color *obj = static_cast<Color *>(JS_GetOpaque(this_val, js_Color_class_id));
	if (!obj) { return JS_EXCEPTION; }
	uint32_t result;
	JS_ToUint32(ctx, &result, val);
	obj->g = result;
	return JS_UNDEFINED;
}

static JSValue js_Color_set_b(JSContext *ctx, const JSValueConst this_val, const JSValueConst val) {
	Color *obj = static_cast<Color *>(JS_GetOpaque(this_val, js_Color_class_id));
	if (!obj) { return JS_EXCEPTION; }
	uint32_t result;
	JS_ToUint32(ctx, &result, val);
	obj->b = result;
	return JS_UNDEFINED;
}

static JSValue js_Color_set_a(JSContext *ctx, const JSValueConst this_val, const JSValueConst val) {
	Color *obj = static_cast<Color *>(JS_GetOpaque(this_val, js_Color_class_id));
	if (!obj) { return JS_EXCEPTION; }
	uint32_t result;
	JS_ToUint32(ctx, &result, val);
	obj->a = result;
	return JS_UNDEFINED;
}

static constexpr JSCFunctionListEntry js_Color_funcs[] = {
	JS_CGETSET_DEF("r", js_Color_get_r, js_Color_set_r),
	JS_CGETSET_DEF("g", js_Color_get_g, js_Color_set_g),
	JS_CGETSET_DEF("b", js_Color_get_b, js_Color_set_b),
	JS_CGETSET_DEF("a", js_Color_get_a, js_Color_set_a),
};

static constexpr JSClassDef js_Color_class_def = {
	.class_name = "Color",
	.finalizer = js_Color_finalizer,
};

static JSValue js_Color_constructor(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
	Color *obj = static_cast<Color *>(js_malloc(ctx, sizeof(Color)));
	if (!obj) { return JS_EXCEPTION; }

	uint32_t r_val;
	if (JS_ToUint32(ctx, &r_val, argv[0]) < 0) {
		js_free(ctx, obj);
		return JS_ThrowTypeError(ctx, "Argument 1: expected unsigned char");
	}
	obj->r = r_val;

	uint32_t g_val;
	if (JS_ToUint32(ctx, &g_val, argv[1]) < 0) {
		js_free(ctx, obj);
		return JS_ThrowTypeError(ctx, "Argument 2: expected unsigned char");
	}
	obj->g = g_val;

	uint32_t b_val;
	if (JS_ToUint32(ctx, &b_val, argv[2]) < 0) {
		js_free(ctx, obj);
		return JS_ThrowTypeError(ctx, "Argument 3: expected unsigned char");
	}
	obj->b = b_val;

	uint32_t a_val;
	if (JS_ToUint32(ctx, &a_val, argv[3]) < 0) {
		js_free(ctx, obj);
		return JS_ThrowTypeError(ctx, "Argument 4: expected unsigned char");
	}
	obj->a = a_val;

	JSValue ret = JS_NewObjectClass(ctx, js_Color_class_id);
	JS_SetOpaque(ret, obj);
	return ret;
}

void js_define_raylib_Color_struct(JSContext *ctx, JSValue target) {
	JSRuntime *rt = JS_GetRuntime(ctx);
	JS_NewClassID(rt, &js_Color_class_id);
	JS_NewClass(rt, js_Color_class_id, &js_Color_class_def);
	const JSValue proto = JS_NewObject(ctx);
	JS_SetPropertyFunctionList(ctx, proto, js_Color_funcs, 4);
	JS_SetClassProto(ctx, js_Color_class_id, proto);
	const JSValue constructor = JS_NewCFunction2(ctx, js_Color_constructor, "Color", 0, JS_CFUNC_constructor, 0);
	JS_SetPropertyStr(ctx, target, "Color", constructor);
}

void js_define_raylib_structs(JSContext *ctx, JSValue target) {
	js_define_raylib_Vector2_struct(ctx, target);
	js_define_raylib_Color_struct(ctx, target);
}
