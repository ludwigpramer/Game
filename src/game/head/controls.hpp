#ifndef _controls
#define _controls

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>

#include "../../constants.hpp"


class Controller
{
     private:
     glm::mat4 ViewMatrix;

     glm::mat4 ProjectionMatrix;

     glm::vec3 position = CAMERA_STARTING_POS;

     glm::vec3 direction;

     glm::vec3 up;

     int mouseBound = MOUSE_BOUND;

     float horizontalAngle = 90.0f;

     float verticalAngle = 0.0f;

     float initialFoV = 45.0f;

     float speed = BASE_SPEED;

     float mouseSpeed = MOUSE_SPEED;

     double lastTime;
     public:
     Controller();
     ~Controller();

     void update();

     glm::mat4 getProjectionMatrix();

     glm::mat4 getViewMatrix();

     glm::vec3 getPositionVector();

     glm::vec3 getDirectionVector();

     glm::vec3 getUpVector();
};


#endif