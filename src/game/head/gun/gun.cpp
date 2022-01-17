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

Gun::~Gun()
{
     
}

void Gun::update(glm::vec3 playerPosition)
{
     position = playerPosition + glm::vec3();
     this->model.position = position;
}