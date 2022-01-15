#ifndef _GUN_HPP
#define _GUN_HPP
#include <stdio.h>
#include <stdlib.h>

#include <vector>

#include <glm/glm.hpp>

#include "../../../constants.hpp"



#include "../model.hpp"

class Gun
{    
     public:
     Model model;
     glm::vec3 position;
     
     public:
     Gun();
     Gun(glm::vec3 position);
     ~Gun();
     private:
     void update();
};

#endif