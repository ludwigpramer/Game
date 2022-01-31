#include <stdio.h>
#include <string.h>
// int main(int argc, const char** argv)
// {
//      const char* path = argc == 2 ? argv[1] : "assets/cube.obj";
//      std::vector<glm::vec3> out_vertices;
//      std::vector<glm::vec2> out_uvs;
//      std::vector<glm::vec3> out_normals;

//      int error = loadOBJ(path, out_vertices, out_uvs, out_normals);

//      for(glm::vec3 vertex : out_vertices )
//      {
//           printf("(%f, %f, %f) \n", vertex.x, vertex.y, vertex.z);
//      }
//      for(glm::vec2 uv : out_uvs )
//      {
//           printf("(%f, %f) \n", uv.x, uv.y);
//      }
//      for(glm::vec3 normal : out_normals )
//      {
//           printf("(%f, %f, %f) \n", normal.x, normal.y, normal.z);
//      }
//      return error;
// }

int main(int argc, const char** argv)
{
     printf("Hello WORLD\n");
     const char* path = argc == 2 ? argv[1] : "assets/uvmap.DDS";
     unsigned char header[124];

	FILE *fp; 
 
	/* try to open the file */ 
	fp = fopen(path, "rb"); 
	if (fp == NULL){
		printf("%s could not be opened. Are you in the right directory ? Don't forget to read the FAQ !\n", path); getchar(); 
		return 0;
	}
   
	/* verify the type of file */ 
	char filecode[4]; 
	fread(filecode, 1, 4, fp); 
	if (strncmp(filecode, "DDS ", 4) != 0) { 
		fclose(fp); 
		return 0; 
	}
	
	/* get the surface desc */ 
	fread(&header, 124, 1, fp); 

	unsigned int height = *(unsigned int*)&(header[8]);
	unsigned int width = *(unsigned int*)&(header[12]);
	unsigned int linearSize	 = *(unsigned int*)&(header[16]);
	unsigned int mipMapCount = *(unsigned int*)&(header[24]);
	unsigned int fourCC      = *(unsigned int*)&(header[80]);

 
	unsigned char * buffer;
	unsigned int bufsize;
	/* how big is it going to be including all mipmaps? */ 
	bufsize = mipMapCount > 1 ? linearSize * 2 : linearSize; 
	buffer = new unsigned char[bufsize];
	fread(buffer, 1, bufsize, fp); 
	/* close the file pointer */ 

     printf("height: %u\nwidth: %u\nlinearSize: %u\n mipMapCount: %u\n fourCC: %u\n buffer: %s\n bufsize: %u\n", height, width, linearSize, mipMapCount, fourCC, buffer, bufsize);
	fclose(fp);
     delete[] buffer;
}