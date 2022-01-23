#include "../src/renderingHead/objloader.hpp"

int main(int argc, const char** argv)
{
     const char* path = argc == 2 ? argv[1] : "assets/cube.obj";
     std::vector<glm::vec3> out_vertices;
     std::vector<glm::vec2> out_uvs;
     std::vector<glm::vec3> out_normals;

     int error = loadOBJ(path, out_vertices, out_uvs, out_normals);

     for(glm::vec3 vertex : out_vertices )
     {
          printf("(%f, %f, %f) \n", vertex.x, vertex.y, vertex.z);
     }
     for(glm::vec2 uv : out_uvs )
     {
          printf("(%f, %f) \n", uv.x, uv.y);
     }
     for(glm::vec3 normal : out_normals )
     {
          printf("(%f, %f, %f) \n", normal.x, normal.y, normal.z);
     }
     return error;
}