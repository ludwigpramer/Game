#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <vector>
#include <array>

#include "game.hpp"

#include "../constants.hpp"

#include "head/controls.hpp"

#include "../renderingHead/vboindexing.hpp"

#include "../renderingHead/shader.hpp"
#include "../renderingHead/texture.hpp"
#include "../renderingHead/objloader.hpp"

#define LOG

#ifdef DEBUG
#define lg printf("Log Point%d\n", i); i++
int i = 0;
#else
#define lg
#endif

//the globally used variables
GLFWwindow* window;

FILE* logFile;

GLuint LoadShaders(const char* vertex_file_path, const char* fragment_file_path);

void GenVao(GLuint* id);
int InitAll();
void loadBuffers(
    GLuint* vertexbuffer,
    GLuint* uvbuffer,
    GLuint* normalbuffer,
    GLuint* elementbuffer,
    std::vector<unsigned short> indices,
    std::vector<glm::vec3> indexed_vertices,
    std::vector<glm::vec2> indexed_uvs,
    std::vector<glm::vec3> indexed_normals);



    

int Game(void)
{ 
    int error = 0;

    GLuint ProgramID;

    GLuint VertexArrayID;
    GLuint TextureID;
    GLuint LightID;

    GLuint Texture;

    GLuint vertexbuffer;
    GLuint uvbuffer;
    GLuint normalbuffer;
    GLuint elementbuffer;

    GLuint MatrixID;
    GLuint ViewMatrixID;
    GLuint ModelMatrixID;

    error = InitAll();

    if(error != 0)
    {
        return error;
    }
    
    //Generate Vao
    GenVao(&VertexArrayID);
    
    ProgramID = LoadShaders("src/renderingHead/Shaders/ShadingVertexShader.vs", "src/renderingHead/Shaders/ShadingFragmentShader.fs");



    // Get a handle for  "MVP" uniform
	MatrixID = glGetUniformLocation(ProgramID, "MVP");
    ViewMatrixID = glGetUniformLocation(ProgramID, "V");
    ModelMatrixID = glGetUniformLocation(ProgramID, "M");

    
    Texture = loadDDS("assets/uvmap.DDS"); //loadDDS("imgs/uvmap.DDS");

    
    //read .obj file
    std::vector<glm::vec3> vertices;
    std::vector<glm::vec2> uvs;
    std::vector<glm::vec3> normals;
    error = loadOBJ("assets/suzanne.obj", vertices, uvs, normals);
    if(error != 0)
    {
        fprintf(stderr, "Error: Failed to load mesh.\n");
        return error;
    }
    
    //VBO indexing
    std::vector<unsigned short> indices;
    std::vector<glm::vec3> indexed_vertices;
    std::vector<glm::vec2> indexed_uvs;
    std::vector<glm::vec3> indexed_normals;
    indexVBO(vertices, uvs, normals, indexed_vertices, indexed_uvs, indexed_normals, indices);

    

    // Get a handle for  "myTextureSampler" uniform
	TextureID  = glGetUniformLocation(ProgramID, "myTextureSampler");
    
    //Make and load the buffers
    



    GLuint colorbuffer;  
    glGenBuffers(1, &colorbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_color_buffer_data), g_color_buffer_data, GL_STATIC_DRAW);

    LightID = glGetUniformLocation(ProgramID, "LightPosition_worldspace");
    
    double lastTime;
    int frames;
    lastTime = glfwGetTime();
    frames = 0;
    do
    {
        loadBuffers(
        &vertexbuffer,
        &uvbuffer,
        &normalbuffer,
        &elementbuffer,
        indices,
        indexed_vertices,
        indexed_uvs,
        indexed_normals);
        double currentTime;
        currentTime = glfwGetTime();
        frames++;
        if(currentTime - lastTime >= 1.0f)
        {
            logFps(frames);
            frames = 0;
            lastTime += 1.0f;
        }


        glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        computeMatricesFromInputs();
        
	    // Camera matrix
        glm::mat4 ProjectionMatrix = getProjectionMatrix();
	    glm::mat4 ViewMatrix  = getViewMatrix();

        
	    //Use the shaders
        glUseProgram(ProgramID);
        
        glm::vec3 lightPos = glm::vec3(4, 4, 4);
        glUniform3f(LightID, lightPos.x, lightPos.y, lightPos.y);
        //bind the contant matrix
        glUniformMatrix4fv(ViewMatrixID, 1, GL_FALSE, &ViewMatrix[0][0]);
        
        
        ////render first object////
	   

        glm::mat4 ModelMatrix1 = glm::mat4(1.0f);
        glm::mat4 MVP1 = ProjectionMatrix * ViewMatrix * ModelMatrix1;


        glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP1[0][0]);

        glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &ModelMatrix1[0][0]);

        // Bind texture in Texture Unit 0
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, Texture);
		//Set "myTextureSampler" sampler to use Texture Unit 0
		glUniform1i(TextureID, 0);

        
        //vertexBuffer
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
        glVertexAttribPointer(
           0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
           3,                  // size
           GL_FLOAT,           // type
           GL_FALSE,           // normalized?
           0,                  // stride
           (void*)0            // array buffer offset
        );
       
        
        //2nd attribute buffer: textures 
        glEnableVertexAttribArray(1);
        glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
        glVertexAttribPointer(
        1,                                // attribute. No particular reason for 1, but must match the layout in the shader.
        2,                                // size only 2
        GL_FLOAT,                         // type
        GL_FALSE,                         // normalized?
        0,                                // stride
        (void*)0                          // array buffer offset
        );

        
        //3rd attribute buffer: normals
        glEnableVertexAttribArray(2);
        glBindBuffer(GL_ARRAY_BUFFER, normalbuffer);
        glVertexAttribPointer(
            2,        //attribute
            3,        //size
            GL_FLOAT, //type
            GL_FALSE, //normalized
            0,        //stride
            (void*) 0 //offset
        );
        
        //Indexbuffer
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer);
        
        //draw the triangles
        glDrawElements( GL_TRIANGLES, (GLsizei) indices.size(), GL_UNSIGNED_SHORT, (void*)0);
        
        ////render second////
       
        glm::mat4 ModelMatrix2 = glm::mat4(1.0f);
        ModelMatrix2 = glm::translate(ModelMatrix2, glm::vec3(2.0f, 0.0f, 0.0f));
        glm::mat4 MVP2 = ProjectionMatrix * ViewMatrix * ModelMatrix2;


        glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP2[0][0]);

        glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &ModelMatrix2[0][0]);

        // Bind texture in Texture Unit 0
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, Texture);
		//Set "myTextureSampler" sampler to use Texture Unit 0
		glUniform1i(TextureID, 0);


        //vertexBuffer
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
        glVertexAttribPointer(
           0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
           3,                  // size
           GL_FLOAT,           // type
           GL_FALSE,           // normalized?
           0,                  // stride
           (void*)0            // array buffer offset
        );
       

        //2nd attribute buffer: textures 
        glEnableVertexAttribArray(1);
        glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
        glVertexAttribPointer(
        1,                                // attribute. No particular reason for 1, but must match the layout in the shader.
        2,                                // size only 2
        GL_FLOAT,                         // type
        GL_FALSE,                         // normalized?
        0,                                // stride
        (void*)0                          // array buffer offset
        );


        //3rd attribute buffer: normals
        glEnableVertexAttribArray(2);
        glBindBuffer(GL_ARRAY_BUFFER, normalbuffer);
        glVertexAttribPointer(
            2,        //attribute
            3,        //size
            GL_FLOAT, //type
            GL_FALSE, //normalized
            0,        //stride
            (void*) 0 //offset
        );

        //Indexbuffer
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer);

        //draw the triangles
        glDrawElements( GL_TRIANGLES, (GLsizei) indices.size(), GL_UNSIGNED_SHORT, 0);

        
        //diable the buffers
        glDisableVertexAttribArray(0);
        glDisableVertexAttribArray(1);
        glDisableVertexAttribArray(2);



        //Update Display
        glfwSwapBuffers(window);
        glfwPollEvents();
    } while(glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(window) == 0);

    //delete and close everything
    glDeleteBuffers(1, &vertexbuffer);
	glDeleteBuffers(1, &uvbuffer);
    glDeleteBuffers(1, &normalbuffer);
    glDeleteBuffers(1, &elementbuffer);
	glDeleteProgram(ProgramID);
	glDeleteTextures(1, &Texture);
	glDeleteVertexArrays(1, &VertexArrayID);

    //terminate glfw and close the window
    glfwTerminate();

    return 0;
}
void GenVao(GLuint* id)
{
    glGenVertexArrays(1, id);
    glBindVertexArray(*id);
}

int InitAll()
{
    if( !glfwInit() )
    {
        fprintf( stderr, "Error: Failed to initialize GLFW\n");
        return -1;
    }
    glfwWindowHint(GLFW_SAMPLES, 4); // 4x anti aliasing
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); //Make macos happy
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //NO old opengl


    
    window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE, NULL, NULL);

    if( window == NULL)
    {
        fprintf( stderr, "Error: Failed to open GLFW window.\n");
        glfwTerminate();
        return -1;
    }
    
    glfwMakeContextCurrent(window); //Initialize glew
    glewExperimental = true;
    
    if(glewInit() != GLEW_OK)
    {
        fprintf(stderr, "Error: Failed to initialize GLEW\n");
        return -1;
    }
    

    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

    glfwPollEvents();
    glfwSetCursorPos(window, WINDOW_WIDTH/2, WINDOW_HEIGHT/2);

    glClearColor(0.0f, 1.0f, 1.0f, 0.9f);
    //enable depth test
    glEnable(GL_DEPTH_TEST);
    //accept fragment if it is closer to the camera than the former one
    glDepthFunc(GL_LESS);
    //enable backface culing
    glEnable(GL_CULL_FACE);



    logFile = fopen("log/log.LOG", LOG_FILE_MODE);
    if(logFile == NULL)
    {
        fprintf(stderr, "Error: Failed to open LogFile.\n");
        return -1;
    }

    return 0;
}  

void loadBuffers(
    GLuint* vertexbuffer,
    GLuint* uvbuffer,
    GLuint* normalbuffer,
    GLuint* elementbuffer,
    std::vector<unsigned short> indices,
    std::vector<glm::vec3> indexed_vertices,
    std::vector<glm::vec2> indexed_uvs,
    std::vector<glm::vec3> indexed_normals)
    {
       glGenBuffers(1, uvbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, *uvbuffer);
    glBufferData(GL_ARRAY_BUFFER, indexed_uvs.size() * sizeof(glm::vec2), &indexed_uvs[0], GL_STATIC_DRAW);


    glGenBuffers(1, vertexbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, *vertexbuffer);
    glBufferData(GL_ARRAY_BUFFER, indexed_vertices.size() * sizeof(glm::vec3), &indexed_vertices[0], GL_STATIC_DRAW);
    

    glGenBuffers(1, normalbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, *normalbuffer);
    glBufferData(GL_ARRAY_BUFFER, indexed_normals.size() * sizeof(glm::vec3), &indexed_vertices[0], GL_STATIC_DRAW);



    glGenBuffers(1, elementbuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *elementbuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW); 
    }

