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
     public:
     void update();
     Enemy();
     Enemy(glm::vec3 position, glm::vec3 direction);
     ~Enemy();
     
};
#endif