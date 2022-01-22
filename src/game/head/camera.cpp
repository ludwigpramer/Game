#include "camera.hpp"

Camera::Camera()
{
     //default constructor
}
void Camera::update(glm::vec3 position, glm::vec3 direction, glm::vec3 up, glm::mat4 ProjectionMatix, glm::mat4 ViewMatrix)
{
     this->position = position;
     this->direction = direction;
     this->up = up;
     this->ProjectionMatrix = ProjectionMatix;
     this->ViewMatrix = ViewMatrix;
     
}
Camera::~Camera()
{
     //destructor
}