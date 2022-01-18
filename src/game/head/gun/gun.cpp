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

void Gun::update(glm::vec3 playerPosition, glm::vec3 playerDirection)
{
     position = glm::vec3(0, 0, 0);
     //position = playerPosition + glm::normalize(playerDirection) * 2.0f;
     model.setPos(position);
     model.ModelMatrix = model.ModelMatrix * ROTATION_MATRIX(170, 0, 0);

}