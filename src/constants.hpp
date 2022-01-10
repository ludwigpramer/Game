#ifndef _CONSTS
#define _CONSTS

#include <unistd.h>
#include <sys/stat.h>
#include <stdint.h>


//Define the WindowConstants
#define WINDOW_WIDTH 1024
#define WINDOW_HEIGHT 768
#define WINDOW_TITLE "TEST"

//define the ControllConstants
#define BASE_SPEED 3.0f
#define BOOST_SPEED 9.0f
#define MOUSE_SPEED 0.005f
#define MOUSE_BOUND 0


//define the logging and LoggingControll constants
#define LOG_CONTROLS
#define LOG_FILE_MODE "w"
#define logFps(x) printf("%d fps\n", x)
#define logMspf(x) printf("%f ms/frame\n", 1000.0/double(x))


#endif