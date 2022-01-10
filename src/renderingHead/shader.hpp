#ifndef _SHADER_HPP
#define _SHADER_HPP

#include <stdio.h>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <sstream>

#ifdef DEBUG
#include <unistd.h>
#include <stdio.h>
#include <limits.h>
#endif

#include <stdlib.h>
#include <string.h>

#include <GL/glew.h>

#include "../constants.hpp"


GLuint LoadShaders(const char * vertex_file_path,const char * fragment_file_path);

#endif
