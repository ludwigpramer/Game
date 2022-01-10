#ifndef _VBOINDEXING
#define _VBOINDEXING

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include <vector>
#include <map>

#include <glm/glm.hpp>

#include "../constants.hpp"

void indexVBO(std::vector<glm::vec3> &in_vertices, std::vector<glm::vec2> &in_uvs, std::vector<glm::vec3> &in_normals, std::vector<glm::vec3> &out_vertices, std::vector<glm::vec2> &out_uvs, std::vector<glm::vec3> &out_normals, std::vector<unsigned short> &out_indices);

#endif
