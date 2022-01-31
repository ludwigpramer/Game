#include "text.hpp"


GLuint TextTextureID;
GLuint textvertexbuffer;
GLuint textuvbuffer;
GLuint textshaderprogram;
GLuint TextUniformID;


void initText(const char* texttexturepath)
{
     TextTextureID = load(texttexturepath);
     textshaderprogram = LoadShaders("src/renderingHead/Shaders/TextVertexShader.vs", "src/renderingHead/Shaders/TextFragmentShader.fs");

     glGenBuffers(1, &textvertexbuffer);
     glGenBuffers(1, &textuvbuffer);
     

     TextUniformID = glGetUniformLocation(textshaderprogram, "myTextureSampler");
}
void printText(const char * text, int x, int y, int size)
{

	unsigned int length = strlen(text);

	// Fill buffers
	std::vector<glm::vec2> vertices;
	std::vector<glm::vec2> UVs;
	for ( unsigned int i=0 ; i<length ; i++ ){
		
		glm::vec2 vertex_up_left    = glm::vec2( x+i*size     , y+size );
		glm::vec2 vertex_up_right   = glm::vec2( x+i*size+size, y+size );
		glm::vec2 vertex_down_right = glm::vec2( x+i*size+size, y      );
		glm::vec2 vertex_down_left  = glm::vec2( x+i*size     , y      );

		vertices.push_back(vertex_up_left   );
		vertices.push_back(vertex_down_left );
		vertices.push_back(vertex_up_right  );

		vertices.push_back(vertex_down_right);
		vertices.push_back(vertex_up_right);
		vertices.push_back(vertex_down_left);

		char character = text[i];
		float uv_x = (character%16)/16.0f;
		float uv_y = (character/16)/16.0f;

		glm::vec2 uv_up_left    = glm::vec2( uv_x           , uv_y );
		glm::vec2 uv_up_right   = glm::vec2( uv_x+1.0f/16.0f, uv_y );
		glm::vec2 uv_down_right = glm::vec2( uv_x+1.0f/16.0f, (uv_y + 1.0f/16.0f) );
		glm::vec2 uv_down_left  = glm::vec2( uv_x           , (uv_y + 1.0f/16.0f) );
		UVs.push_back(uv_up_left   );
		UVs.push_back(uv_down_left );
		UVs.push_back(uv_up_right  );

		UVs.push_back(uv_down_right);
		UVs.push_back(uv_up_right);
		UVs.push_back(uv_down_left);
	}
	glBindBuffer(GL_ARRAY_BUFFER, textvertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec2), &vertices[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, textuvbuffer);
	glBufferData(GL_ARRAY_BUFFER, UVs.size() * sizeof(glm::vec2), &UVs[0], GL_STATIC_DRAW);

	// Bind shader
	glUseProgram(textshaderprogram);

	// Bind texture
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, TextTextureID);
	// Set our "myTextureSampler" sampler to use Texture Unit 0
	glUniform1i(textuvbuffer, 0);

	// 1rst attribute buffer : vertices
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, textvertexbuffer);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (void*)0 );

	// 2nd attribute buffer : UVs
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, textuvbuffer);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0 );

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Draw call
	glDrawArrays(GL_TRIANGLES, 0, vertices.size() );

	glDisable(GL_BLEND);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);

     glBindTexture(TextTextureID, 0);

}


void cleanupText()
{
     glDeleteBuffers(1, &textvertexbuffer);
     glDeleteBuffers(1, &textuvbuffer);

     glDeleteTextures(1, &TextTextureID);

     glDeleteShader(textshaderprogram);
}