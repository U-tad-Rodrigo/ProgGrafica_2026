#pragma once

#include "libMath.h"

typedef struct {
        vec4float posicion;
        vec4float color;
}vertex_t;


class Object3D {
public:
        vector<vertex_t> vertexList;
        vec4float position = {0, 0, 0, 1};
        Object3D();
};
