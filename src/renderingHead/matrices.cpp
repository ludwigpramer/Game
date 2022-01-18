#include "matrices.hpp"

glm::mat4 getRotationMatrix(double alpha, double beta, double gamma)
{
     return glm::mat4(glm::vec4(cos(beta) * cos(gamma), cos(beta) * sin(gamma), -sin(beta), 0),
               glm::vec4(sin(alpha) * sin(beta) * cos(gamma) - cos(alpha) * sin(gamma), sin(alpha) * sin(beta) * sin(gamma) + cos(alpha) * cos(gamma), sin(alpha) * cos(beta), 0),
               glm::vec4(cos(alpha) * sin(beta) * cos(gamma) + sin(alpha) * sin(gamma), cos(alpha) * sin(beta) * sin(gamma) - sin(alpha) * cos(gamma), cos(alpha) * cos(beta) ,0),
               glm::vec4(0, 0, 0, 1));
}