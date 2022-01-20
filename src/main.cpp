#include "game/game.hpp"
#include "constants.hpp"
#include "args.hpp"


extern int miscFlag;
extern int miscInt;

int main(int argc, const char** argv)
{    
     parseArgs(argc, argv);
     printf("MiscInt: %d\n", miscInt);
     int errorStatus = Game();
     return errorStatus;
}