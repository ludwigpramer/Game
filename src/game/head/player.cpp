#include "player.hpp"

glm::vec3 Player::getGunPosition()
{
     return position + glm::normalize(direction) * 2.0f;
}

int Player::collideWith(Model model)
{
     (void) model;
     return 0;
}
int Player::collideWithSight(Model model)
{
     (void) model;
     return 0;
}
void Player::update()
{
     controller.update();

     position = controller.getPositionVector();
     direction = controller.getDirectionVector();
     up = controller.getUpVector();

     gun.update(position, direction);
     camera.update(position, direction, up, controller.getProjectionMatrix(), controller.getViewMatrix());
}

Player::Player()
{
     this->up = G_UP;
     this->direction = PLAYER_STARTING_DIRECTION;
     this->position = PLAYER_STARTING_POS;
     this->camera.position = position;
     this->gun = Gun(position + glm::normalize(direction) + 2.0f, direction);
     this->gun = Gun(glm::vec3(10.0f, 0.0f, 0.0f), direction);
}

Player::~Player()
{

}