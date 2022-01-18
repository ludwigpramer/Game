#include "collider.hpp"


int SimpleBoxCollider::collideWith(Ray r)
{
     glm::vec3 P;
     for(r.t = 0; r.t <= 1000;r.t += 0.001)
     {
          P = r.origin + r.direction * float(r.t);
          
          if(P.x >= A.x && P.x <= B.x && P.y >= A.y && P.y <= B.y && P.z >= A.z && P.z <= B.z)
          {
               return 1;
          }
          continue;
     }

     return 0;
}
int SimpleBoxCollider::collideWith(SimpleBoxCollider c)
{
     return 0;
}

SimpleBoxCollider::SimpleBoxCollider()
{
     //Default contructor
}

SimpleBoxCollider::SimpleBoxCollider(glm::vec3 A, glm::vec3 G)
{
     this->A = A;
     this->B = G;
}
SimpleBoxCollider::~SimpleBoxCollider()
{

}