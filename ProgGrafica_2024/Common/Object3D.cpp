//
// Created by Rodrigo on 09/02/2026.
//

#include "Object3D.h"

Object3D::Object3D() {
    vertexList = {
        {{   0,  0.5, 0 , 1 },{ 1, 0, 1, 1}},
        {{-0.5, -0.5, 0 , 1 },{ 1, 1, 0, 1}},
        {{ 0.5, -0.5, 0 , 1 },{ 0, 0, 1, 1}}
    };
}