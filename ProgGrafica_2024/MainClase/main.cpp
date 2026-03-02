#define GLAD_BIN
#include "common.h"
#include "EventManager.h"
#include "Object3D.h"
#include "Render.h"


void drawObject(Object3D& obj) {
    glBegin(GL_TRIANGLES);
    {
        auto model = obj.computeModelMatrix();
        for (auto& i : obj.indexList) {
            auto v = obj.vertexList[i];
            v.position = model * v.position;
            glColor3f(v.color.x, v.color.y, v.color.z);
            glVertex3f(v.position.x, v.position.y, v.position.z);
        }

    }
    glEnd();
}

int main(int argc, char** argv)
{
    auto r = new Render();
    auto obj = new Object3D();
    r->setupObject(obj);
    r->objectList.push_back(obj);
    r->mainLoop();

    glfwTerminate();
    return 0;
}
