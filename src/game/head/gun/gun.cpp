#include "gun.hpp"

Gun::Gun()
{
     
}

Gun::Gun( glm::vec3 position, glm::vec3 direction)
{
     update(position, direction);
     this->model = Model(GUN_TEXTURE_PATH, GUN_OBJ_PATH);
     this->position = position;
     this->model.position = position;
}

Gun::~Gun()
{
     
}

void Gun::update(glm::vec3 position, glm::vec3 direction)
{
     // this->position = position;
     this->position = glm::vec3(0.0f);
     this->direction = direction;

     this->model.setPos(position);

     this->alpha = glm::angle(direction, G_UP);
     model.ModelMatrix = model.ModelMatrix * ROTATION_MATRIX(this->alpha, 0, 0);

}