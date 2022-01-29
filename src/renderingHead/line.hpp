#ifndef _LINE_HPP
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>

#include "../constants.hpp"

class Line {
public:
    GLuint shaderProgram;
    GLuint VBO, VAO;
    std::vector<float> vertices;
    glm::vec3 startPoint;
    glm::vec3 endPoint;
    glm::mat4 MVP;
    glm::vec3 lineColor;
public:
     Line(glm::vec3 start, glm::vec3 end);
     void setMVP(glm::mat4);
     void setColor(glm::vec3 color);
     ~Line();
};
#endif