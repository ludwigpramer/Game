#include "controls.hpp"

extern GLFWwindow* window;
extern FILE* logFile;
extern int error;
extern GLFWmonitor* primaryMonitor;
extern const GLFWvidmode* mode;


Controller::Controller()
{

}

Controller::~Controller()
{

}


void Controller::update(int* windowFullscreen)
{
     double currentTime= glfwGetTime();
     float deltaTime = float(currentTime - lastTime);
     lastTime = currentTime;
     //the field of view
     float FoV = NORMAL_FOV;

     double xpos, ypos;
     if(mouseBound)
     {
     glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
	glfwGetCursorPos(window, &xpos, &ypos);
	//Compute orientation
	horizontalAngle += mouseSpeed * float(WINDOW_WIDTH/2 - xpos );
	verticalAngle   += mouseSpeed * float(WINDOW_HEIGHT/2 - ypos );

     //reset
	glfwSetCursorPos(window, WINDOW_WIDTH/2, WINDOW_HEIGHT/2);

     //printf("%d\n", horizontalAngle);
     }
     else
     {
          glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
     }
     //direction vector
	direction = glm::vec3(
		cos(verticalAngle) * sin(horizontalAngle), 
		sin(verticalAngle),
		cos(verticalAngle) * cos(horizontalAngle)
	);
     

     //right vector
     glm::vec3 right = glm::vec3(
          sin(horizontalAngle - 3.14f/2.0f),
          0,
          cos(horizontalAngle - 3.14f/2.0f)
     );

     up = glm::cross(right, direction);
     //move forwards
     if (glfwGetKey(window, GLFW_KEY_W ) == GLFW_PRESS && !cameraBound)
     {
          position += normalize(glm::vec3(direction.x, 0.0f, direction.z)) * deltaTime * speed;
     }
     //move backwards
     if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS && !cameraBound)
     {
          position -= normalize(glm::vec3(direction.x, 0.0f, direction.z)) * deltaTime * speed;
     }
     //move right
     if (glfwGetKey(window, GLFW_KEY_D ) == GLFW_PRESS && !cameraBound)
     {
          position += normalize(right) * deltaTime * speed;
     }
     //move left
     if (glfwGetKey(window, GLFW_KEY_A ) == GLFW_PRESS && !cameraBound)
     {
          position -= normalize(right) * deltaTime * speed;
     }
     if(glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS && !cameraBound)
     {
          position.y -= deltaTime * speed;
     }
     //move up
     if(glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS && !cameraBound)
     {
          position.y += deltaTime * speed;
     }
     //speed
     if(glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
     {
          speed = BOOST_SPEED;
     } else
     {
          speed = BASE_SPEED;
     }
     //unbind mouse
     if(glfwGetKey(window, GLFW_KEY_ENTER) == GLFW_PRESS && mouseBound)
     {
          mouseBound = 0;
     }
     //bind mouse
     if(glfwGetKey(window, GLFW_KEY_BACKSPACE) == GLFW_PRESS && !mouseBound)
     {
          mouseBound = 1;
          glfwSetCursorPos(window, WINDOW_WIDTH/2, WINDOW_HEIGHT/2);
     }
     //shoot
     if(glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_1)  == GLFW_PRESS)
     {
          printf("Shoot!!!\n");
     }
     if(glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_2) == GLFW_PRESS)
     {

          FoV = SCOPE_FOV;
          
     } else
     {

          FoV = NORMAL_FOV;
     }
     if(glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS)
     {

          cameraBound = 0;
     }
     if(glfwGetKey(window, GLFW_KEY_B) == GLFW_PRESS)
     {

          cameraBound = 1;
     }
     if(glfwGetKey(window, GLFW_KEY_9) == GLFW_PRESS)
     {
          printf("ScreenSizeFunc\n");
          if(!*windowFullscreen)
          {
               glfwSetWindowMonitor(window, primaryMonitor, 0, 0, mode->width, mode->height, mode->refreshRate);
               glfwSetCursorPos(window, mode->width/2, mode->height/2);
               *windowFullscreen = 1;
               printf("Fullscreen\n");
          }
     }
     if(glfwGetKey(window, GLFW_KEY_8) == GLFW_PRESS)
     {
          if(*windowFullscreen)
          {
               glfwSetWindowMonitor(window, NULL, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, GLFW_DONT_CARE);
               glfwSetCursorPos(window, WINDOW_WIDTH/2, WINDOW_HEIGHT/2);
               *windowFullscreen = 0;
               printf("UNFullscreen\n");
          }
     }
  


     #ifdef LOGCONTROLS
     printf(
          "%s %f %f %f %s %f %f %f %s %f %f %s %s %f %s %f \n",
          "UP: ", up.x, up.y, up.z,
          "DIRECTION: ", direction.x, direction.y, direction.z,
          "cos", cos(verticalAngle), cos(horizontalAngle), 
          "Angles", "vertical angle", verticalAngle, "horizontal angle", horizontalAngle
     );
     fprintf(
          logFile,
          "%s %f %f %f %s %f %f %f %s %f %f %s %s %f %s %f \n",
          "UP: ", up.x, up.y, up.z,
          "DIRECTION: ", direction.x, direction.y, direction.z,
          "cos", cos(verticalAngle), cos(horizontalAngle), 
          "Angles", "vertical angle", verticalAngle, "horizontal angle", horizontalAngle
     );

     if(up.y < 0)
     {
          printf("Upside Down!\n");
     }
     #endif
     //Projection Matrix
     ProjectionMatrix = glm::perspective(glm::radians(FoV), 4.0f / 3.0f, 0.1f, 100.0f);

     //View Matrix for Camera
     ViewMatrix = glm::lookAt(
          position, //Camera position
          position + direction, // Looks at position plus direction
          up // Where up is
     );

}

glm::mat4 Controller::getProjectionMatrix()
{
     return ProjectionMatrix;
}

glm::mat4 Controller::getViewMatrix()
{
     return ViewMatrix;
}
glm::vec3 Controller::getPositionVector()
{
     return position;
}
glm::vec3 Controller::getDirectionVector()
{
     return direction;
}
glm::vec3 Controller::getUpVector()
{
     return up;
}