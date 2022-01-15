#include "gun.hpp"

Gun::Gun()
{
     
}

Gun::Gun( glm::vec3 position)
{
     this->model = Model(GUN_TEXTURE_PATH, GUN_OBJ_PATH);
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

void Gun::update()
{
     position = getPositionVector() + glm::vec3();
}