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
#include "raycast.hpp"
#include "collider/collider.hpp"


extern GLFWwindow* window;
extern int error;



class Player
{
     public:
     glm::vec3 position;
     glm::vec3 direction;
     Camera camera;
     Gun gun;
     Ray sight;
     SimpleBoxCollider collider;

     public:
     Player();
     int collideWithSight(Model model);
     int collideWith(Model model);
     void update();
     ~Player();
     private:
     glm::vec3 getGunPosition();

};

#endif