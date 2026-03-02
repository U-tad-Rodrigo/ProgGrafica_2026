//
// Created by Rodrigo on 10/02/2026.
//

#include "Render.h"

#include "EventManager.h"

Render::Render(){
    initialized = false;
    // Inicializar GLFW
    if (!glfwInit())
    {
        std::cerr << "ERROR: Failed to initialize glfw" << std::endl;
        return;
    }
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    this->window = glfwCreateWindow(800, 600, "Hello Triangle", nullptr, nullptr);
    if (!window)
    {
        std::cerr << "ERROR: Failed to create window" << std::endl;
        glfwTerminate();
        return;
    }
    glfwMakeContextCurrent(window);

    if (!gladLoadGL(glfwGetProcAddress))
    {
        std::cerr << "ERROR: Failed to initialize GLAD" << std::endl;
        glfwTerminate();
        return;
    }

    EventManager::initEventManager(window);

    // Configurar OpenGL
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);  // Gris-verdoso para ver que funciona

    glViewport(0, 0, 800, 600);

    initialized = true;
}

void Render::setupObject(Object3D *obj) {
    bufferObject_t bo = {0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF};
    glGenVertexArrays(1, &bo.bufferId);
    glGenBuffers(1, &bo.vertexBufferId);
    glGenBuffers(1, &bo.indexBufferId);

    glBindVertexArray(bo.bufferId);

    glBindBuffer(GL_ARRAY_BUFFER, bo.vertexBufferId);
    glBufferData(GL_ARRAY_BUFFER, obj->vertexList.size() * sizeof(vertex_t), obj->vertexList.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bo.indexBufferId);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, obj->indexList.size() * sizeof(unsigned int), obj->indexList.data(), GL_STATIC_DRAW);

    glBindVertexArray(0);

    bufferedObjectList[obj->objectId] = bo;
}

void Render::drawObjects() {
    matrix4x4f proj = cam->computeProjectionMatrix(100.0f, 0.1f, PI/4.0f, 4.0f/3.0f);
    matrix4x4f projT = transpose(proj);

    glMatrixMode(GL_PROJECTION);
    glLoadMatrixf(projT.mat);
    matrix4x4f view = cam->computeViewMatrix();
    matrix4x4f viewT = transpose(view);

    glMatrixMode(GL_MODELVIEW);
    glLoadMatrixf(viewT.mat);

    for (auto& obj : objectList) {
        auto bo = bufferedObjectList[obj->objectId];
        glPushMatrix();

        matrix4x4f model = obj->computeModelMatrix();
        matrix4x4f modelT = transpose(model);
        glMultMatrixf(modelT.mat);

        glBindVertexArray(bo.bufferId);
        glBindBuffer(GL_ARRAY_BUFFER, bo.vertexBufferId);

        glEnableClientState(GL_VERTEX_ARRAY);
        glEnableClientState(GL_COLOR_ARRAY);
        glVertexPointer(4, GL_FLOAT, sizeof(vertex_t), (void*)offsetof(vertex_t, position));
        glColorPointer(4, GL_FLOAT, sizeof(vertex_t), (void*)offsetof(vertex_t, color));

        glDrawElements(GL_TRIANGLES, obj->indexList.size(), GL_UNSIGNED_INT, nullptr);

        glDisableClientState(GL_COLOR_ARRAY);
        glDisableClientState(GL_VERTEX_ARRAY);
        glBindVertexArray(0);

        glPopMatrix();
    }
}
void Render::updateObject(double timestep) {
    cam->moveCamera(timestep);
    for (auto& obj : objectList) {
        obj->moveObject(timestep);
    }
}

void Render::mainLoop() {
    if (!initialized || window == nullptr) {
        return;
    }
    double lastTime = glfwGetTime();
    double newTime = 0;
    double deltaTime = 0;

    while (!glfwWindowShouldClose(window))
    {
        EventManager::updateEvents();

        newTime = glfwGetTime();
        deltaTime = newTime - lastTime;
        lastTime = newTime;

        updateObject(deltaTime);

        if (EventManager::keyMap[GLFW_KEY_ESCAPE]) {
            glfwSetWindowShouldClose(window, true);
        }

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        drawObjects();
        glfwSwapBuffers(window);
    }

}
