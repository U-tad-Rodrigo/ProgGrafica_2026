//
// Created by Rodrigo on 23/02/2026.
//

#include "Camera.h"
#include "EventManager.h"

Camera::Camera(vec4float position, vec4float lookAt, vec4float up) {
    this->pos = position;
    this->rot = {0, 0, 0, 1};
    this->lookAt = lookAt;
    this->up = up;

    forward = normalize(lookAt - position);
    right = {0, 0, 0, 0};
}

matrix4x4f Camera::computeViewMatrix() {
    matrix4x4f view = make_identityf();
    right = cross(forward, up);
    right = normalize(right);
    vec4float upCamera = normalize(cross(right, forward));

    view.mat2D[0][0] = right.x;
    view.mat2D[0][1] = right.y;
    view.mat2D[0][2] = right.z;
    view.mat2D[0][3] = -dot(right, pos);

    view.mat2D[1][0] = upCamera.x;
    view.mat2D[1][1] = upCamera.y;
    view.mat2D[1][2] = upCamera.z;
    view.mat2D[1][3] = -dot(upCamera, pos);

    view.mat2D[2][0] = -forward.x;
    view.mat2D[2][1] = -forward.y;
    view.mat2D[2][2] = -forward.z;
    view.mat2D[2][3] = dot(forward, pos);

    return view;
}

matrix4x4f Camera::computeProjectionMatrix(float zFar, float zNear, float fovy, float aspect) {
    matrix4x4f projMatrix = make_identityf();
    float tanHalfFovy = tanf(fovy / 2.0f);

    projMatrix.mat2D[0][0] = 1.0f / (aspect * tanHalfFovy);
    projMatrix.mat2D[1][1] = 1.0f / tanHalfFovy;
    projMatrix.mat2D[2][2] = -(zFar + zNear) / (zFar - zNear);
    projMatrix.mat2D[2][3] = -(2.0f * zFar * zNear) / (zFar - zNear);
    projMatrix.mat2D[3][2] = -1.0f;
    projMatrix.mat2D[3][3] = 0.0f;

    return projMatrix;

}

void Camera::moveCamera(double timeStep) {
    float speed = 2.0f;
    float rotSpeed = 45.0f; // grados por segundo

    vec4float translation = {0, 0, 0, 1};

    if (EventManager::keyMap[GLFW_KEY_W]) {
        translation.y -= speed * timeStep;
    }
    if (EventManager::keyMap[GLFW_KEY_S]) {
        translation.y += speed * timeStep;
    }
    if (EventManager::keyMap[GLFW_KEY_A]) {
        translation.x += speed * timeStep;
    }
    if (EventManager::keyMap[GLFW_KEY_D]) {
        translation.x -= speed * timeStep;
    }
    if (EventManager::keyMap[GLFW_KEY_Q]) {
        rot.y += rotSpeed * timeStep;
    }
    if (EventManager::keyMap[GLFW_KEY_E]) {
        rot.y -= rotSpeed * timeStep;
    }

    matrix4x4f translationMatrix = make_translate(translation.x, translation.y, translation.z);
    matrix4x4f rotationMatrix = make_rotate(0, rot.y, 0);

    pos.x += translation.x;
    pos.y += translation.y;
    pos.z += translation.z;

    vec4float lookAtRest = {0, 0, -3, 1};

    vec4float rotatedLookAt = rotationMatrix * lookAtRest;
    lookAt.x = pos.x + rotatedLookAt.x;
    lookAt.y = pos.y + rotatedLookAt.y;
    lookAt.z = pos.z + rotatedLookAt.z;

    // Recalcular forward
    forward = normalize(lookAt - pos);
}

