#ifndef _CAMERA_HPP
#define _CAMERA_HPP
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "../../constants.hpp"
#include "controls.hpp"

extern GLFWwindow* window;
extern int error;

class Camera
{
     public:
     glm::vec3 up;
     glm::vec3 direction;
     glm::vec3 position;
     glm::mat4 ViewMatrix;
     glm::mat4 ProjectionMatrix;
     public:
     Camera();
     Camera(glm::vec3 position);
     void update(glm::vec3 position, glm::vec3 direction, glm::vec3 up);
     ~Camera();
};

#endif