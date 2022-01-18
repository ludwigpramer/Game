#ifndef _GUN_HPP
#define _GUN_HPP
#include <stdio.h>
#include <stdlib.h>

#include <vector>

#include <glm/glm.hpp>
#include <glm/gtx/vector_angle.hpp>

#include "../../../constants.hpp"

#include "../model.hpp"
#include "../controls.hpp"
#include "../../../renderingHead/matrices.hpp"

class Gun
{    
     public:
     Model model;
     glm::vec3 position;
     glm::vec3 direction;
     double alpha, beta, gamma;
     
     public:
     Gun();
     Gun(glm::vec3 position, glm::vec3 direction);
     ~Gun();
     void update(glm::vec3 playerPosition, glm::vec3 playerDirection);
};

#endif