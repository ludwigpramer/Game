#include "scene.hpp"

void Scene::add(Model model)
{
     contents.push_back(model);
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