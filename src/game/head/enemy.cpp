#include "enemy.hpp"
#include "../../renderingHead/cube.hpp"
#include "../../renderingHead/vboindexing.hpp"

void Enemy::update()
{
     //The update method
}
void Enemy::setPos(glm::vec3 position)
{
     this->position = position;
     model.setPos(position);
}
void Enemy::setRot(double alpha, double beta, double gamma)
{
     model.setRot(alpha, beta, gamma);
}
Enemy::Enemy()
{
     model.vertices = cub_vertices;
     model.uvs = cub_uvs;
     model.normals = cub_normals;
     indexVBO(model.vertices, model.uvs, model.normals, model.indexed_vertices, model.indexed_uvs, model.indexed_normals, model.indices);

     model.setTexture("assets/uvmap.DDS");

     position = glm::vec3(0.0f, 1.0f, 0.0f);
     model.setPos(position);
}
Enemy::~Enemy()
{
     //decontructor
}
