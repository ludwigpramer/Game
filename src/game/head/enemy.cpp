#include "enemy.hpp"

void Enemy::update()
{
     this->model.position = position;
}
Enemy::Enemy()
{
     //default contructor
}
Enemy::Enemy(glm::vec3 position, glm::vec3 direction)
{
     this->position = position;
     this->direction = direction;
}
Enemy::~Enemy()
{
     //decontructor
}
