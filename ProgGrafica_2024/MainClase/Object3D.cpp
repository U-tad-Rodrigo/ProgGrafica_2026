//
// Created by Rodrigo on 09/02/2026.
//

#include "Object3D.h"
#include "EventManager.h"
#include <iostream>

Object3D::Object3D() {
    objectId = idCounter++;
    vertexList = {
        {{-0.5,  0.5, 0, 1 },{ 1, 0, 0, 1}},
        {{ 0.5,  0.5, 0, 1 },{ 0, 1,0, 1}},
        {{-0.5, -0.5, 0, 1 },{ 1, 1, 0, 1}},
        {{ 0.5, -0.5, 0, 1 },{ 0, 0, 1, 1}}
    };
    indexList = {0,1,2 , 2,1,3};
}

matrix4x4f Object3D::computeModelMatrix() {
    matrix4x4f scaleMatrix = make_scale(scale.x, scale.y, scale.z);
    matrix4x4f rotationMatrix = make_rotate(rotation.x, rotation.y, rotation.z);
    matrix4x4f translationMatrix = make_translate(position.x, position.y, position.z);
    matrix4x4f model = translationMatrix * rotationMatrix * scaleMatrix;
    return model;

}

void Object3D::moveObject(double deltaTime) {
}
