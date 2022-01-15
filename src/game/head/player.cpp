#include "player.hpp"

int Player::collideWith(Model model)
{
     return 0;
}
int Player::collideWithSight(Model model)
{
     
     return 0;
}
Player::Player()
{

     this->position = PLAYER_STARTING_POS;
     this->camera.position = position;
     this->gun = Gun(position + glm::normalize(camera.direction) + 2.0f);
}

Player::~Player()
{

}