#include "collider.hpp"

SimpleBoxCollider::SimpleBoxCollider()
{
     //Default contructor
}

SimpleBoxCollider::SimpleBoxCollider(glm::vec3 A, glm::vec3 G)
{
     this->A = A;
     this->G = G;
}
SimpleBoxCollider::~SimpleBoxCollider()
{

}