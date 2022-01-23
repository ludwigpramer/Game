#ifndef _CONSTS
#define _CONSTS

#include <unistd.h>
#include <sys/stat.h>
#include <stdint.h>

#include <stdio.h>
#include <vector>

#include <GL/glew.h>
#include <glm/glm.hpp>

#include "renderingHead/matrices.hpp"
#include "args.hpp"

//Define the WindowConstants
#define WINDOW_WIDTH 1024
#define WINDOW_HEIGHT 768
#define WINDOW_TITLE "TEST"

#define BACKGROUND_COLOR 0.0f, 1.0f, 1.0f, 0.9f

//define the ControllConstants
#define BASE_SPEED 3.0f
#define BOOST_SPEED 9.0f
#define MOUSE_SPEED 0.005f
#define MOUSE_BOUND 0

#define NORMAL_FOV 45
#define SCOPE_FOV 20

//define the Path contants
#define GUN_TEXTURE_PATH "assets/uvmap.DDS"
#define GUN_OBJ_PATH "assets/gun.obj"

//define the GameConstants
#define CAMERA_STARTING_POS glm::vec3(0, 0, 5)
#define PLAYER_STARTING_POS CAMERA_STARTING_POS
#define CAMERA_STARTING_DIRECTION glm::vec3(0, 0, 1)
#define PLAYER_STARTING_DIRECTION CAMERA_STARTING_DIRECTION

#define G_UP glm::vec3(0, 1, 0)
#define G_DOWN -G_UP
#define G_RIGHT glm::vec3(0, 0, 1)
#define G_LEFT -G_RIGHT
#define G_FORWARDS glm::vec3(1, 0, 0)
#define G_BACKWARDS -G_FORWARDS

#define ENEMY_STARTING_COUNT 2

#define TESTING_TEXTURE "assets/uvtemplate.bmp"


//define the logging and LoggingControll constants
#ifdef DEBUG
#define LOG_CONTROLS
#define LOG_FILE_MODE "w"
#define logFps(x) printf("%d fps\n", x)
#define logMspf(x) printf("%f ms/frame\n", 1000.0/double(x))
#define logVec3(name, l) printf("%s %f %f %f\n", name, l.x, l.y, l.z)

#else
#define LOG_CONTROLS
#define LOG_FILE_MODE "w"
#define logFps(x) printf("%d fps\n", x)
#define logMspf(x) printf("%f ms/frame\n", 1000.0/double(x))
#endif



#ifdef LOG_POSITIONS

#endif 

//The temporary color buffer data
const GLfloat g_color_buffer_data[] = {
     0.583f,  0.771f,  0.014f,
     0.609f,  0.115f,  0.436f,
     0.327f,  0.483f,  0.844f,
     0.822f,  0.569f,  0.201f,
     0.435f,  0.602f,  0.223f,
     0.310f,  0.747f,  0.185f,
     0.597f,  0.770f,  0.761f,
     0.559f,  0.436f,  0.730f,
     0.359f,  0.583f,  0.152f,
     0.483f,  0.596f,  0.789f,
     0.559f,  0.861f,  0.639f,
     0.195f,  0.548f,  0.859f,
     0.014f,  0.184f,  0.576f,
     0.771f,  0.328f,  0.970f,
     0.406f,  0.615f,  0.116f,
     0.676f,  0.977f,  0.133f,
     0.971f,  0.572f,  0.833f,
     0.140f,  0.616f,  0.489f,
     0.997f,  0.513f,  0.064f,
     0.945f,  0.719f,  0.592f,
     0.543f,  0.021f,  0.978f,
     0.279f,  0.317f,  0.505f,
     0.167f,  0.620f,  0.077f,
     0.347f,  0.857f,  0.137f,
     0.055f,  0.953f,  0.042f,
     0.714f,  0.505f,  0.345f,
     0.783f,  0.290f,  0.734f,
     0.722f,  0.645f,  0.174f,
     0.302f,  0.455f,  0.848f,
     0.225f,  0.587f,  0.040f,
     0.517f,  0.713f,  0.338f,
     0.053f,  0.959f,  0.120f,
     0.393f,  0.621f,  0.362f,
     0.673f,  0.211f,  0.457f,
     0.820f,  0.883f,  0.371f,
     0.982f,  0.099f,  0.879f
};


#endif