#ifndef _PLAYER_HPP
#define _PLAYER_HPP

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>

#include "../../constants.hpp"
#include "camera.hpp"
#include "gun/gun.hpp"


extern GLFWwindow* window;
extern int error;



class Player
{
     public:
     glm::vec3 position;
     Camera camera;
     Gun gun;

     public:
     Player();
     Player(glm::vec3 position);
     ~Player();

};

#endif