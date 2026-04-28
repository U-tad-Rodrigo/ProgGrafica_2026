//
// Created by mokiu on 27/04/2026.
//

#include "Colliders.h"

bool Sphere::collisionTest(Collider *coll) {
    Sphere* other = (Sphere*)coll;
    return distance(this->center, other->center) < (this->radius + other->radius);
}

bool Sphere::addParticle(particle3D* particle) {
    this->particleList.push_back(*particle);
    float newRadius = length(particle->size) / 2;
    vec4float newCenter = particle->pos;
    float dist = distance(this->center, newCenter);
    if (dist + newRadius > this->radius) {
        this->radius = dist + newRadius;
    }
    return true;
}
