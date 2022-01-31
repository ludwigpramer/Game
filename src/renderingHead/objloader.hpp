#ifndef _OBJLOADER_HPP
#define _OBJLOADER_HPP

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <iostream>
#include <fstream>
#include <ostream>
#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


int loadOBJ(const char* path, std::vector<glm::vec3> &out_vertices, std::vector<glm::vec2> &out_uvs, std::vector<glm::vec3> &out_normals);

#endif