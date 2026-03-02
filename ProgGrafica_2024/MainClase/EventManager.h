#pragma once

// No incluimos common.h aquí para evitar introducir la implementación de GLAD
// en múltiples unidades de traducción. Declaramos GLFWwindow de forma adelantada
// y usamos std::map sin "using namespace" en el encabezado.

#include <map>

struct GLFWwindow; // forward declaration

class EventManager {
public:
    static std::map<int,bool> keyMap; // Mapa para almacenar el estado de las teclas
    static GLFWwindow* window;
    static void initEventManager(GLFWwindow* window);
    static void keyboardManager(GLFWwindow* window, int key, int scancode, int action, int mods);
    //static void mouseButtonManager(GLFWwindow* window, int button, int action, int mods);
    static void updateEvents();


};
