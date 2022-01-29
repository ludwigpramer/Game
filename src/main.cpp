
#ifndef _LUDWIGPRAMER_
#error "Compile as LUDWIGPRAMER"
#endif

#include "game/game.hpp"
#include "constants.hpp"
#include "args.hpp"

#ifndef __WIN32

extern int miscFlag;
extern int miscInt;

int main(int argc, const char** argv)
{    
     parseArgs(argc, argv);
     printf("MiscInt: %d\n", miscInt);
     int errorStatus = Game();
     return errorStatus;
}
#else
extern int miscFlag;
extern int miscInt;

int main(int argc, const char** argv)
{    
     parseArgs(argc, argv);
     printf("MiscInt: %d\n", miscInt);
     int errorStatus = Game();
     return errorStatus;
}
#endif
