#include "line.hpp"

const char*lineVertexShaderSource = "#version 330 core\n"
            "layout (location = 0) in vec3 aPos;\n"
            "uniform mat4 MVP;\n"
            "void main()\n"
            "{\n"
            "   gl_Position = MVP * vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
            "}\0";
const char *lineFragShaderSource = "#version 330 core\n"
            "out vec4 FragColor;\n"
            "uniform vec3 color;\n"
            "void main()\n"
            "{\n"
            "   FragColor = vec4(color, 1.0f);\n"
            "}\n\0";


Line::Line(glm::vec3 start, glm::vec3 end)
{
     startPoint = start;
     endPoint = end;
     MVP = glm::mat4(1.0f);
     lineColor = glm::vec3(200, 0, 0);

     GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
     glShaderSource(vertexShader, 1, &lineVertexShaderSource, NULL);
     glCompileShader(vertexShader);

     GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
     glShaderSource(fragmentShader, 1, &lineFragShaderSource, NULL);
     glCompileShader(fragmentShader);


     shaderProgram = glCreateProgram();
     glAttachShader(shaderProgram, vertexShader);
     glAttachShader(shaderProgram, fragmentShader);
     glLinkProgram(shaderProgram);


     glDeleteShader(vertexShader);
     glDeleteShader(fragmentShader);
     vertices = {
          start.x, start.y, start.z,
          end.x, end.y, end.z,
     };
        
     glGenVertexArrays(1, &VAO);
     glGenBuffers(1, &VBO);
     glBindVertexArray(VAO);
     glBindBuffer(GL_ARRAY_BUFFER, VBO);
     glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices.data(), GL_STATIC_DRAW);
     glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
     glEnableVertexAttribArray(0);
     glBindBuffer(GL_ARRAY_BUFFER, 0); 
     glBindVertexArray(0); 
}
Line::~Line() 
{
     glDeleteVertexArrays(1, &VAO);
     glDeleteBuffers(1, &VBO);
     glDeleteProgram(shaderProgram);
}

void Line::setColor(glm::vec3 color)
{
     this->lineColor = color;
}

void Line::setMVP(glm::mat4 MVP)
{
     this->MVP = MVP;
}