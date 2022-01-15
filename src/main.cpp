#include "game/game.hpp"


const char** args;


int main(int argc, const char** argv)
{    
     (void) argc;
     args = argv;
     int errorStatus = Game();
     return errorStatus;
}