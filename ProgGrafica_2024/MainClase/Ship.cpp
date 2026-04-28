#include "Object3D.h"
#include "Bullet.h"
#include "EventManager.h"

void Ship::moveObject(double timeStep) {
    if (EventManager::keyMap[GLFW_KEY_A]) posicion.x -= speed * (float)timeStep;
    if (EventManager::keyMap[GLFW_KEY_D]) posicion.x += speed * (float)timeStep;
    if (EventManager::keyMap[GLFW_KEY_W]) posicion.y += speed * (float)timeStep;
    if (EventManager::keyMap[GLFW_KEY_S]) posicion.y -= speed * (float)timeStep;

    static bool spaceWasPressed = false;
    bool spaceNow = EventManager::keyMap[GLFW_KEY_SPACE];
    if (spaceNow && !spaceWasPressed)
        Object3D::pendingSpawn.push_back(new Bullet(posicion));
    spaceWasPressed = spaceNow;
}
