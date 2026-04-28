#include "Bullet.h"

Bullet::Bullet(vec4float startPos) : Object3D() {
    posicion = startPos;
    escalado = { 0.2f, 0.5f, 0.2f, 1.0f };
    mat->color = { 1.0f, 1.0f, 0.0f, 1.0f };
}

void Bullet::moveObject(double timeStep) {
    posicion.y += speed * (float)timeStep;
}
