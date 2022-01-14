#include "raycast.hpp"

Ray::Ray()
{
     //default contructor (should not be used)
}
Ray::Ray(glm::vec3 origin, glm::vec3 direciton)
{
     this->origin = origin;
     this->direction = direciton;
}