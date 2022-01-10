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





void computeMatricesFromInputs();

glm::mat4 getProjectionMatrix();

glm::mat4 getViewMatrix();


#endif