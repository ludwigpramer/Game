#ifndef _COLLIDER_HPP
#define _COLLIDER_HPP
#include <stdio.h>
#include <stdlib.h>

#include <vector>

#include <glm/glm.hpp>

#include "../../../constants.hpp"
#include "../raycast.hpp"


class SimpleBoxCollider
{
     public:
     glm::vec3 A;
     glm::vec3 B;
     public:
     SimpleBoxCollider();
     SimpleBoxCollider(glm::vec3 A, glm::vec3 G);
     ~SimpleBoxCollider();
};

void CollideWith(SimpleBoxCollider c, Ray r);
#endif