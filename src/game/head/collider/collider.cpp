#include "collider.hpp"


int collideWith(SimpleBoxCollider c, Ray r)
{
     glm::vec3 P;
     for(r.t = 0; r.t <= 1000;r.t += 0.001)
     {
          P = r.origin + r.direction * float(r.t);
          
          if(P.x >= c.A.x && P.x <= c.B.x && P.y >= c.A.y && P.y <= c.B.y && P.z >= c.A.z && P.z <= c.B.z)
          {
               return 1;
          }
          continue;
     }

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