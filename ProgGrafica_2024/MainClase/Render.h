#pragma once
#include "Camera.h"
#include "Object3D.h"

class Render {
public:
    Render();
    typedef struct {
        unsigned int bufferId;
        unsigned int vertexBufferId;
        unsigned int indexBufferId;
    }bufferObject_t;

    Camera* cam = new Camera({0,0,3,1}, {0,0,0,1}, {0,1,0,1});
    vector <Object3D*> objectList;
    map<unsigned int, bufferObject_t> bufferedObjectList;
    GLFWwindow* window = nullptr;
    bool initialized = false;

    void setupObject(Object3D* obj);
    void drawObjects();
    void updateObject(double timeStep);
    void mainLoop();

};
