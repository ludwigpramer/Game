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

     gun.update(position);
     camera.update(position, direction, up, controller.getProjectionMatrix(), controller.getViewMatrix());
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