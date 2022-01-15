#include "camera.hpp"

Camera::Camera()
{
     //default constructor
}
void Camera::update(glm::vec3 position, glm::vec3 direction, glm::vec3 up)
{
     this->position = position;
     this->direction = direction;
     this->up = up;
     this->ProjectionMatrix = getProjectionMatrix();
     this->ViewMatrix = getViewMatrix();
     
}
Camera::~Camera()
{
     //destructor
}