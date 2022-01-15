#include "player.hpp"

int Player::collideWith(Model model)
{
     
}
int Player::collideWithSight(Model m)
{

}
Player::Player()
{

     this->position = glm::vec3(0.0f);
     this->camera.position = position;
     this->gun = Gun(position + glm::normalize(camera.direction) + 2.0f);
}
Player::Player(glm::vec3 position)
{
     this->position = position;
     this->camera.position = position;
     this->gun = Gun(position + glm::normalize(camera.direction) + 2.0f);
}
Player::~Player()
{

}