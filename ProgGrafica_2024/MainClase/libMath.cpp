#include "libMath.h"
#include <cmath>

vec4float make_vector4f(float x, float y, float z, float w) {
    vec4float result;
    result.x = x;
    result.y = y;
    result.z = z;
    result.w = w;
    return result;
}

vec4float normalize(vec4float v) {
    float len = sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
    vec4float result;
    result.x = v.x / len;
    result.y = v.y / len;
    result.z = v.z / len;
    result.w = v.w;
    return result;
}

float dot(vec4float v1, vec4float v2) {
    return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

vec4float cross(vec4float v1, vec4float v2) {
    vec4float result;
    result.x = v1.y * v2.z - v1.z * v2.y;
    result.y = v1.z * v2.x - v1.x * v2.z;
    result.z = v1.x * v2.y - v1.y * v2.x;
    result.w = 0.0f;
    return result;
}

matrix4x4f make_identityf() {
    matrix4x4f result;
    for (int i = 0; i < 16; i++) {
        result.mat[i] = 0.0f;
    }
    result.mat[0] = 1.0f;
    result.mat[5] = 1.0f;
    result.mat[10] = 1.0f;
    result.mat[15] = 1.0f;
    return result;
}

matrix4x4f make_translate(float X, float Y, float Z) {
    matrix4x4f result = make_identityf();
    // Row-major: mat[row*4+col], traslación en última columna
    result.mat[3] = X;   // [0][3]
    result.mat[7] = Y;   // [1][3]
    result.mat[11] = Z;  // [2][3]
    return result;
}

matrix4x4f make_rotate(float angleX, float angleY, float angleZ) {
    float radX = angleX * PI / 180.0f;
    float radY = angleY * PI / 180.0f;
    float radZ = angleZ * PI / 180.0f;

    // Column-major: mat[columna*4 + fila]
    matrix4x4f rotX = make_identityf();
    rotX.mat[5] = cos(radX);      // [1][1]
    rotX.mat[9] = -sin(radX);     // [2][1]
    rotX.mat[6] = sin(radX);      // [1][2]
    rotX.mat[10] = cos(radX);     // [2][2]

    matrix4x4f rotY = make_identityf();
    rotY.mat[0] = cos(radY);      // [0][0]
    rotY.mat[8] = sin(radY);      // [2][0]
    rotY.mat[2] = -sin(radY);     // [0][2]
    rotY.mat[10] = cos(radY);     // [2][2]

    matrix4x4f rotZ = make_identityf();
    rotZ.mat[0] = cos(radZ);      // [0][0]
    rotZ.mat[4] = -sin(radZ);     // [1][0]
    rotZ.mat[1] = sin(radZ);      // [0][1]
    rotZ.mat[5] = cos(radZ);      // [1][1]

    matrix4x4f temp = rotZ * rotY;
    return temp * rotX;
}

matrix4x4f make_scale(float X, float Y, float Z) {
    matrix4x4f result = make_identityf();
    result.mat[0] = X;
    result.mat[5] = Y;
    result.mat[10] = Z;
    return result;
}

matrix4x4f transpose(matrix4x4f m) {
    matrix4x4f result;
    // Row-major: mat[row*4+col] -> transponer invierte row y col
    for (int row = 0; row < 4; row++) {
        for (int col = 0; col < 4; col++) {
            result.mat[col * 4 + row] = m.mat[row * 4 + col];
        }
    }
    return result;
}

vec4float make_quaternion(float x, float y, float z, float angle) {
    vec4float axis = make_vector4f(x, y, z, 0.0f);
    axis = normalize(axis);

    float halfAngle = angle / 2.0f;
    float sinHalfAngle = sin(halfAngle);
    float cosHalfAngle = cos(halfAngle);

    vec4float q;
    q.x = axis.x * sinHalfAngle;
    q.y = axis.y * sinHalfAngle;
    q.z = axis.z * sinHalfAngle;
    q.w = cosHalfAngle;
    return q;
}

matrix4x4f make_rotate_quaternion(vec4float q) {
    matrix4x4f result;
    float xx = q.x * q.x;
    float yy = q.y * q.y;
    float zz = q.z * q.z;
    float xy = q.x * q.y;
    float xz = q.x * q.z;
    float yz = q.y * q.z;
    float wx = q.w * q.x;
    float wy = q.w * q.y;
    float wz = q.w * q.z;

    result.mat[0] = 1.0f - 2.0f * (yy + zz);
    result.mat[1] = 2.0f * (xy - wz);
    result.mat[2] = 2.0f * (xz + wy);
    result.mat[3] = 0.0f;

    result.mat[4] = 2.0f * (xy + wz);
    result.mat[5] = 1.0f - 2.0f * (xx + zz);
    result.mat[6] = 2.0f * (yz - wx);
    result.mat[7] = 0.0f;

    result.mat[8] = 2.0f * (xz - wy);
    result.mat[9] = 2.0f * (yz + wx);
    result.mat[10] = 1.0f - 2.0f * (xx + yy);
    result.mat[11] = 0.0f;

    result.mat[12] = 0.0f;
    result.mat[13] = 0.0f;
    result.mat[14] = 0.0f;
    result.mat[15] = 1.0f;

    return result;
}

matrix4x4f inverse(matrix4x4f m) {
    matrix4x4f result;
    float det;

    result.mat[0] = m.mat[5] * m.mat[10] * m.mat[15] - m.mat[5] * m.mat[11] * m.mat[14] - m.mat[9] * m.mat[6] * m.mat[15] + m.mat[9] * m.mat[7] * m.mat[14] + m.mat[13] * m.mat[6] * m.mat[11] - m.mat[13] * m.mat[7] * m.mat[10];
    result.mat[4] = -m.mat[4] * m.mat[10] * m.mat[15] + m.mat[4] * m.mat[11] * m.mat[14] + m.mat[8] * m.mat[6] * m.mat[15] - m.mat[8] * m.mat[7] * m.mat[14] - m.mat[12] * m.mat[6] * m.mat[11] + m.mat[12] * m.mat[7] * m.mat[10];
    result.mat[8] = m.mat[4] * m.mat[9] * m.mat[15] - m.mat[4] * m.mat[11] * m.mat[13] - m.mat[8] * m.mat[5] * m.mat[15] + m.mat[8] * m.mat[7] * m.mat[13] + m.mat[12] * m.mat[5] * m.mat[11] - m.mat[12] * m.mat[7] * m.mat[9];
    result.mat[12] = -m.mat[4] * m.mat[9] * m.mat[14] + m.mat[4] * m.mat[10] * m.mat[13] + m.mat[8] * m.mat[5] * m.mat[14] - m.mat[8] * m.mat[6] * m.mat[13] - m.mat[12] * m.mat[5] * m.mat[10] + m.mat[12] * m.mat[6] * m.mat[9];

    result.mat[1] = -m.mat[1] * m.mat[10] * m.mat[15] + m.mat[1] * m.mat[11] * m.mat[14] + m.mat[9] * m.mat[2] * m.mat[15] - m.mat[9] * m.mat[3] * m.mat[14] - m.mat[13] * m.mat[2] * m.mat[11] + m.mat[13] * m.mat[3] * m.mat[10];
    result.mat[5] = m.mat[0] * m.mat[10] * m.mat[15] - m.mat[0] * m.mat[11] * m.mat[14] - m.mat[8] * m.mat[2] * m.mat[15] + m.mat[8] * m.mat[3] * m.mat[14] + m.mat[12] * m.mat[2] * m.mat[11] - m.mat[12] * m.mat[3] * m.mat[10];
    result.mat[9] = -m.mat[0] * m.mat[9] * m.mat[15] + m.mat[0] * m.mat[11] * m.mat[13] + m.mat[8] * m.mat[1] * m.mat[15] - m.mat[8] * m.mat[3] * m.mat[13] - m.mat[12] * m.mat[1] * m.mat[11] + m.mat[12] * m.mat[3] * m.mat[9];
    result.mat[13] = m.mat[0] * m.mat[9] * m.mat[14] - m.mat[0] * m.mat[10] * m.mat[13] - m.mat[8] * m.mat[1] * m.mat[14] + m.mat[8] * m.mat[2] * m.mat[13] + m.mat[12] * m.mat[1] * m.mat[10] - m.mat[12] * m.mat[2] * m.mat[9];

    result.mat[2] = m.mat[1] * m.mat[6] * m.mat[15] - m.mat[1] * m.mat[7] * m.mat[14] - m.mat[5] * m.mat[2] * m.mat[15] + m.mat[5] * m.mat[3] * m.mat[14] + m.mat[13] * m.mat[2] * m.mat[7] - m.mat[13] * m.mat[3] * m.mat[6];
    result.mat[6] = -m.mat[0] * m.mat[6] * m.mat[15] + m.mat[0] * m.mat[7] * m.mat[14] + m.mat[4] * m.mat[2] * m.mat[15] - m.mat[4] * m.mat[3] * m.mat[14] - m.mat[12] * m.mat[2] * m.mat[7] + m.mat[12] * m.mat[3] * m.mat[6];
    result.mat[10] = m.mat[0] * m.mat[5] * m.mat[15] - m.mat[0] * m.mat[7] * m.mat[13] - m.mat[4] * m.mat[1] * m.mat[15] + m.mat[4] * m.mat[3] * m.mat[13] + m.mat[12] * m.mat[1] * m.mat[7] - m.mat[12] * m.mat[3] * m.mat[5];
    result.mat[14] = -m.mat[0] * m.mat[5] * m.mat[14] + m.mat[0] * m.mat[6] * m.mat[13] + m.mat[4] * m.mat[1] * m.mat[14] - m.mat[4] * m.mat[2] * m.mat[13] - m.mat[12] * m.mat[1] * m.mat[6] + m.mat[12] * m.mat[2] * m.mat[5];

    result.mat[3] = -m.mat[1] * m.mat[6] * m.mat[11] + m.mat[1] * m.mat[7] * m.mat[10] + m.mat[5] * m.mat[2] * m.mat[11] - m.mat[5] * m.mat[3] * m.mat[10] - m.mat[9] * m.mat[2] * m.mat[7] + m.mat[9] * m.mat[3] * m.mat[6];
    result.mat[7] = m.mat[0] * m.mat[6] * m.mat[11] - m.mat[0] * m.mat[7] * m.mat[10] - m.mat[4] * m.mat[2] * m.mat[11] + m.mat[4] * m.mat[3] * m.mat[10] + m.mat[8] * m.mat[2] * m.mat[7] - m.mat[8] * m.mat[3] * m.mat[6];
    result.mat[11] = -m.mat[0] * m.mat[5] * m.mat[11] + m.mat[0] * m.mat[7] * m.mat[9] + m.mat[4] * m.mat[1] * m.mat[11] - m.mat[4] * m.mat[3] * m.mat[9] - m.mat[8] * m.mat[1] * m.mat[7] + m.mat[8] * m.mat[3] * m.mat[5];
    result.mat[15] = m.mat[0] * m.mat[5] * m.mat[10] - m.mat[0] * m.mat[6] * m.mat[9] - m.mat[4] * m.mat[1] * m.mat[10] + m.mat[4] * m.mat[2] * m.mat[9] + m.mat[8] * m.mat[1] * m.mat[6] - m.mat[8] * m.mat[2] * m.mat[5];

    det = m.mat[0] * result.mat[0] + m.mat[1] * result.mat[4] + m.mat[2] * result.mat[8] + m.mat[3] * result.mat[12];

    // Verificar que el determinante no sea cero (matriz singular)
    if (det == 0.0f) {
        // Retornar matriz identidad si no se puede invertir
        return make_identityf();
    }

    for (int i = 0; i < 16; i++)
        result.mat[i] = result.mat[i] / det;

    return result;
}

