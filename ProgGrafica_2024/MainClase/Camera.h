#pragma once
#include "common.h"
#include "libMath.h"

using namespace std;

class Camera {
public:
    vec4float pos;
    vec4float rot;
    vec4float lookAt;
    vec4float forward;
    vec4float up;
    vec4float right;

    Camera(vec4float position, vec4float lookAt, vec4float up = {0, 1, 0, 1});
    matrix4x4f computeViewMatrix();
    matrix4x4f computeProjectionMatrix(float, float, float fovy, float aspect);
    void moveCamera(double deltaTime);
};