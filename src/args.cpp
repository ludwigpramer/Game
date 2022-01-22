#include "args.hpp"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "constants.hpp"

//Flags
int miscFlag = 0;
int miscInt = 0;
int windowStartFullscreen;

void parseArgs(int argc, const char** argv)
{
     for(int i = 1; i < argc; ++i)
     {
          if(strstr(argv[i], "-m") != NULL)
          {
               miscFlag = 1;
          }
          else if(strstr(argv[i], "-i") != NULL)
          {
               if(argc-1 > i)
               {
                    miscInt = atoi(argv[++i]);
               }else
               {
                    fprintf(stderr, "Error: Not enough arguments for -i flag provided!\n");
                    exit(-1);
               }
          }
          else if(strstr(argv[i], "-w") != NULL)
          {
              windowStartFullscreen = 1;
          }
     }
}