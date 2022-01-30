#include "line.hpp"

Line::Line()
{
     //The default contructor.
}
Line::Line(glm::vec3 start, glm::vec3 end)
{
     this->start = start;
     this->end = end;
}
Line::~Line()
{

}