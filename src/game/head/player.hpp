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
#include "gun.hpp"
#include "raycast.hpp"
#include "collider.hpp"


extern GLFWwindow* window;
extern int error;



class Player
{
     public:
     glm::vec3 position;
     glm::vec3 direction;
     glm::vec3 up;

     Controller controller;

     Camera camera;
     //TODO REMOVEGun gun;
     Ray sight;
     SimpleBoxCollider collider;

     public:
     Player();
     int collideWithSight(Model model);
     int collideWith(Model model);
     void update(int* windowFullscreen);
     ~Player();
     private:
     glm::vec3 getGunPosition();

};

#endif