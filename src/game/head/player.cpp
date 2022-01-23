#include "player.hpp"

glm::vec3 Player::getGunPosition()
{
     return position + glm::normalize(direction) * 2.0f;
}


void Player::update(int* windowFullscreen)
{
     controller.update(windowFullscreen);

     position = controller.getPositionVector();
     direction = controller.getDirectionVector();
     up = controller.getUpVector();

     //TODO REMOVE gun.update(position, direction);
     camera.update(position, direction, up, controller.getProjectionMatrix(), controller.getViewMatrix());
}

Player::Player()
{
     this->up = G_UP;
     this->direction = PLAYER_STARTING_DIRECTION;
     this->position = PLAYER_STARTING_POS;
     this->camera.position = position;
   //TODO REMOVE  this->gun = Gun(position + glm::normalize(direction) + 2.0f, direction);
    //TODO REMOVE this->gun = Gun(glm::vec3(10.0f, 0.0f, 0.0f), direction);
}

Player::~Player()
{

}