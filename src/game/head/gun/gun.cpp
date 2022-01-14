#include "gun.hpp"

Gun::Gun()
{
     
}

Gun::Gun( glm::vec3 position)
{
     this->model = Model("assets/gun.DDS", "assets/gun.obj");
     this->position = position;
     this->model.position = position;
     
}
void Gun::update()
{
     this->model.position = position;
}

Gun::~Gun()
{
     
}