#ifndef _SCENE_HPP
#define _SCENE_HPP
#include <stdio.h>
#include <stdlib.h>

#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "../../constants.hpp"

#include "model.hpp"
#include "player.hpp"

class Scene
{
     public:
     std::vector<Model> contents;
     Player player;

     public:
     void add(Model model);
     Scene(Player player);
     Scene(std::vector<Model> contents, Player player);
     ~Scene();

};

#endif