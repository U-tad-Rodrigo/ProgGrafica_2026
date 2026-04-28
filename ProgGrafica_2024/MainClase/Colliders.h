//
// Created by mokiu on 27/04/2026.
//

#ifndef PROGGRAFICA_2024_COLLIDERS_H
#define PROGGRAFICA_2024_COLLIDERS_H
#include "common.h"
#include "libMath.h"
using namespace std;
using namespace libMath;

typedef struct {
    vec4float pos;
    vec4float size;

}particle3D;

class Collider {
    protected:
    vector<particle3D> particleList;
    public:
    Collider(){};
    virtual bool collisionTest(Collider* coll)= 0;
    virtual bool addParticle(particle3D* particle)= 0;
    virtual void updateParticle(matrix4x4f mat)= 0;
};

class Sphere : public Collider {
    public:
    float radius = 0;
    vec4float center = {0,0,0,1};

    virtual bool collisionTest(Collider* coll)override;
    virtual bool addParticle(particle3D* particle)override;
    virtual void updateParticle(matrix4x4f mat)override;
};

class ColliderTree {
    public:

};


#endif //PROGGRAFICA_2024_COLLIDERS_H
