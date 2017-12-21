//-
// ==========================================================================
// Copyright 1995,2006,2008 Autodesk, Inc. All rights reserved.
//
// Use of this software is subject to the terms of the Autodesk
// license agreement provided at the time of installation or download,
// or which otherwise accompanies this software in either electronic
// or hard copy form.
// ==========================================================================
//+

#include <maya/MGlobal.h>

#include "Platform.h"
#include "hlslSm3FXShader.h"

#include "ResourceManager.h"

const char header[] =
"///////////////////////////////////////////////////////////////////////////////\n"
"//\n"
"// Copyright 2003, ATI Technologies, Inc., All rights reserved.\n"
"//\n"
"// Permission to use, copy, modify, and distribute this software and its \n"
"// documentation for any purpose and without fee is hereby granted,\n"
"// provided that the above copyright notice appear in all copies and derivative\n"
"// works and that both the copyright notice and this permission notice appear in\n"
"// support documentation, and that the name of ATI Technologies, Inc. not be used\n"
"// in advertising or publicity pertaining to distribution of the software without\n"
"// specific, written prior permission.\n"
"//\n"
"///////////////////////////////////////////////////////////////////////////////\n"
"\n"
"// Ashli native operator -> GLSL\n"
"\n"
"float Add(float f0, float f1) { return f0 + f1; }\n"
"vec2 Add(float f, vec2 v) { return f + v; }\n"
"vec2 Add(vec2 v, float f) { return v + f; }\n"
"vec2 Add(vec2 v0,  vec2 v1) { return v0 + v1; }\n"
"vec3 Add(float f, vec3 v) { return f + v; }\n"
"vec3 Add(vec3 v, float f) { return v + f; }\n"
"vec3 Add(vec3 v0,  vec3 v1) { return v0 + v1; }\n"
"vec4 Add(float f, vec4 v) { return f + v; }\n"
"vec4 Add(vec4 v, float f) { return v + f; }\n"
"vec4 Add(vec4 v0,  vec4 v1) { return v0 + v1; }\n"
"mat2 Add(float f, mat2 m) { return m + f; }\n"
"mat2 Add(mat2 m, float f) { return m + f; }\n"
"mat2 Add(mat2 m0, mat2 m1) { return m0 + m1; }\n"
"\n"
"float Subtract(float f0, float f1) { return f0 - f1; }\n"
"vec2 Subtract(float f, vec2 v) { return f - v; }\n"
"vec2 Subtract(vec2 v, float f) { return v - f; }\n"
"vec2 Subtract(vec2 v0, vec2 v1) { return v0 - v1; }\n"
"vec3 Subtract(float f, vec3 v) { return f - v; }\n"
"vec3 Subtract(vec3 v, float f) { return v - f; }\n"
"vec3 Subtract(vec3 v0, vec3 v1) { return v0 - v1; }\n"
"vec4 Subtract(float f, vec4 v) { return f - v; }\n"
"vec4 Subtract(vec4 v, float f) { return v - f; }\n"
"vec4 Subtract(vec4 v0, vec4 v1) { return v0 - v1; }\n"
"mat2 Subtract(float f, mat2 m) { return f - m; }\n"
"mat2 Subtract(mat2 m, float f) { return m - f; }\n"
"mat2 Subtract(mat2 m0, mat2 m1) { return m0 - m1; }\n"
"\n"
"float Multiply(float f0, float f1) { return f0 * f1; }\n"
"vec2 Multiply(float f, vec2 v) { return f * v; }\n"
"vec2 Multiply(vec2 v, float f) { return v * f; }\n"
"vec2 Multiply(vec2 v0, vec2 v1) { return v0 * v1; }\n"
"vec3 Multiply(float f, vec3 v) { return f * v; }\n"
"vec3 Multiply(vec3 v, float f) { return v * f; }\n"
"vec3 Multiply(vec3 v0, vec3 v1) { return v0 * v1; }\n"
"vec4 Multiply(float f, vec4 v) { return f * v; }\n"
"vec4 Multiply(vec4 v, float f) { return v * f; }\n"
"vec4 Multiply(vec4 v0, vec4 v1) { return v0 * v1; }\n"
"mat2 Multiply(float f, mat2 m) { return f * m; }\n"
"mat2 Multiply(mat2 m, float f) { return m * f; }\n"
"vec2 Multiply(mat2 m, vec2 v) { return m * v; }\n"
"vec2 Multiply(vec2 v, mat2 m) { return v * m; }\n"
"mat2 Multiply(mat2 m0, mat2 m1) { return m0 * m1; }\n"
"mat3 Multiply(float f, mat3 m) { return f * m; }\n"
"mat3 Multiply(mat3 m, float f) { return m * f; }\n"
"vec3 Multiply(mat3 m, vec3 v) { return m * v; }\n"
"vec3 Multiply(vec3 v, mat3 m) { return v * m; }\n"
"mat3 Multiply(mat3 m0, mat3 m1) { return m0 * m1; }\n"
"mat4 Multiply(float f, mat4 m) { return f * m; }\n"
"mat4 Multiply(mat4 m, float f) { return m * f; }\n"
"vec4 Multiply(mat4 m, vec4 v) { return m * v; }\n"
"vec4 Multiply(vec4 v, mat4 m) { return v * m; }\n"
"mat4 Multiply(mat4 m0, mat4 m1) { return m0 * m1; }\n"
"\n"
"float Divide(float f0, float f1) { return f0 / f1; }\n"
"vec2 Divide(vec2 v, float f) { return v / f; }\n"
"vec2 Divide(float f, vec2 v) { return f / v; }\n"
"vec2 Divide(vec2 v0, vec2 v1) { return v0 / v1; }\n"
"vec3 Divide(vec3 v, float f) { return v / f; }\n"
"vec3 Divide(float f, vec3 v) { return f / v; }\n"
"vec3 Divide(vec3 v0, vec3 v1) { return v0 / v1; }\n"
"vec4 Divide(vec4 v, float f) { return v / f; }\n"
"vec4 Divide(float f, vec4 v) { return f / v; }\n"
"vec4 Divide(vec4 v0, vec4 v1) { return v0 / v1; }\n"
"mat2 Divide(mat2 m, float f) { return m / f; }\n"
"mat2 Divide(float f, mat2 m) { return f / m; }\n"
"mat2 Divide(mat2 m0, mat2 m1) { return m0 / m1; }\n"
"mat3 Divide(mat3 m, float f) { return m / f; }\n"
"mat3 Divide(float f, mat3 m) { return f / m; }\n"
"mat3 Divide(mat3 m0, mat3 m1) { return m0 / m1; }\n"
"mat4 Divide(mat4 m, float f) { return m / f; }\n"
"mat4 Divide(float f, mat4 m) { return f / m; }\n"
"mat4 Divide(mat4 m0, mat4 m1) { return m0 / m1; }\n"
"\n"
"float MultiplyAdd(float f0, float f1, float f2) { return f0 * f1 + f2; }\n"
"vec2 MultiplyAdd(float f0, vec2 v1, vec2 v2) { return f0 * v1 + v2; }\n"
"vec3 MultiplyAdd(float f0, vec3 v1, vec3 v2) { return f0 * v1 + v2; }\n"
"vec4 MultiplyAdd(float f0, vec4 v1, vec4 v2) { return f0 * v1 + v2; }\n"
"vec2 MultiplyAdd(vec2 v0, float f1, vec2 v2) { return v0 * f1 + v2; }\n"
"vec3 MultiplyAdd(vec3 v0, float f1, vec3 v2) { return v0 * f1 + v2; }\n"
"vec4 MultiplyAdd(vec4 v0, float f1, vec4 v2) { return v0 * f1 + v2; }\n"
"vec2 MultiplyAdd(vec2 v0, vec2 v1, float f2) { return v0 * v1 + f2; }\n"
"vec3 MultiplyAdd(vec3 v0, vec3 v1, float f2) { return v0 * v1 + f2; }\n"
"vec4 MultiplyAdd(vec4 v0, vec4 v1, float f2) { return v0 * v1 + f2; }\n"
"vec2 MultiplyAdd(vec2 v0, float f1, float f2) { return v0 * f1 + f2; }\n"
"vec3 MultiplyAdd(vec3 v0, float f1, float f2) { return v0 * f1 + f2; }\n"
"vec4 MultiplyAdd(vec4 v0, float f1, float f2) { return v0 * f1 + f2; }\n"
"vec2 MultiplyAdd(float f0, vec2 v1, float f2) { return f0 * v1 + f2; }\n"
"vec2 MultiplyAdd(float f0, float f1, vec2 v2) { return f0 * f1 + v2; }\n"
"vec3 MultiplyAdd(float f0, float f1, vec3 v2) { return f0 * f1 + v2; }\n"
"vec4 MultiplyAdd(float f0, float f1, vec4 v2) { return f0 * f1 + v2; }\n"
"vec2 MultiplyAdd(vec2 v0, vec2 v1, vec2 v2) { return v0 * v1 + v2; }\n"
"vec3 MultiplyAdd(vec3 v0, vec3 v1, vec3 v2) { return v0 * v1 + v2; }\n"
"vec4 MultiplyAdd(vec4 v0, vec4 v1, vec4 v2) { return v0 * v1 + v2; }\n"
"\n"
"float Negate(float f) { return -f; }\n"
"vec2 Negate(vec2 v) { return -v; }\n"
"vec3 Negate(vec3 v) { return -v; }\n"
"vec4 Negate(vec4 v) { return -v; }\n"
"mat2 Negate(mat2 m) { return -m; }\n"
"mat3 Negate(mat3 m) { return -m; }\n"
"mat4 Negate(mat4 m) { return -m; }\n"
"\n"
"float Reciprocal(float f) { return 1.0 / f; }\n"
"vec2 Reciprocal(vec2 v) { return 1.0 / v; }\n"
"vec3 Reciprocal(vec3 v) { return 1.0 / v; }\n"
"vec4 Reciprocal(vec4 v) { return 1.0 / v; }\n"
"mat2 Reciprocal(mat2 m) { return 1.0 / m; }\n"
"mat3 Reciprocal(mat3 m) { return 1.0 / m; }\n"
"mat4 Reciprocal(mat4 m) { return 1.0 / m; }\n"
"\n"
"float ReciprocalSquareRoot(float f) { return inversesqrt(f); }\n"
"vec2 ReciprocalSquareRoot(vec2 v) { return inversesqrt(v); }\n"
"vec3 ReciprocalSquareRoot(vec3 v) { return inversesqrt(v); }\n"
"vec4 ReciprocalSquareRoot(vec4 v) { return inversesqrt(v); }\n"
"mat2 ReciprocalSquareRoot(mat2 m) { return mat2(inversesqrt(m[0]), inversesqrt(m[1])); } \n"
"mat3 ReciprocalSquareRoot(mat3 m) { return mat3(inversesqrt(m[0]), inversesqrt(m[1]), inversesqrt(m[2])); }\n"
"mat4 ReciprocalSquareRoot(mat4 m) { return mat4(inversesqrt(m[0]), inversesqrt(m[1]), inversesqrt(m[2]), inversesqrt(m[3])); } \n"
"\n"
"float Absolute(float f) { return abs(f); }\n"
"vec2 Absolute(vec2 v) { return abs(v); }\n"
"vec3 Absolute(vec3 v) { return abs(v); }\n"
"vec4 Absolute(vec4 v) { return abs(v); }\n"
"mat2 Absolute(mat2 m) { return mat2(abs(m[0]), abs(m[1])); } \n"
"mat3 Absolute(mat3 m) { return mat3(abs(m[0]), abs(m[1]), abs(m[2])); } \n"
"mat4 Absolute(mat4 m) { return mat4(abs(m[0]), abs(m[1]), abs(m[2]), abs(m[3])); }\n"
"\n"
"float Modulus(float f0, float f1) { return mod(f0, f1); } \n"
"vec2 Modulus(float f, vec2 v) { return mod(vec2(f), v); } \n"
"vec2 Modulus(vec2 v, float f) { return mod(v, f); } \n"
"vec2 Modulus(vec2 v0, vec2 v1) { return mod(v0, v1); }  \n"
"vec3 Modulus(float f, vec3 v) { return mod(vec3(f), v); } \n"
"vec3 Modulus(vec3 v, float f) { return mod(v, f); } \n"
"vec3 Modulus(vec3 v0, vec3 v1) { return mod(v0, v1); } \n"
"vec4 Modulus(float f, vec4 v) { return mod(vec4(f), v); }\n"
"vec4 Modulus(vec4 v, float f) { return mod(v, f); } \n"
"vec4 Modulus(vec4 v0, vec4 v1) { return mod(v0, v1); }\n"
"mat2 Modulus(float f, mat2 m) { return mat2(mod(vec2(f), m[0]), mod(vec2(f), m[1])); }\n"
"mat2 Modulus(mat2 m, float f) { return mat2(mod(m[0], vec2(f)), mod(m[1], vec2(f))); }\n"
"mat2 Modulus(mat2 m0, mat2 m1) { return mat2(mod(m0[0], m1[0]), mod(m0[1], m1[1])); } \n"
"mat3 Modulus(float f, mat3 m) { return mat3(mod(vec3(f), m[0]), mod(vec3(f), m[1]), mod(vec3(f), m[2])); }\n"
"mat3 Modulus(mat3 m, float f) { return mat3(mod(m[0], vec3(f)), mod(m[1], vec3(f)), mod(m[2], vec3(f))); }\n"
"mat3 Modulus(mat3 m0, mat3 m1) { return mat3(mod(m0[0], m1[0]), mod(m0[1], m1[1]), mod(m0[2], m1[2])); }\n"
"mat4 Modulus(float f, mat4 m) { return mat4(mod(vec4(f), m[0]), mod(vec4(f), m[1]), mod(vec4(f), m[2]), mod(vec4(f), m[3])); } \n"
"mat4 Modulus(mat4 m, float f) { return mat4(mod(m[0], vec4(f)), mod(m[1], vec4(f)), mod(m[2], vec4(f)), mod(m[3], vec4(f))); } \n"
"mat4 Modulus(mat4 m0, mat4 m1) { return mat4(mod(m0[0], m1[0]), mod(m0[1], m1[1]), mod(m0[2], m1[2]), mod(m0[3], m1[3])); } \n"
"\n"
"float Fraction(float f) { return fract(f); }\n"
"vec2 Fraction(vec2 v) { return fract(v); }\n"
"vec3 Fraction(vec3 v) { return fract(v); }\n"
"vec4 Fraction(vec4 v) { return fract(v); }\n"
"mat2 Fraction(mat2 m) { return mat2(fract(m[0]), fract(m[1])); }\n"
"mat3 Fraction(mat3 m) { return mat3(fract(m[0]), fract(m[1]), fract(m[2])); } \n"
"mat4 Fraction(mat4 m) { return mat4(fract(m[0]), fract(m[1]), fract(m[2]), fract(m[3])); }\n"
"\n"
"float Exponent(float f) { return exp2(f); }\n"
"vec2 Exponent(vec2 v) { return exp2(v); }\n"
"vec3 Exponent(vec3 v) { return exp2(v); }\n"
"vec4 Exponent(vec4 v) { return exp2(v); }\n"
"mat2 Exponent(mat2 m) { return mat2(exp2(m[0]), exp2(m[1])); } \n"
"mat3 Exponent(mat3 m) { return mat3(exp2(m[0]), exp2(m[1]), exp2(m[2])); }\n"
"mat4 Exponent(mat4 m) { return mat4(exp2(m[0]), exp2(m[1]), exp2(m[2]), exp2(m[3])); }\n"
"\n"
"float Power(float f0, float f1) { return pow(f0, f1); }  \n"
"vec2 Power(vec2 v, float f) { return pow(v, vec2(f)); }\n"
"vec2 Power(float f, vec2 v) { return pow(vec2(f), v); }\n"
"vec2 Power(vec2 v0, vec2 v1) { return pow(v0, v1); }\n"
"vec3 Power(vec3 v, float f) { return pow(v, vec3(f)); }\n"
"vec3 Power(float f, vec3 v) { return pow(vec3(f), v); }\n"
"vec3 Power(vec3 v0, vec3 v1) { return pow(v0, v1); }\n"
"vec4 Power(vec4 v, float f) { return pow(v, vec4(f)); }\n"
"vec4 Power(float f, vec4 v) { return pow(vec4(f), v); }\n"
"vec4 Power(vec4 v0, vec4 v1) { return pow(v0, v1); }\n"
"mat2 Power(mat2 m, float f) { return mat2(pow(m[0], vec2(f)), pow(m[1], vec2(f))); }\n"
"mat2 Power(float f, mat2 m) { return mat2(pow(vec2(f), m[0]), pow(vec2(f), m[1])); }\n"
"mat2 Power(mat2 m0, mat2 m1) { return mat2(pow(m0[0], m1[0]), pow(m0[1], m1[1])); }\n"
"mat3 Power(mat3 m, float f) { return mat3(pow(m[0], vec3(f)), pow(m[1], vec3(f)), pow(m[2], vec3(f))); }\n"
"mat3 Power(float f, mat3 m) { return mat3(pow(vec3(f), m[0]), pow(vec3(f), m[1]), pow(vec3(f), m[2])); }\n"
"mat3 Power(mat3 m0, mat3 m1) { return mat3(pow(m0[0], m1[0]), pow(m0[1], m1[1]), pow(m0[2], m1[2])); }\n"
"mat4 Power(mat4 m, float f) { return mat4(pow(m[0], vec4(f)), pow(m[1], vec4(f)), pow(m[2], vec4(f)), pow(m[3], vec4(f))); }\n"
"mat4 Power(float f, mat4 m) { return mat4(pow(vec4(f), m[0]), pow(vec4(f), m[1]), pow(vec4(f), m[2]), pow(vec4(f), m[3])); }\n"
"mat4 Power(mat4 m0, mat4 m1) { return mat4(pow(m0[0], m1[0]), pow(m0[1], m1[1]), pow(m0[2], m1[2]), pow(m0[3], m1[3])); }\n"
"\n"
"float Log(float f) { return log2(f); }\n"
"vec2 Log(vec2 v) { return log2(v); }\n"
"vec3 Log(vec3 v) { return log2(v); }\n"
"vec4 Log(vec4 v) { return log2(v); }\n"
"mat2 Log(mat2 m) { return mat2(log2(m[0]), log2(m[1])); } \n"
"mat3 Log(mat3 m) { return mat3(log2(m[0]), log2(m[1]), log2(m[2])); } \n"
"mat4 Log(mat4 m) { return mat4(log2(m[0]), log2(m[1]), log2(m[2]), log2(m[3])); } \n"
"\n"
"float Max(float f0, float f1) { return max(f0, f1); }\n"
"vec2 Max(float f, vec2 v) { return max(vec2(f), v); }\n"
"vec2 Max(vec2 v, float f) { return max(v, f); }\n"
"vec2 Max(vec2 v0, vec2 v1) { return max(v0, v1); }\n"
"vec3 Max(float f, vec3 v) { return max(vec3(f), v); }\n"
"vec3 Max(vec3 v, float f) { return max(v, f); }\n"
"vec3 Max(vec3 v0, vec3 v1) { return max(v0, v1); }\n"
"vec4 Max(float f, vec4 v) { return max(vec4(f), v); }\n"
"vec4 Max(vec4 v, float f) { return max(v, f); }\n"
"vec4 Max(vec4 v0, vec4 v1) { return max(v0, v1); }\n"
"mat2 Max(float f, mat2 m) { return mat2(max(vec2(f), m[0]), max(vec2(f), m[1])); } \n"
"mat2 Max(mat2 m, float f) { return mat2(max(m[0], f),max(m[1], f)); } \n"
"mat2 Max(mat2 m0, mat2 m1) { return mat2(max(m0[0], m1[0]), max(m0[1], m1[1])); } \n"
"mat3 Max(float f, mat3 m) { return mat3(max(vec3(f), m[0]), max(vec3(f), m[1]), max(vec3(f), m[2])); } \n"
"mat3 Max(mat3 m, float f) { return mat3(max(m[0], f), max(m[1], f), max(m[2], f)); } \n"
"mat3 Max(mat3 m0, mat3 m1) { return mat3(max(m0[0], m1[0]), max(m0[1], m1[1]), max(m0[2], m1[2])); } \n"
"mat4 Max(float f, mat4 m) { return mat4(max(vec4(f), m[0]), max(vec4(f), m[1]), max(vec4(f), m[2]), max(vec4(f), m[3])); } \n"
"mat4 Max(mat4 m, float f) { return mat4(max(m[0], f), max(m[1], f), max(m[2], f), max(m[3], f)); } \n"
"mat4 Max(mat4 m0, mat4 m1) { return mat4(max(m0[0], m1[0]), max(m0[1], m1[1]), max(m0[2], m1[2]), max(m0[3], m1[3])); } \n"
"\n"
"float Min(float f0, float f1) { return min(f0, f1); }\n"
"vec2 Min(float f, vec2 v) { return min(vec2(f), v); }\n"
"vec2 Min(vec2 v, float f) { return min(v, f); }\n"
"vec2 Min(vec2 v0, vec2 v1) { return min(v0, v1); }\n"
"vec3 Min(float f, vec3 v) { return min(vec3(f), v); }\n"
"vec3 Min(vec3 v, float f) { return min(v, f); }\n"
"vec3 Min(vec3 v0, vec3 v1) { return min(v0, v1); }\n"
"vec4 Min(float f, vec4 v) { return min(vec4(f), v); }\n"
"vec4 Min(vec4 v, float f) { return min(v, f); }\n"
"vec4 Min(vec4 v0, vec4 v1) { return min(v0, v1); }\n"
"mat2 Min(float f, mat2 m) { return mat2(min(vec2(f), m[0]), min(vec2(f), m[1])); } \n"
"mat2 Min(mat2 m, float f) { return mat2(min(m[0], f), min(m[1], f)); } \n"
"mat2 Min(mat2 m0, mat2 m1) { return mat2(min(m0[0], m1[0]), min(m0[1], m1[1])); } \n"
"mat3 Min(float f, mat3 m) { return mat3(min(vec3(f), m[0]), min(vec3(f), m[1]), min(vec3(f), m[2])); } \n"
"mat3 Min(mat3 m, float f) { return mat3(min(m[0], f), min(m[1], f), min(m[2], f)); } \n"
"mat3 Min(mat3 m0, mat3 m1) { return mat3(min(m0[0], m1[0]), min(m0[1], m1[1]), min(m0[2], m1[2])); } \n"
"mat4 Min(float f, mat4 m) { return mat4(min(vec4(f), m[0]), min(vec4(f), m[1]), min(vec4(f), m[2]), min(vec4(f), m[3])); } \n"
"mat4 Min(mat4 m, float f) { return mat4(min(m[0],f),min(m[1], f),min(m[2], f),min(m[3], f)); }\n"
"mat4 Min(mat4 m0, mat4 m1) { return mat4(min(m0[0], m1[0]), min(m0[1], m1[1]), min(m0[2], m1[2]), min(m0[3], m1[3])); }\n"
"\n"
"float Clamp(float f) { return clamp(f, 0.0, 1.0); }\n"
"vec2 Clamp(vec2 v) { return clamp(v, 0.0, 1.0); }\n"
"vec3 Clamp(vec3 v) { return clamp(v, 0.0, 1.0); }\n"
"vec4 Clamp(vec4 v) { return clamp(v, 0.0, 1.0); }\n"
"mat2 Clamp(mat2 m) { return mat2(clamp( m[0], 0.0, 1.0), clamp(m[1], 0.0, 1.0)); }\n"
"mat3 Clamp(mat3 m) { return mat3(clamp( m[0], 0.0, 1.0), clamp(m[1], 0.0, 1.0), clamp(m[2], 0.0, 1.0)); } \n"
"mat4 Clamp(mat4 m) { return mat4(clamp( m[0], 0.0, 1.0), clamp(m[1], 0.0, 1.0), clamp(m[2], 0.0, 1.0), clamp(m[3], 0.0, 1.0 )); } \n"
"\n"
"vec2 Normalize(vec2 v) { return normalize(v); }\n"
"vec3 Normalize(vec3 v) { return normalize(v); }\n"
"vec4 Normalize(vec4 v) { return normalize(v); }\n"
"\n"
"float DotProduct(vec2 v0, vec2 v1) { return dot(v0, v1); }\n"
"float DotProduct(vec3 v0, vec3 v1) { return dot(v0, v1); }\n"
"float DotProduct(vec4 v0, vec4 v1) { return dot(v0, v1); }\n"
"\n"
"vec3 CrossProduct(vec3 v0, vec3 v1) { return cross(v0, v1); }\n"
"\n"
"float LinearInterpolate(float a, float f0, float f1) { return mix(f0, f1, a); }\n"
"vec2 LinearInterpolate(float a, vec2 v0, vec2 v1) { return mix(v0, v1, a); }\n"
"vec3 LinearInterpolate(float a, vec3 v0, vec3 v1) { return mix(v0, v1, a); }\n"
"vec4 LinearInterpolate(float a, vec4 v0, vec4 v1) { return mix(v0, v1, a); }\n"
"vec2 LinearInterpolate(vec2 a, vec2 v0, vec2 v1) { return mix(v0, v1, a); }\n"
"vec3 LinearInterpolate(vec3 a, vec3 v0, vec3 v1) { return mix(v0, v1, a); }\n"
"vec4 LinearInterpolate(vec4 a, vec4 v0, vec4 v1) { return mix(v0, v1, a); }\n"
"mat2 LinearInterpolate(mat2 a, mat2 m0, mat2 m1) { return mat2(mix(m0[0], m1[0], a[0]), mix(m0[1], m1[1], a[1])); }\n"
"mat3 LinearInterpolate(mat3 a, mat3 m0, mat3 m1) { return mat3(mix(m0[0], m1[0], a[0]), mix(m0[1], m1[1], a[1]), mix(m0[2], m1[2], a[2])); }\n"
"mat4 LinearInterpolate(mat4 a, mat4 m0, mat4 m1) { return mat4(mix(m0[0], m1[0], a[0]), mix(m0[1], m1[1], a[1]), mix(m0[2], m1[2], a[2]), mix(m0[3], m1[3], a[3])); }\n"
"\n"
"float Sine(float f) { return sin(f); }\n"
"vec2 Sine(vec2 v) { return sin(v); }\n"
"vec3 Sine(vec3 v) { return sin(v); }\n"
"vec4 Sine(vec4 v) { return sin(v); }\n"
"mat2 Sine(mat2 m) { return mat2(sin(m[0]), sin(m[1])); }\n"
"mat3 Sine(mat3 m) { return mat3(sin(m[0]), sin(m[1]), sin(m[2])); }\n"
"mat4 Sine(mat4 m) { return mat4(sin(m[0]), sin(m[1]), sin(m[2]), sin(m[3])); }\n"
"float Cosine(float f) { return cos(f); }\n"
"vec2 Cosine(vec2 v) { return cos(v); }\n"
"vec3 Cosine(vec3 v) { return cos(v); }\n"
"vec4 Cosine(vec4 v) { return cos(v); }\n"
"mat2 Cosine(mat2 m) { return mat2(cos(m[0]), cos(m[1])); }\n"
"mat3 Cosine(mat3 m) { return mat3(cos(m[0]), cos(m[1]), cos(m[2])); }\n"
"mat4 Cosine(mat4 m) { return mat4(cos(m[0]), cos(m[1]), cos(m[2]), cos(m[3])); }\n"
"			\n"
"bool GreaterThan(float f0, float f1) { return f0 > f1; }\n"
"bvec2 GreaterThan(vec2 v0, vec2 v1) { return greaterThan( v0, v1 ); }\n"
"bvec3 GreaterThan(vec3 v0, vec3 v1) { return greaterThan( v0, v1 ); }\n"
"bvec4 GreaterThan(vec4 v0, vec4 v1) { return greaterThan( v0, v1 ); }\n"
"bool GreaterThanOrEqual(float f0, float f1) { return f0 >= f1; }\n"
"bvec2 GreaterThanOrEqual(vec2 v0, vec2 v1) { return greaterThanEqual( v0, v1 ); } \n"
"bvec3 GreaterThanOrEqual(vec3 v0, vec3 v1) { return greaterThanEqual( v0, v1 ); } \n"
"bvec4 GreaterThanOrEqual(vec4 v0, vec4 v1) { return greaterThanEqual( v0, v1 ); }\n"
"bool LessThan(float f0, float f1) { return f0 < f1; }\n"
"bvec2 LessThan(vec2 v0, vec2 v1) { return lessThan( v0, v1 ); } \n"
"bvec3 LessThan(vec3 v0, vec3 v1) { return lessThan( v0, v1 ); } \n"
"bvec4 LessThan(vec4 v0, vec4 v1) { return lessThan( v0, v1 ); }\n"
"bool LessThanOrEqual(float f0, float f1) { return f0 <= f1; }\n"
"bvec2 LessThanOrEqual(vec2 v0, vec2 v1) { return lessThanEqual( v0, v1 ); } \n"
"bvec3 LessThanOrEqual(vec3 v0, vec3 v1) { return lessThanEqual( v0, v1 ); } \n"
"bvec4 LessThanOrEqual(vec4 v0, vec4 v1) { return lessThanEqual( v0, v1 ); }\n"
"bool Equal(float f0, float f1) { return f0 == f1; }\n"
"bvec2 Equal(vec2 v0, vec2 v1) { return equal( v0, v1 ); } \n"
"bvec3 Equal(vec3 v0, vec3 v1) { return equal( v0, v1 ); } \n"
"bvec4 Equal(vec4 v0, vec4 v1) { return equal( v0, v1 ); }\n"
"bool NotEqual(float f0, float f1) { return f0 != f1; }\n"
"bvec2 NotEqual(vec2 v0, vec2 v1) { return notEqual( v0, v1 ); } \n"
"bvec3 NotEqual(vec3 v0, vec3 v1) { return notEqual( v0, v1 ); } \n"
"bvec4 NotEqual(vec4 v0, vec4 v1) { return notEqual( v0, v1 ); }\n"
"\n"
"bool LogicalNot(float f) { return !bool(f); }\n"
"#define NOT2(v) v.x = !v.x; v.y = !v.y\n"
"bvec2 LogicalNot(vec2 v) { bvec2 t = bvec2(v); NOT2(t); return t; }\n"
"#define NOT3(v) v.x = !v.x; v.y = !v.y; v.x = !v.z\n"
"bvec3 LogicalNot(vec3 v) { bvec3 t = bvec3(v); NOT3(t); return t; }\n"
"#define NOT4(v) v.x = !v.x; v.y = !v.y; v.x = !v.z; v.w = !v.w\n"
"bvec4 LogicalNot(vec4 v) { bvec4 t = bvec4(v); NOT4(t); return t; }\n"
"bool LogicalAnd(float f0, float f1) { return bool(f0) && bool(f1); }\n"
"#define AND2(v0, v1) v0.x = v0.x && v1.x; v0.y = v0.y && v1.y\n"
"bvec2 LogicalAnd(vec2 v0, vec2 v1) { bvec2 t0 = bvec2(v0); bvec2 t1 = bvec2(v1); AND2(t0, t1); return t0; }\n"
"#define AND3(v0, v1) v0.x = v0.x && v1.x; v0.y = v0.y && v1.y; v0.z = v0.z && v1.z\n"
"bvec3 LogicalAnd(vec3 v0, vec3 v1) { bvec3 t0 = bvec3(v0); bvec3 t1 = bvec3(v1); AND3(t0, t1); return t0; }\n"
"#define AND4(v0, v1) v0.x = v0.x && v1.x; v0.y = v0.y && v1.y; v0.z = v0.z && v1.z; v0.w = v0.w && v1.w\n"
"bvec4 LogicalAnd(vec4 v0, vec4 v1) { bvec4 t0 = bvec4(v0); bvec4 t1 = bvec4(v1); AND4(t0, t1); return t0; }\n"
"bool LogicalOr(float f0, float f1) { return bool(f0) || bool(f1); }\n"
"#define OR2(v0, v1) v0.x = v0.x || v1.x; v0.y = v0.y || v1.y \n"
"bvec2  LogicalOr(vec2 v0, vec2 v1) { bvec2 t0 = bvec2(v0); bvec2 t1 = bvec2(v1); OR2(t0, t1); return t0; }\n"
"#define OR3(v0, v1) v0.x = v0.x || v1.x; v0.y = v0.y || v1.y; v0.z = v0.z || v1.z\n"
"bvec3  LogicalOr(vec3 v0, vec3 v1) { bvec3 t0 = bvec3(v0); bvec3 t1 = bvec3(v1); OR3(t0, t1); return t0; }\n"
"#define OR4(v0, v1) v0.x = v0.x || v1.x; v0.y = v0.y || v1.y; v0.z = v0.z || v1.z; v0.w = v0.w || v1.w\n"
"bvec4  LogicalOr(vec4 v0, vec4 v1) { bvec4 t0 = bvec4(v0); bvec4 t1 = bvec4(v1); OR4(t0, t1); return t0; }\n"
"\n"
"float MultiChoice(bool cond, float f0, float f1) { return (cond ? f0 : f1); }\n"
"vec2 MultiChoice(bool cond, vec2 v0, vec2 v1) { return (cond ? v0 : v1); }\n"
"vec3 MultiChoice(bool cond, vec3 v0, vec3 v1) { return (cond ? v0 : v1); }\n"
"vec4 MultiChoice(bool cond, vec4 v0, vec4 v1) { return (cond ? v0 : v1); }\n"
"mat2 MultiChoice(bool cond, mat2 m0, mat2 m1) { return (cond ? m0 : m1); }\n"
"mat3 MultiChoice(bool cond, mat3 m0, mat3 m1) { return (cond ? m0 : m1); }\n"
"mat4 MultiChoice(bool cond, mat4 m0, mat4 m1) { return (cond ? m0 : m1); }\n"
"\n"
"float TypeCast(int i) { return float(i); }\n"
"int TypeCast(float f) { return int(f); }\n"
"vec2 TypeCast(vec3 v) { return vec2(v); }\n"
"vec2 TypeCast(vec4 v) { return vec2(v); }\n"
"//vec3 TypeCast(vec4 v) { return vec3(v); }\n"
"//mat2 TypeCast(mat3 m) { return mat2(m); }\n"
"//mat2 TypeCast(mat4 m) { return mat2(m); }\n"
"//mat3 TypeCast(mat4 m) { return mat3(m); }\n"
"\n";

//
//
//
////////////////////////////////////////////////////////////////////////////////
hlslSm3FXShader::hlslSm3FXShader() :  m_techniqueCount(0), m_valid(false), m_stale(false), m_color(true), m_activePass(0), m_activeTechnique(0), m_normal(true),
m_tangent(true), m_binormal(true), m_texMask(0x1), m_error("") {

  
}

//
//
//
////////////////////////////////////////////////////////////////////////////////
hlslSm3FXShader::~hlslSm3FXShader() {
  for (std::vector<passState*>::iterator it=m_stateList.begin(); it<m_stateList.end(); it++) {
    delete *it;
  }

  deleteShaders();
}

//
//
//
////////////////////////////////////////////////////////////////////////////////
void hlslSm3FXShader::deleteShaders() {

	//these assume destroying object 0 is OK

	//schedule all the programs for delete
	{
		for (std::vector<GLuint>::iterator it=m_programList.begin(); it<m_programList.end(); it++) {
			ResourceManager::destroyProgram( *it);
		}
	}
	m_programList.clear();

	//schedule all the vertex shaders for delete
	{
		for (std::vector<GLuint>::iterator it=m_vShaderList.begin(); it<m_vShaderList.end(); it++) {
			ResourceManager::destroyProgram( *it);
		}
	}
	m_vShaderList.clear();

	//schedule all the fragment shaders for delete
	{
		for (std::vector<GLuint>::iterator it=m_fShaderList.begin(); it<m_fShaderList.end(); it++) {
			ResourceManager::destroyProgram( *it);
		}
	}
	m_fShaderList.clear();
}

//
//
//
////////////////////////////////////////////////////////////////////////////////
bool hlslSm3FXShader::createFromFile( const char *filename) {
  /*
  m_error = ""; 
  m_fx = new IAshliFX;
  m_fx->init();
  m_fx->setBinding( IAshliFX::DXSL);
  m_fx->setFX( filename);  //may need to do some path searching here
  m_stale = true;

  m_observer = new stateObserver;
  m_fx->attach( (IObserveFX*)m_observer);

  if (!m_fx->parse()) {
    //should store a string describing the failure for query
    m_error = "Unable to load FX file\n  ";
    m_error += m_fx->getError();
    delete m_fx;
    m_fx = NULL;
    return false;
  }

  m_ashli = new IAshli;
  m_ashli->setNative(IAshli::DXSL);
  m_ashli->setFlag( IAshli::UnpackedScalars, true);
  m_ashli->setFlag( IAshli::ContiguousMatrix, true);
  m_ashli->setFlag( IAshli::ContiguousArray, true);
  m_ashli->setFlag( IAshli::MultiPass, false);
  m_ashli->init( IAshli::Stream, IAshli::GL, IAshli::Stream);

  if ( !m_fx->isVertexNull( 0, 0)) {
    m_ashli->addShaderItem( m_fx->getVertexShader( 0, 0));
    m_ashli->addShaderInstance( m_ashli->addShader( IAshli::Vertex, m_fx->getVertexEntry( 0, 0)));
  }
  if ( !m_fx->isPixelNull( 0, 0)) {
    m_ashli->addShaderItem( m_fx->getPixelShader( 0, 0));
    m_ashli->addShaderInstance( m_ashli->addShader( IAshli::Pixel, m_fx->getPixelEntry( 0, 0)));
  }
  if ( m_ashli->invoke("")) {
    //compile succeeded 
    m_fx->setMetadata( 0, 0, m_ashli->getFormals());
    m_fx->setVertexAssembly( 0, 0, m_ashli->getVertexShader());
    m_fx->setPixelAssembly( 0, 0, m_ashli->getPixelShader());
    
  }
  else {
    //compile failed
    m_error = "Shader failed to compile\n";
    m_error += m_ashli->getError();
  }

  if ( (m_fx->getNumTechniques()) && (m_fx->getNumPasses(0) == 1)) {
  }
  else {
    //message about no valid first technique/incorrect number of passes
    delete m_fx;
    m_fx = NULL;
    m_error = "FX file lacked a valid shader";
    return false;
  }
  
  //this will move to bind time
  //if (!buildShaders())
  //  return false;

  if (!parseParameters())
    return false;
*/
  return true;

}

//
//
//
////////////////////////////////////////////////////////////////////////////////
bool hlslSm3FXShader::createFromFX( IAshliFX *fx) {
	m_error = ""; 
	m_stale = true;
  m_valid = false;

  if ( fx->getNumTechniques()) {
		//handle any per-technique processing, none presently required
	}
	else {
		//the effect lacks any technique, consider it invalid
		m_error = "FX file lacked a valid shader";
		return false;
	}

  if (!parseParameters(fx))
		return false;

  //need to extract all shader data from the fx file here 
  //these are to hold the ASHLIFX data
  m_techniqueCount = fx->getNumTechniques();
  m_techniqueNames.clear();
  m_passCount.clear();
  m_techniqueOffset.clear();
  m_vertexShaders.clear();
  m_fragmentShaders.clear();
  for (std::vector<passState*>::iterator it=m_stateList.begin(); it<m_stateList.end(); it++) {
    delete *it;
  }
  m_stateList.clear();
  int totalPasses =0;

  stateObserver *observer = new stateObserver;

  fx->attach( (IObserveFX*)observer);

  for (int ii=0; ii<m_techniqueCount; ii++) {
    int passCount = fx->getNumPasses(ii);
    m_techniqueOffset.push_back(totalPasses);
    ITechniqueFX tech;
    fx->getTechnique(ii, tech);
    m_techniqueNames.push_back(tech.getId());
    m_passCount.push_back(passCount);
    for (int jj=0; jj<passCount; jj++) {
      std::string vString;
      std::string fString;
      std::string orgVString;
      std::string orgFString;

      //allocate an ashli for this pass
      IAshli *ashli = new IAshli;
      ashli->setNative(IAshli::DXSL);
      ashli->setFlag( IAshli::UnpackedScalars, true);
      ashli->setFlag( IAshli::ContiguousMatrix, true);
      ashli->setFlag( IAshli::ContiguousArray, true);
      ashli->setFlag( IAshli::MultiPass, false);
      ashli->init( IAshli::Stream, IAshli::GL_SL10, IAshli::Stream);
      if ( !fx->isVertexNull( ii, jj)) {
        orgVString = fx->getVertexShader( ii, jj);
        ashli->addShaderItem( orgVString.c_str());
        ashli->addShaderInstance( ashli->addShader( IAshli::Vertex, fx->getVertexEntry( ii, jj)));
      }
      if ( !fx->isPixelNull( ii, jj)) {
        orgFString = fx->getPixelShader( ii, jj);
        ashli->addShaderItem( orgFString.c_str());
        ashli->addShaderInstance( ashli->addShader( IAshli::Pixel, fx->getPixelEntry( ii, jj)));
      }
      if ( ashli->invoke("")) {
        //compile succeeded 
        fx->setMetadata( ii, jj, ashli->getFormals());
        fx->setVertexAssembly( ii, jj, ashli->getVertexShader());
        fx->setPixelAssembly( ii, jj, ashli->getPixelShader());
        if (fx->getVertexAssembly( ii, jj))
          vString = fx->getVertexAssembly( ii, jj);
        if (fx->getPixelAssembly( ii, jj))
          fString = fx->getPixelAssembly( ii, jj);
      }
      else {
        //compile failed
        const char* error = ashli->getError();
        m_error = "Shader failed to compile\n";
        m_error += error;
        m_error += std::string("\n");
        // would like to print the offending text, but the parsing seems to difficult
      }

      m_vertexShaders.push_back(vString);
      m_fragmentShaders.push_back(fString);

      m_orgVertexShaders.push_back(orgVString);
      m_orgFragmentShaders.push_back(orgFString);

      //accumulate the state data
      m_stateList.push_back(new passState);
      observer->setPassMonitor(m_stateList.back());
      for (int kk=0; kk<fx->getNumStates( ii,jj); kk++) {
        fx->getStateItem( ii, jj, kk);
      }
      observer->finalizePassMonitor();
    }
    totalPasses += passCount;
  }
    
  fx->attach(NULL);
  delete observer;

  m_valid = true;

	return true;
}

//
//
//
////////////////////////////////////////////////////////////////////////////////
//new method, parsing parameters from AshliFX
bool hlslSm3FXShader::parseParameters(const IAshliFX *fx) {

  int passCount =0, ii;
  
  for (ii=0; ii<fx->getNumTechniques(); ii++) {
    passCount = std::max<int>( fx->getNumPasses(ii), passCount);
  }

  //process the exposed shader parameters
  for (ii=0; ii<fx->getNumParameters(); ii++) {
    IParameterFX parm;
    fx->getParameter( "", ii, parm);
    const char *usage = parm.getUsage();
    const char *type = parm.getType();
    const char *name = parm.getId();
    const char *semantic = parm.getSemantic();
    const char *expression = parm.getExpression();
    if (strcmp( "const", usage)) {
      if (strncmp( "sampler", type, 7)) {
        // this is a regular uniform (not a sampler)

        //should verify the compatibility of the following pieces of data
        shader::DataType dt = parseUniformType( type);
        shader::Semantic sm = parseUniformSemantic( semantic);
        uniform u;
        u.type = dt;
        u.handle.resize( passCount, -1);
        u.usage = sm;
        u.name = name;
        //parse the expression to extract a default value
        parseExpression( u, expression);

        //skip adding strings for now, maybe add them somewhere else later
        if (dt != shader::dtString)
          m_uniformList.push_back(u);
      }
      else {
        // this is a sampler uniform
        shader::SamplerType st = parseSamplerType( type);
        sampler s;
        s.texUnit.resize( passCount, -1);
        s.handle.resize( passCount, -1);
        s.type = st;
        s.name = name;
        m_samplerList.push_back(s);
      }
    }
    else {
      //don't know what else we could encounter, might want to create warnings
    }
  }

  return true;
}

//
//
//
////////////////////////////////////////////////////////////////////////////////
shader::DataType hlslSm3FXShader::parseUniformType( const char *type) {
  if (!strcmp( "float", type)) {
    return shader::dtFloat;
  }
  else if (!strcmp( "float1", type)) {
    return shader::dtFloat;
  }
  else if (!strcmp( "float2", type)) {
    return shader::dtVec2;
  }
  else if (!strcmp( "float3", type)) {
    return shader::dtVec3;
  }
  else if (!strcmp( "float4", type)) {
    return shader::dtVec4;
  }
  else if (!strcmp( "int", type)) {
    return shader::dtInt;
  }
  else if (!strcmp( "int1", type)) {
    return shader::dtInt;
  }
  else if (!strcmp( "int2", type)) {
    return shader::dtIVec2;
  }
  else if (!strcmp( "int3", type)) {
    return shader::dtIVec3;
  }
  else if (!strcmp( "int4", type)) {
    return shader::dtIVec4;
  }
  else if (!strcmp( "bool", type)) {
    return shader::dtBool;
  }
  else if (!strcmp( "bool1", type)) {
    return shader::dtBVec2;
  }
  else if (!strcmp( "bool2", type)) {
    return shader::dtBVec2;
  }
  else if (!strcmp( "bool3", type)) {
    return shader::dtBVec3;
  }
  else if (!strcmp( "bool4", type)) {
    return shader::dtBVec4;
  }
  else if (!strcmp( "float2x2", type)) {
    return shader::dtMat2;
  }
  else if (!strcmp( "float3x3", type)) {
    return shader::dtMat3;
  }
  else if (!strcmp( "float4x4", type)) {
    return shader::dtMat4;
  }
  
  return shader::dtUnknown;
}

//
//
//
////////////////////////////////////////////////////////////////////////////////
void hlslSm3FXShader::parseExpression( hlslSm3FXShader::uniform &u, const char *exp) {
  //this function should call a real parser, until then only handle a subset of types

  for (int ii=0; ii<16; ii++)
    u.fDefault[ii] = 0.0f;

  switch ( u.type) {
    case shader::dtInt:
      if ( 1 == sscanf( exp, " int ( %f )", &u.fDefault[0])) {
      }
      else if ( 1 == sscanf( exp, " int1 ( %f )", &u.fDefault[0])) {
      }
      else if ( 1 == sscanf( exp, " %f ", &u.fDefault[0])) {
      }
      else {
        u.fDefault[0] = 0.0f;
      }
      break;
    case shader::dtFloat:
      if ( 1 == sscanf( exp, " float ( %f )", &u.fDefault[0])) {
      }
      else if ( 1 == sscanf( exp, " float1 ( %f )", &u.fDefault[0])) {
      }
      else if ( 1 == sscanf( exp, " %f ", &u.fDefault[0])) {
      }
      else if ( 1 == sscanf( exp, " float ( %ff )", &u.fDefault[0])) {
      }
      else if ( 1 == sscanf( exp, " float1 ( %ff )", &u.fDefault[0])) {
      }
      else if ( 1 == sscanf( exp, " %ff ", &u.fDefault[0])) {
      }
      else if ( 1 == sscanf( exp, " { %f } ", &u.fDefault[0])) {
      }
      else if ( 1 == sscanf( exp, " { %ff } ", &u.fDefault[0])) {
      }
      else {
        u.fDefault[0] = 0.0f;
      }
      break;
    case shader::dtVec2:
      if ( 2 == sscanf( exp, " float2 ( %f , %f )", &u.fDefault[0], &u.fDefault[1])) {
      }
      else if ( 2 == sscanf( exp, " { %f , %f }", &u.fDefault[0], &u.fDefault[1])) {
      }
      else if ( 2 == sscanf( exp, " float2 ( %ff , %ff )", &u.fDefault[0], &u.fDefault[1])) {
      }
      else if ( 2 == sscanf( exp, " { %ff , %ff }", &u.fDefault[0], &u.fDefault[1])) {
      }
      else {
        u.fDefault[0] = 0.0f;
        u.fDefault[1] = 0.0f;
      }
      break;
    case shader::dtVec3:
      if ( 3 == sscanf( exp, " float3 ( %f , %f , %f )", &u.fDefault[0], &u.fDefault[1], &u.fDefault[2])) {
      }
      else if ( 3 == sscanf( exp, " { %f , %f , %f }", &u.fDefault[0], &u.fDefault[1], &u.fDefault[2])) {
      }
      else if ( 3 == sscanf( exp, " float3 ( %ff , %ff , %ff )", &u.fDefault[0], &u.fDefault[1], &u.fDefault[2])) {
      }
      else if ( 3 == sscanf( exp, " { %ff , %ff , %ff }", &u.fDefault[0], &u.fDefault[1], &u.fDefault[2])) {
      }
      else {
        u.fDefault[0] = 0.0f;
        u.fDefault[1] = 0.0f;
        u.fDefault[2] = 0.0f;
      }
      break;
    case shader::dtVec4:
      if ( 4 == sscanf( exp, " float4 ( %f , %f , %f , %f )", &u.fDefault[0], &u.fDefault[1], &u.fDefault[2], &u.fDefault[3])) {
      }
      else if ( 4 == sscanf( exp, " float4 ( %ff , %ff , %ff , %ff )", &u.fDefault[0], &u.fDefault[1], &u.fDefault[2], &u.fDefault[3])) {
      }
      else if ( 4 == sscanf( exp, " { %f , %f , %f , %f }", &u.fDefault[0], &u.fDefault[1], &u.fDefault[2], &u.fDefault[3])) {
      }
      else if ( 4 == sscanf( exp, " { %ff , %ff , %ff , %ff }", &u.fDefault[0], &u.fDefault[1], &u.fDefault[2], &u.fDefault[3])) {
      }
      else {
        u.fDefault[0] = 0.0f;
        u.fDefault[1] = 0.0f;
        u.fDefault[2] = 0.0f;
        u.fDefault[3] = 0.0f;
      }
      break;
    default:
      //make gcc happy
      break;
  };
}

//
//
//
////////////////////////////////////////////////////////////////////////////////
shader::Semantic hlslSm3FXShader::parseUniformSemantic( const char *semantic) {

  if (semantic == NULL)
    return shader::smNone;

  //this would be more efficient as a map
  if (!strcmp( "World", semantic)) {
    return shader::smWorld;
  }
  else if (!strcmp( "View", semantic)) {
    return shader::smView;
  }
  else if (!strcmp( "Projection", semantic)) {
    return shader::smProjection;
  }
  else if (!strcmp( "WorldView", semantic)) {
    return shader::smWorldView;
  }
  else if (!strcmp( "ViewProjection", semantic)) {
    return shader::smViewProjection;
  }
  else if (!strcmp( "WorldViewProjection", semantic)) {
    return shader::smWorldViewProjection;
  }
  else if ( (!strcmp( "WorldI", semantic)) || (!strcmp( "WorldInverse", semantic))) {
    return shader::smWorldI;
  }
  else if ( (!strcmp( "ViewI", semantic)) || (!strcmp( "ViewInverse", semantic)) ) {
    return shader::smViewI;
  }
  else if ( (!strcmp( "ProjectionI", semantic)) || (!strcmp( "ProjectionInverse", semantic)) ) {
    return shader::smProjectionI;
  }
  else if ( (!strcmp( "WorldViewI", semantic)) || (!strcmp( "WorldViewInverse", semantic)) ) {
    return shader::smWorldViewI;
  }
  else if ( (!strcmp( "ViewProjectionI", semantic)) || (!strcmp( "ViewProjectionInverse", semantic)) ) {
    return shader::smViewProjectionI;
  }
  else if ( (!strcmp( "WorldViewProjectionI", semantic)) || (!strcmp( "WorldViewProjectionInverse", semantic)) ) {
    return shader::smWorldViewProjectionI;
  }
  else if ( (!strcmp( "WorldT", semantic)) || (!strcmp( "WorldTranspose", semantic)) ) {
    return shader::smWorldT;
  }
  else if ( (!strcmp( "ViewT", semantic)) || (!strcmp( "ViewTranspose", semantic)) ) {
    return shader::smViewT;
  }
  else if ( (!strcmp( "ProjectionT", semantic)) || (!strcmp( "ProjectionTranspose", semantic)) ) {
    return shader::smProjectionT;
  }
  else if ( (!strcmp( "WorldViewT", semantic)) || (!strcmp( "WorldViewTranspose", semantic)) ) {
    return shader::smWorldViewT;
  }
  else if ( (!strcmp( "ViewProjectionT", semantic)) || (!strcmp( "ViewProjectionTranspose", semantic)) ) {
    return shader::smViewProjectionT;
  }
  else if ( (!strcmp( "WorldViewProjectionT", semantic)) || (!strcmp( "WorldViewProjectionTranspose", semantic)) ) {
    return shader::smWorldViewProjectionT;
  }
  else if ( (!strcmp( "WorldIT", semantic)) || (!strcmp( "WorldInverseTranspose", semantic)) ) {
    return shader::smWorldIT;
  }
  else if ( (!strcmp( "ViewIT", semantic)) || (!strcmp( "ViewInverseTranspose", semantic)) ) {
    return shader::smViewIT;
  }
  else if ( (!strcmp( "ProjectionIT", semantic)) || (!strcmp( "ProjectionInverseTranspose", semantic)) ) {
    return shader::smProjectionIT;
  }
  else if ( (!strcmp( "WorldViewIT", semantic)) || (!strcmp( "WorldViewInverseTranspose", semantic)) ) {
    return shader::smWorldViewIT;
  }
  else if ( (!strcmp( "ViewProjectionIT", semantic)) || (!strcmp( "ViewProjectionInverseTranspose", semantic)) ) {
    return shader::smViewProjectionIT;
  }
  else if ( (!strcmp( "WorldViewProjectionIT", semantic)) || (!strcmp( "WorldViewProjectionInverseTranspose", semantic)) ) {
    return shader::smWorldViewProjectionIT;
  }

  return shader::smUnknown;
}

//
//
//
////////////////////////////////////////////////////////////////////////////////
shader::SamplerType hlslSm3FXShader::parseSamplerType( const char *type) {
  if (!strcmp( "sampler1D", type)) {
    return shader::st1D;
  }
  else if (!strcmp( "sampler2D", type)) {
    return shader::st2D;
  }
  else if (!strcmp( "sampler3D", type)) {
    return shader::st3D;
  }
  else if (!strcmp( "samplerCUBE", type)) {
    return shader::stCube;
  }

  //add sampler RECT stuff here

  return shader::stUnknown;
}

//
//
//
////////////////////////////////////////////////////////////////////////////////
void hlslSm3FXShader::updateHandles() {
  passState ps;
/*
  //attach a pass state to th observer here and iterate the list
  m_observer->setPassMonitor( &ps);
  for (int ii=0; ii<m_fx->getNumStates( 0, 0); ii++) {
    m_fx->getStateItem( 0, 0, ii);
  }


  MGlobal::displayInfo( MString("Vertex uniforms: ") + ps.m_vRegMap.size());
  MGlobal::displayInfo( MString("Fragment uniforms: ") + ps.m_fRegMap.size());

  //now apply the information
  for (std::vector<uniform>::iterator it = m_uniformList.begin(); it < m_uniformList.end(); it++) {
    std::map< std::string, int>::const_iterator it2 = ps.m_vRegMap.find(it->name);
    if ( it2 != ps.m_vRegMap.end()) 
      it->vReg = it2->second;
    else
      it->vReg = -1;

    it2 = ps.m_fRegMap.find(it->name);
    if ( it2 != ps.m_fRegMap.end()) 
      it->fReg = it2->second;
    else
      it->fReg = -1;

    //need to use observer to get the register value grrrrr
    it->dirty = true; //need to mark it dirty, don't know the old state
  }

  for (std::vector<sampler>::iterator it = m_samplerList.begin(); it < m_samplerList.end(); it++) {
    std::map< std::string, int>::const_iterator it2 = ps.m_fRegMap.find(it->name);

    if ( it2 != ps.m_fRegMap.end()) 
      it->texUnit = it2->second;
    else
      it->texUnit = -1;

    //this should only happen once per compile, we never remap samplers
    it->dirty = true;
  }

  for (std::vector<attribute>::iterator it = m_attributeList.begin(); it < m_attributeList.end(); it++) {
    //it->handle = glGetAttribLocation( m_program, it->name);
    //nothing to mark dirty
  }

  m_observer->setPassMonitor( NULL);
  */
}


//
// buildShaders
//
//  This is doen when the shader is marked dirty to rebuild the shaders. It
// requires a current context.
////////////////////////////////////////////////////////////////////////////////
bool hlslSm3FXShader::buildShaders() {

	//clean up any old shaders
	deleteShaders();

	//create all the passes up front
  m_programList.resize( m_passCount[m_activeTechnique], 0);
  m_vShaderList.resize( m_passCount[m_activeTechnique], 0);
  m_fShaderList.resize( m_passCount[m_activeTechnique], 0);
  

  int offset = m_techniqueOffset[m_activeTechnique];

  for (int ii=0; ii<m_passCount[m_activeTechnique]; ii++) {
    //build the programs
    GLuint program = glCreateProgramObject();
    m_programList[ii] = program;
    bool fail = false;

    GL_CHECK;

    if (m_vertexShaders[offset+ii].length() > 0) {
      const char* temp[2];
      GLuint vShader = glCreateShaderObject( GL_VERTEX_SHADER);
      m_vShaderList[ii] = vShader;
      glAttachObject( program, vShader);
      temp[0] = header;
      temp[1] = m_vertexShaders[offset+ii].c_str();
      glShaderSource( vShader, 2, temp, NULL);
      glCompileShader(vShader);
      //need to check for success here
      GLint success;
      glGetObjectParameteriv( vShader, GL_COMPILE_STATUS, &success);
      if (!success) {
        char log[256];
        glGetInfoLog( vShader, 256, NULL, log);
        fail = true; //allow fragment shader errors to occur
        m_error = "Vertex shader failed compile:\n";
        m_error += log;
        m_error += "\n";
      }
    }
    GL_CHECK;

    if (m_fragmentShaders[offset+ii].length() > 0) {
      const char* temp[2];
      GLuint fShader = glCreateShaderObject( GL_FRAGMENT_SHADER);
      m_fShaderList[ii] = fShader;
      glAttachObject( program, fShader);
      temp[0] = header;
      temp[1] = m_fragmentShaders[offset+ii].c_str();
      glShaderSource( fShader, 2, temp, NULL);
      glCompileShader(fShader);
      //need to check for success here
      GLint success;
      glGetObjectParameteriv( fShader, GL_COMPILE_STATUS, &success);
      if (!success) {
        char log[256];
        glGetInfoLog( fShader, 256, NULL, log);
        fail = true; //allow fragment shader errors to occur
        m_error += "Fragment shader failed compile:\n";
        m_error += log;
      }
    }
    GL_CHECK;

    if (fail) {
      glDeleteObject( m_programList[ii]);
      m_programList[ii] = 0;
      if (m_fShaderList[ii]) {
        glDeleteObject( m_fShaderList[ii]);
        m_fShaderList[ii] = 0;
      }
      if (m_vShaderList[ii]) {
        glDeleteObject( m_vShaderList[ii]);
        m_vShaderList[ii] = 0;
      }
      return false;
    }

    glLinkProgram(program);
    GLint success;
    glGetObjectParameteriv( program, GL_LINK_STATUS, &success);
    if (!success) {
      char log[256];
      glGetInfoLog( program, 256, NULL, log);
      m_error = "Link failed:\n";
      m_error += log;
      glDeleteObject( m_programList[ii]);
      m_programList[ii] = 0;
      if (m_fShaderList[ii]) {
        glDeleteObject( m_fShaderList[ii]);
        m_fShaderList[ii] = 0;
      }
      if (m_vShaderList[ii]) {
        glDeleteObject( m_vShaderList[ii]);
        m_vShaderList[ii] = 0;
      }
      GL_CHECK;
      return false;
    }

    GL_CHECK;
  }

  return true;
}

//
//
//
////////////////////////////////////////////////////////////////////////////////
bool hlslSm3FXShader::valid() {
  return m_valid;
}

//
//
//
////////////////////////////////////////////////////////////////////////////////
int hlslSm3FXShader::passCount() {
  //forcing single pass for now
  return 1;
}

//
//
//
////////////////////////////////////////////////////////////////////////////////
int hlslSm3FXShader::techniqueCount() {
  //ignoring techniques for now
  return 1;
}

//
//
//
////////////////////////////////////////////////////////////////////////////////
const char* hlslSm3FXShader::techniqueName( int n) {
  //ignoring all but technique zero for now
  return NULL;
}

//
//
//
////////////////////////////////////////////////////////////////////////////////
bool hlslSm3FXShader::build() {

  //need to try to compile the shaders here if they don't exist yet

  if (m_stale) {
    m_stale = false;
    if (!buildShaders())
      return false;
    updateHandles();
  }

  return true;
}

//
// bind
//
//  This function is used to bind in the active program and set all of
// the associated shape independent state. Please note that only dirty 
// program state is sent to the shader. 
////////////////////////////////////////////////////////////////////////////////
void hlslSm3FXShader::bind() {
	glUseProgramObject( m_programList[m_activePass]);
	GL_CHECK;

	GLenum targets[] = { GL_TEXTURE_1D, GL_TEXTURE_2D, GL_TEXTURE_3D, GL_TEXTURE_CUBE_MAP, GL_TEXTURE_1D, GL_TEXTURE_2D};

	//update dirty samplers
	for (std::vector<sampler>::iterator it2 = m_samplerList.begin(); it2<m_samplerList.end(); it2++) {
		if ( it2->handle[m_activePass] != -1) {
			if (it2->dirty) {
				glUniform1i( it2->handle[m_activePass], it2->texUnit[m_activePass]);
				//it->dirty = false;
			}
			glActiveTexture( GL_TEXTURE0_ARB + it2->texUnit[m_activePass]);
			glBindTexture( targets[it2->type], it2->texObject);
		}
	}
	glActiveTexture( GL_TEXTURE0_ARB);

	GL_CHECK;

	//set up the render states
  m_stateList[m_techniqueOffset[m_activeTechnique]+m_activePass]->setState();

	GL_CHECK;

	return;
}

//
// setShapeDependentState
//
//  This function is used to setup any shape dependent data
////////////////////////////////////////////////////////////////////////////////
void hlslSm3FXShader::setShapeDependentState() {
	//update dirty values
	for (std::vector<uniform>::iterator it = m_uniformList.begin(); it<m_uniformList.end(); it++) {
		if ( it->dirty) {

			//only mark it clean on the last pass
      if ( m_activePass == m_passCount[m_activeTechnique]-1)
				it->dirty = false;

			if ( it->handle[m_activePass] == -1)
				continue; // avoid causing a GL error, by submitting a uniform with a -1 (does not exist) handle

			switch (it->type) {
		case shader::dtBool:
			glUniform1i( it->handle[m_activePass], it->iVal[0]);
			break;
		case shader::dtBVec2:
			glUniform2iv( it->handle[m_activePass], 1, it->iVal);
			break;
		case shader::dtBVec3:
			glUniform3iv( it->handle[m_activePass], 1, it->iVal);
			break;
		case shader::dtBVec4:
			glUniform4iv( it->handle[m_activePass], 1, it->iVal);
			break;
		case shader::dtInt:
			glUniform1i( it->handle[m_activePass], it->iVal[0]);
			break;
		case shader::dtIVec2:
			glUniform2iv( it->handle[m_activePass], 1, it->iVal);
			break;
		case shader::dtIVec3:
			glUniform3iv( it->handle[m_activePass], 1, it->iVal);
			break;
		case shader::dtIVec4:
			glUniform4iv( it->handle[m_activePass], 1, it->iVal);
			break;
		case shader::dtFloat:
			glUniform1f( it->handle[m_activePass], it->fVal[0]);
			break;
		case shader::dtVec2:
			glUniform2fv( it->handle[m_activePass], 1, it->fVal);
			break;
		case shader::dtVec3:
			glUniform3fv( it->handle[m_activePass], 1, it->fVal);
			break;
		case shader::dtVec4:
			glUniform4fv( it->handle[m_activePass], 1, it->fVal);
			break;
		case shader::dtMat2:
			glUniformMatrix2fv( it->handle[m_activePass], 1, false, it->fVal);
			break;
		case shader::dtMat3:
			glUniformMatrix3fv( it->handle[m_activePass], 1, false, it->fVal);
			break;
		case shader::dtMat4:
			glUniformMatrix4fv( it->handle[m_activePass], 1, false, it->fVal);
			break;
		default:
			break;
			};
			GL_CHECK;
		}
	}
	return;
}

//
//
//
////////////////////////////////////////////////////////////////////////////////
void hlslSm3FXShader::unbind() {
  glDisable( GL_FRAGMENT_PROGRAM_ARB);
  glDisable( GL_VERTEX_PROGRAM_ARB);
}

//
//
//
////////////////////////////////////////////////////////////////////////////////
void hlslSm3FXShader::setTechnique( int t) {
  m_activeTechnique = t;
}

//
//
//
////////////////////////////////////////////////////////////////////////////////
void hlslSm3FXShader::setPass( int p) {
  m_activePass = p;
}

//
//
//
////////////////////////////////////////////////////////////////////////////////
int hlslSm3FXShader::uniformCount() {
  return (int)m_uniformList.size();
}

//
//
//
////////////////////////////////////////////////////////////////////////////////
int hlslSm3FXShader::samplerCount() {
  return (int)m_samplerList.size();
}

//
//
//
////////////////////////////////////////////////////////////////////////////////
int hlslSm3FXShader::attributeCount() {
  return (int)m_attributeList.size();
}

//
//
//
////////////////////////////////////////////////////////////////////////////////
const char* hlslSm3FXShader::uniformName(int i) {
  //should check for array bounds
  return m_uniformList[i].name.c_str();
}

//
//
//
////////////////////////////////////////////////////////////////////////////////
shader::DataType hlslSm3FXShader::uniformType(int i) {
  //should check for array bounds
  return m_uniformList[i].type;
}

//
//
//
////////////////////////////////////////////////////////////////////////////////
shader::Semantic hlslSm3FXShader::uniformSemantic(int i) {
  //might want to check array bounds
  return m_uniformList[i].usage;
}

//
//
//
////////////////////////////////////////////////////////////////////////////////
const char* hlslSm3FXShader::samplerName(int i) {
  //should check for array bounds
  return m_samplerList[i].name.c_str();
}

//
//
//
////////////////////////////////////////////////////////////////////////////////
shader::SamplerType hlslSm3FXShader::samplerType(int i) {
  //should check for array bounds
  return m_samplerList[i].type;
}

//
//
//
////////////////////////////////////////////////////////////////////////////////
const char* hlslSm3FXShader::attributeName(int i) {
  //should check for array bounds
  return m_attributeList[i].name.c_str();
}

//
//
//
////////////////////////////////////////////////////////////////////////////////
shader::DataType hlslSm3FXShader::attributeType(int i) {
  return m_attributeList[i].type;
}

//
//
//
////////////////////////////////////////////////////////////////////////////////
void hlslSm3FXShader::updateUniformBool( int i, bool val) {
  m_uniformList[i].fVal[0] = val ? 1.0f : 0.0f;
  m_uniformList[i].dirty = true;
}

//
//
//
////////////////////////////////////////////////////////////////////////////////
void hlslSm3FXShader::updateUniformInt( int i, int val) {
  m_uniformList[i].fVal[0] = (float)val;
  m_uniformList[i].dirty = true;
}

//
//
//
////////////////////////////////////////////////////////////////////////////////
void hlslSm3FXShader::updateUniformFloat( int i, float val) {
  m_uniformList[i].fVal[0] = val;
  m_uniformList[i].dirty = true;
}

//
//
//
////////////////////////////////////////////////////////////////////////////////
void hlslSm3FXShader::updateUniformBVec( int i, const bool* val) {
  for (int ii=0; ii<size(m_uniformList[i].type); ii++) {
    m_uniformList[i].fVal[ii] = val[ii] ? 0.0f : 1.0f;
  }
  m_uniformList[i].dirty = true;
}

//
//
//
////////////////////////////////////////////////////////////////////////////////
void hlslSm3FXShader::updateUniformIVec( int i, const int* val) {
  for (int ii=0; ii<size(m_uniformList[i].type); ii++) {
    m_uniformList[i].fVal[ii] = (float)val[ii];
  }
  m_uniformList[i].dirty = true;
}

//
//
//
////////////////////////////////////////////////////////////////////////////////
void hlslSm3FXShader::updateUniformVec( int i, const float* val) {
  for (int ii=0; ii<size(m_uniformList[i].type); ii++) {
    m_uniformList[i].fVal[ii] = val[ii];
  }
  m_uniformList[i].dirty = true;
}

//
//
//
////////////////////////////////////////////////////////////////////////////////
void hlslSm3FXShader::updateUniformMat( int i, const float* val) {
  for (int ii=0; ii<size(m_uniformList[i].type); ii++) {
    m_uniformList[i].fVal[ii] = val[ii];
  }
  m_uniformList[i].dirty = true;
}

//
//
//
////////////////////////////////////////////////////////////////////////////////
void hlslSm3FXShader::updateUniformMat( int i, const double* val) {
  for (int ii=0; ii<size(m_uniformList[i].type); ii++) {
    m_uniformList[i].fVal[ii] = (float)val[ii];
  }
  m_uniformList[i].dirty = true;
}

//
//
//
////////////////////////////////////////////////////////////////////////////////
void hlslSm3FXShader::updateSampler( int i, unsigned int val) {
  m_samplerList[i].texObject = val;
  //m_samplerList[i].dirty = true;
}

//
//
//
////////////////////////////////////////////////////////////////////////////////
bool hlslSm3FXShader::usesColor() {
  return m_color;
}

//
//
//
////////////////////////////////////////////////////////////////////////////////
bool hlslSm3FXShader::usesNormal() {
  return m_normal;
}

//
//
//
////////////////////////////////////////////////////////////////////////////////
bool hlslSm3FXShader::usesTexCoord( int set) {
  return ((m_texMask>>set) & 0x1) == 1;
}

//
//
//
////////////////////////////////////////////////////////////////////////////////
bool hlslSm3FXShader::usesTangent() {
  return m_tangent;
}

//
//
//
////////////////////////////////////////////////////////////////////////////////
bool hlslSm3FXShader::usesBinormal() {
  return m_binormal;
}

//
//
//
////////////////////////////////////////////////////////////////////////////////
int hlslSm3FXShader::tangentSlot() {
  return m_tangentSlot;
}

//
//
//
////////////////////////////////////////////////////////////////////////////////
int hlslSm3FXShader::binormalSlot() {
  return m_binormalSlot;
}

//
//
//
////////////////////////////////////////////////////////////////////////////////
const char* hlslSm3FXShader::errorString() {
  return m_error.c_str();
}

