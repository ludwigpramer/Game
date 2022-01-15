#include "camera.hpp"

Camera::Camera()
{
     //default constructor
}
void Camera::update()
{
     computeMatricesFromInputs();
     this->ProjectionMatrix = getProjectionMatrix();
     this->ViewMatrix = getViewMatrix();
     this->position = getPositionVector();
     this->direction = getDirectionVector();
}
Camera::~Camera()
{
     //destructor
}