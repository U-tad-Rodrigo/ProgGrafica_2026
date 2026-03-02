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

// Suma de vectores: sumar componentes x,y,z,w
inline vec4float operator +(vec4float v1, vec4float v2) {
    vec4float res;
    res.x = v1.x + v2.x;
    res.y = v1.y + v2.y;
    res.z = v1.z + v2.z;
    res.w = v1.w + v2.w;
    return res;

}

// Resta de vectores: restar componentes x,y,z,w
inline vec4float operator -(vec4float v1, vec4float v2) {
    vec4float res;
    res.x = v1.x - v2.x;
    res.y = v1.y - v2.y;
    res.z = v1.z - v2.z;
    res.w = v1.w - v2.w;
    return res;

}

// Suma de matrices: sumar los 16 elementos
inline matrix4x4f operator +(matrix4x4f m1, matrix4x4f m2) {
    matrix4x4f res;
    for (int i = 0; i < 16; i++) {
        res.mat[i] = m1.mat[i] + m2.mat[i];
    }
    return res;

}

// Resta de matrices: restar los 16 elementos
inline matrix4x4f operator -(matrix4x4f m1, matrix4x4f m2) {
    matrix4x4f res;
    for (int i = 0; i < 16; i++) {
        res.mat[i] = m1.mat[i] - m2.mat[i];
    }
    return res;

}

// Matriz por escalar: multiplicar cada elemento por s
inline matrix4x4f operator *(matrix4x4f m, float s) {
    matrix4x4f res;
    for (int i = 0; i < 16; i++) {
        res.mat[i] = m.mat[i] * s;
    }
    return res;

}

// Multiplicacion de matrices 4x4: res[i][j] = sum(m1[i][k] * m2[k][j])
inline matrix4x4f operator *(matrix4x4f m1, matrix4x4f m2) {
    matrix4x4f res = {0};
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            for (int k = 0; k < 4; k++) {
                res.mat[i*4+j] += m1.mat[i*4+k] * m2.mat[k*4+j];
            }
        }
    }
    return res;

}

// Matriz por vector: res[i] = sum(m[i][j] * v[j])
inline vec4float operator *(matrix4x4f m, vec4float v) {
    vec4float res = {0};
    for (int i = 0; i < 4; i++) {
        for ( int j = 0; j < 4; j++) {
            res.v[i] += m.mat[i*4+j] * v.v[j];
        }
    }
    return res;

}

