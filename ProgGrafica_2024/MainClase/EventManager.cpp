//
// Created by Rodrigo on 03/02/2026.
//

#include "EventManager.h"

// Incluimos solo lo necesario para no reintroducir la implementación de GLAD
#include <GLFW/glfw3.h>

GLFWwindow* EventManager::window = nullptr;
std::map<int,bool> EventManager::keyMap;

void EventManager::initEventManager(GLFWwindow* win) {
    glfwSetKeyCallback(win, keyboardManager);
    //glfwSetMouseButtonCallback(win, mouseButtonManager);
    EventManager::window = win;
}
void EventManager::keyboardManager(GLFWwindow* win, int key, int scancode, int action, int mods) {
    switch (action) {
        case GLFW_PRESS: {
            EventManager::keyMap[key] = true;
        } break;
        case GLFW_RELEASE: {
            EventManager::keyMap[key] = false;
        } break;
        default: {
        } break;
    }
}

void EventManager::updateEvents() {
    glfwPollEvents();

}