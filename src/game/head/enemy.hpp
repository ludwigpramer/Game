#ifndef _ENEMY_HPP
#define _ENEMY_HPP
#include <stdio.h>
#include <stdlib.h>

#include <vector>

#include <glm/glm.hpp>

#include "../../constants.hpp"
#include "model.hpp"

class Enemy
{
     public:
     Model model;
     glm::vec3 position;
     glm::vec3 direction;
     glm::vec3 velocity;
     public:
     void update();
     void setPos(glm::vec3 position);
     void setRot(double alpha, double beta, double gamma);
     Enemy();
     ~Enemy();
     
};
#endif