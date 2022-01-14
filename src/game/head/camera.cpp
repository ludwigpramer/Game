#include "camera.hpp"

Camera::Camera()
{

}
Camera::Camera(glm::vec3 position)
{
     this->position = position;

}
void Camera::update()
{
     computeMatricesFromInputs();
     this->ProjectionMatrix = getProjectionMatrix();
     this->ViewMatrix = getViewMatrix();
}
Camera::~Camera()
{

}