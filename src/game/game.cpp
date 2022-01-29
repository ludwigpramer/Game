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

#ifndef __WIN32
#include <sys/stat.h>
#include <unistd.h>
#else
#include <windows.h>
#endif




#include "game.hpp"

#include "../constants.hpp"


#include "../renderingHead/vboindexing.hpp"

#include "../renderingHead/shader.hpp"
#include "../renderingHead/texture.hpp"
#include "../renderingHead/objloader.hpp"

#include "../renderingHead/line.hpp"

#include "head/controls.hpp"
#include "head/model.hpp"
#include "head/scene.hpp"
#include "head/collider/collider.hpp"
#include "head/gun/gun.hpp"


#define LOG

#ifdef DEBUG
#define lg printf("Log Point %d\n", i); i++
int i = 0;
#else
#define lg
#endif


//the extern flags

extern int windowStartFullscreen;

//the globally used variables
GLFWwindow* window; //The windowobject

FILE* logFile; //The log file

int error = 0; // the error codes

const GLFWvidmode* mode;

int windowFullScreen;

GLFWmonitor* primaryMonitor;

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
    
void renderScene(Scene* scene);
int render(Model* model, glm::mat4 ProjectionMatrix, glm::mat4 ViewMatrix);

static GLuint vertexbuffer;
static GLuint uvbuffer;
static GLuint normalbuffer;
static GLuint elementbuffer;

static GLuint VertexArrayID;
static GLuint TextureID;
static GLuint LightID;

static GLuint MatrixID;
static GLuint ViewMatrixID;
static GLuint ModelMatrixID;



int Game(void)
{
    //Print debugging info
    char cwd[PATH_MAX];
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        printf("Current working dir: %s\n", cwd);
    }
    else 
    {
        perror("getcwd() error");
        exit(1);
    }
    GLuint program;


    error = InitAll();

    if(error != 0)
    {
        return error;
    }
    
    //Generate Vao
    GenVao(&VertexArrayID);
    
    program = LoadShaders("src/renderingHead/Shaders/ShadingVertexShader.vs", "src/renderingHead/Shaders/ShadingFragmentShader.fs");
    

    // Get a handle for  "MVP" uniform
	MatrixID = glGetUniformLocation(program, "MVP");
    ViewMatrixID = glGetUniformLocation(program, "V");
    ModelMatrixID = glGetUniformLocation(program, "M");


    printf("Before Texture loading\n");
    Player player;
    printf("Between Player and Scene creation\n");
    Scene scene = Scene(player);
    printf("After scene loading\n");
    //Make model
    Model monkey(TESTING_TEXTURE, "assets/suzanne.obj");
    printf("After Model creation\n");
    monkey.ModelMatrix = glm::translate(IDENTITY_MATRIX, glm::vec3(10.0f, 0.0f, 0.0f)) * getRotationMatrix(170, 0, 0);
    scene.add(monkey);

    printf("Before Enemy creation\n");
    //Test enemy
    Enemy enemy;
    enemy.setPos(glm::vec3(5.0f, 0.0f, 0.0f));  
    scene.add(enemy);


    

    // Get a handle for  "myTextureSampler" uniform
	TextureID  = glGetUniformLocation(program, "myTextureSampler");
    
 

    //Will later be removed
    GLuint colorbuffer;  
    glGenBuffers(1, &colorbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_color_buffer_data), g_color_buffer_data, GL_STATIC_DRAW);

    LightID = glGetUniformLocation(program, "LightPosition_worldspace");
    
    //printf("PlayerPos:%f %f %f MonkeyPos:%f %f %f ObjPos: %f %f %f \n", scene.player.position.x, scene.player.position.y, scene.player.position.z, monkey.position.x, monkey.position.y, monkey.position.z, 0.0f, 0.0f, 0.0f);
    double lastTime;
    int frames;
    lastTime = glfwGetTime();
    frames = 0;
    glfwSetTime(0.0f);
    do
    {
    //log the fps
        double currentTime;
        currentTime = glfwGetTime();
        frames++;
        if(currentTime - lastTime >= 1.0f)
        {
            logFps(frames);
            frames = 0;
            lastTime += 1.0f;
            //printf("PlayerPos:%f %f %f GunPos:%f %f %f ObjPos: %f %f %f \n", scene.player.position.x, scene.player.position.y, scene.player.position.z, monkey.position.x, monkey.position.y, monkey.position.z, 0.0f, 0.0f, 0.0f);
          
        }
        //clear the displaye
        glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
	    //Use the shaders
        glUseProgram(program);
        
        glm::vec3 lightPos = glm::vec3(4, 4, 4);
        glUniform3f(LightID, lightPos.x, lightPos.y, lightPos.y);

       
        
        
        //render(monkey, ProjectionMatrix, ViewMatrix);
        scene.update(&windowFullScreen);
        renderScene(&scene);
        if(error != 0)
        {
            fprintf(stderr, "Error: Failed in the rendering Method: ErrorCode %d\n", error);
        }

        //Update Display
        glfwSwapBuffers(window);
        glfwPollEvents();

        if(error != 0)
        {
            fprintf(stderr, "Error: Detected at the end of the loop!\n");
            return -1;
        }
    } while(glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(window) == 0);

    //delete and close everything
    glDeleteBuffers(1, &vertexbuffer);
	glDeleteBuffers(1, &uvbuffer);
    glDeleteBuffers(1, &normalbuffer);
    glDeleteBuffers(1, &elementbuffer);
	glDeleteProgram(program);
	glDeleteVertexArrays(1, &VertexArrayID);

    //terminate glfw and close the window
    glfwTerminate();

    return 0;
}
inline void GenVao(GLuint* id)
{
    glGenVertexArrays(1, id);
    glBindVertexArray(*id);
}

inline int InitAll()
{
    if(!glfwInit() )
    {
        fprintf( stderr, "Error: Failed to initialize GLFW\n");
        return -1;
    }

    windowFullScreen = windowStartFullscreen;

    primaryMonitor = glfwGetPrimaryMonitor();
    
    mode = glfwGetVideoMode(primaryMonitor);

    glfwWindowHint(GLFW_SAMPLES, 4); // 4x anti aliasing
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); //Make macos happy
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //NO old opengl

    glfwWindowHint(GLFW_RED_BITS, mode->redBits);
    glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
    glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
    glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);




    
    window = windowFullScreen ? glfwCreateWindow(mode->width, mode->height, "My Title", primaryMonitor, NULL) : glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE,  NULL, NULL);

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

    glClearColor(BACKGROUND_COLOR);
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

inline int render(Model* model, glm::mat4 ProjectionMatrix, glm::mat4 ViewMatrix)
{
    loadBuffers(
    &vertexbuffer,
    &uvbuffer,
    &normalbuffer,
    &elementbuffer,
    model->indices,
    model->indexed_vertices,
    model->indexed_uvs,
    model->indexed_normals);

    ////render////
	   
    glm::mat4 MVP = ProjectionMatrix * ViewMatrix * model->ModelMatrix;


    glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);

    glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &model->ModelMatrix[0][0]);

    // Bind texture in Texture Unit 0
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, *model->Texture);
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
    glDrawElements( GL_TRIANGLES, (GLsizei) model->indices.size(), GL_UNSIGNED_SHORT, (void*)0);
    //diable the buffers
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(2);
    return 0;
}

inline void renderScene(Scene* scene)
{
    glUniformMatrix4fv(ViewMatrixID, 1, GL_FALSE, &scene->player.camera.ViewMatrix[0][0]);

    for(Model m : scene->contents)
    {
        error = render(&m, scene->player.camera.ProjectionMatrix, scene->player.camera.ViewMatrix);
    }

    for(Enemy e : scene->enemies)
    {
        error = render(&e.model, scene->player.camera.ProjectionMatrix, scene->player.camera.ViewMatrix);
    }
    //error = render(scene->player.gun.model, scene->player.camera.ProjectionMatrix, scene->player.camera.ViewMatrix);
}

inline void renderLine(Line* line)
{
    glUseProgram(line->shaderProgram);
    glUniformMatrix4fv(glGetUniformLocation(line->shaderProgram, "MVP"), 1, GL_FALSE, &line->MVP[0][0]);
    glUniform3fv(glGetUniformLocation(line->shaderProgram, "color"), 1, &line->lineColor[0]);

    glBindVertexArray(line->VAO);
    glDrawArrays(GL_LINES, 0, 2);
}
