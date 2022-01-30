#ifndef _LINE_HPP
#define _LINE_HPP
#include <stdio.h>
#include <stdlib.h>

#include <GL/glew.h>
#include <glm/glm.hpp>

class Line
{
     public:
     glm::vec3 start, end;
     public:
     Line();
     Line(glm::vec3 start, glm::vec3 end);
     ~Line();
};
#endif