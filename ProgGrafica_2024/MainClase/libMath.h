#pragma once
#include "common.h"

#define PI 3.1415927f

typedef struct {
    union {
        struct {
            float x;
            float y;
            float z;
            float w;
        };
        float v[4];
    };
}vec4float;

typedef struct {
    union {
        float mat2D[4][4];
        float mat[16];
        vec4float vec[4];
    };
}matrix4x4f;

vec4float make_vector4f(float x, float y, float z, float w);
vec4float normalize(vec4float v);
float dot(vec4float v1, vec4float v2);
vec4float cross(vec4float v1, vec4float v2);

matrix4x4f make_identityf();
matrix4x4f make_translate(float X, float Y, float Z);
matrix4x4f make_rotate(float angleX, float angleY, float angleZ);
matrix4x4f make_scale(float X, float Y, float Z);
matrix4x4f transpose(matrix4x4f m);
matrix4x4f inverse(matrix4x4f m);

vec4float make_quaternion(float x, float y, float z, float angle);
matrix4x4f make_rotate_quaternion(vec4float q);

inline vec4float operator +(vec4float v1, vec4float v2) {
    vec4float res;
    res.x = v1.x + v2.x;
    res.y = v1.y + v2.y;
    res.z = v1.z + v2.z;
    res.w = v1.w + v2.w;
    return res;

}

inline vec4float operator -(vec4float v1, vec4float v2) {
    vec4float res;
    res.x = v1.x - v2.x;
    res.y = v1.y - v2.y;
    res.z = v1.z - v2.z;
    res.w = v1.w - v2.w;
    return res;

}

inline matrix4x4f operator +(matrix4x4f m1, matrix4x4f m2) {
    matrix4x4f res;
    for (int i = 0; i < 16; i++) {
        res.mat[i] = m1.mat[i] + m2.mat[i];
    }
    return res;

}


inline matrix4x4f operator -(matrix4x4f m1, matrix4x4f m2) {
    matrix4x4f res;
    for (int i = 0; i < 16; i++) {
        res.mat[i] = m1.mat[i] - m2.mat[i];
    }
    return res;

}

inline matrix4x4f operator *(matrix4x4f m, float s) {
    matrix4x4f res;
    for (int i = 0; i < 16; i++) {
        res.mat[i] = m.mat[i] * s;
    }
    return res;

}



inline matrix4x4f operator *(matrix4x4f m1, matrix4x4f m2) {
    matrix4x4f res = {0};
    for (int row = 0; row < 4; row++) {
        for (int col = 0; col < 4; col++) {
            for (int k = 0; k < 4; k++) {
                res.mat[row*4+col] += m1.mat[row*4+k] * m2.mat[k*4+col];
            }
        }
    }
    return res;
}

inline vec4float operator *(matrix4x4f m, vec4float v) {
    vec4float res = {0};
    for (int row = 0; row < 4; row++) {
        for (int col = 0; col < 4; col++) {
            res.v[row] += m.mat[row*4+col] * v.v[col];
        }
    }
    return res;

}

