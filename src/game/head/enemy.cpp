#include "enemy.hpp"

void Enemy::update()
{

}
void Enemy::setPos(glm::vec3 position)
{
     this->position = position;
     model.setPos(position);
}
void Enemy::setRot(double alpha, double beta, double gamma)
{
     model.setRot(alpha, beta, gamma);
}
Enemy::Enemy()
{
     model = Model("assets/uvmap1.DDS", "assets/cube.obj");
     position = glm::vec3(0.0f);
     model.setPos(position);
}
Enemy::~Enemy()
{
     //decontructor
}
