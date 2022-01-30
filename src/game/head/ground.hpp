#ifndef _GROUND_HPP
#define _GROUND_HPP
#include <stdio.h>
#include <stdlib.h>

#include <vector>

#include <GL/glew.h>

#include <glm/glm.hpp>

#include "../../renderingHead/model.hpp"

class Ground
{
     public:
     Model model;
     glm::vec3 position;
     public:
     Ground();
     ~Ground();
     void setPos();
     void setAmbientLightFactor();
};

#endif