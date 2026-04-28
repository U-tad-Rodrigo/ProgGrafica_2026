#pragma once
#include "Object3D.h"

class Bullet : public Object3D {
public:
    float speed = 5.0f;
    Bullet(vec4float startPos);
    void moveObject(double timeStep) override;
};
