#ifndef _RAYCAST_HPP
#define _RAYCAST_HPP

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include <glm/glm.hpp>

extern int error;

class Ray
{
     public:
     glm::vec3 origin;
     glm::vec3 direction;
     public:
     Ray();
     Ray(glm::vec3 origin, glm::vec3 direction);
     ~Ray();
};
#endif