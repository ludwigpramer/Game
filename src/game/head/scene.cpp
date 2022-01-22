#include "scene.hpp"

void Scene::add(Model model)
{
     contents.push_back(model);
}

void Scene::add(Enemy enemy)
{
     enemies.push_back(enemy);
}

void Scene::update(int* windowFullscreen)
{

     player.update(windowFullscreen);

     for(Enemy e : enemies)
     {
          e.update();
     }
     
}

Scene::Scene()
{
     //default contructor
}

Scene::Scene(Player player)
{
     this->contents = std::vector<Model>();
     this->player = player;
}

Scene::Scene(std::vector<Model> contents, Player player)
{
     this->contents = contents;
     this->player = player;
}

Scene::~Scene()
{
     //default contructor
}