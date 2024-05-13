#include "global_stuff.h"
#include "system.h"

int main()
{
    System *game = new System(WIDTH, HEIGHT);
    game->run();
    delete game;
    return 0;
}
