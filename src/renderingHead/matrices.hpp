#ifndef _MATRICES_HPP
#define _MATRICES_HPP
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>

#include "../constants.hpp"

extern int error;
extern GLFWwindow* window;

//the spectial matrices
#define IDENTITY_MATRIX glm::mat4(1.0f)
#define ROTATION_MATRIX(alpha, beta, gamma) glm::mat4(glm::vec4(cos(beta) * cos(gamma), cos(beta) * sin(gamma), -sin(beta), 0), glm::vec4(sin(alpha) * sin(beta) * cos(gamma) - cos(alpha) * sin(gamma), sin(alpha) * sin(beta) * sin(gamma) + cos(alpha) * cos(gamma), sin(alpha) * cos(beta), 0), glm::vec4(cos(alpha) * sin(beta) * cos(gamma) + sin(alpha) * sin(gamma), cos(alpha) * sin(beta) * sin(gamma) - sin(alpha) * cos(gamma), cos(alpha) * cos(beta) ,0), glm::vec4(0, 0, 0, 1))
glm::mat4 getRotationMatrix(double alpha, double beta, double gamma);



#endif