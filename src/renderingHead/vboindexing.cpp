#include "vboindexing.hpp"

//returns 1 if v1 can be considered equal ot v2 else 0
int isNear(float v1, float v2);
//Searches through all already exported vertices for a similar one
int getSimilarVertexIndex(glm::vec3 &in_vertex, glm::vec2 &in_uc, glm::vec3 &in_normal, std::vector<glm::vec3> &out_vertices, std::vector<glm::vec2> &out_uvs, std::vector<glm::vec3> &out_normals, unsigned short &result);

void indexVBO(std::vector<glm::vec3> &in_vertices, std::vector<glm::vec2> &in_uvs, std::vector<glm::vec3> &in_normals, std::vector<glm::vec3> &out_vertices, std::vector<glm::vec2> &out_uvs, std::vector<glm::vec3> &out_normals, std::vector<unsigned short> &out_indices)
{
     for(int i = 0; i < in_vertices.size(); i++)
     {
          unsigned short index;
          int found = getSimilarVertexIndex(in_vertices[i], in_uvs[i], in_normals[i], out_vertices, out_uvs, out_normals, index);
          if(found)
          {
               out_indices.push_back(index);
          } 
          else
          {
               out_vertices.push_back(in_vertices[i]);
               out_uvs.push_back(in_uvs[i]);
               out_normals.push_back(in_normals[i]);
               out_indices.push_back((unsigned short)out_vertices.size() -1);
          }
     }
}

int isNear(float v1, float v2)
{
     return fabs(v1-v2) < 0.01f;
}
int getSimilarVertexIndex(glm::vec3 &in_vertex, glm::vec2 &in_uv, glm::vec3 &in_normal, std::vector<glm::vec3> &out_vertices, std::vector<glm::vec2> &out_uvs, std::vector<glm::vec3> &out_normals, unsigned short &result)
{
     for(int i = 0; i<out_vertices.size(); i++)
     {
          if(
               isNear(in_vertex.x, out_vertices[i].x) &&
               isNear(in_vertex.y, out_vertices[i].y) &&
               isNear(in_vertex.z, out_vertices[i].z) &&
               isNear(in_uv.x, out_uvs[i].x) &&
               isNear(in_uv.y, out_uvs[0].y) &&
               isNear(in_normal.x, out_normals[0].x) &&
               isNear(in_normal.y, out_normals[0].y) &&
               isNear(in_normal.z, out_normals[0].z) 
               
          )
          {
               result = i;
               return 1;
          }
     }
     return 0;
}