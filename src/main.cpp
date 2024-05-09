#include "global_stuff.h"
#include "system.h"
#include "setting.h"

int main()
{
    set_setting();
    System *game = new System(WIDTH, HEIGHT);
    game->run();
    //delete game();
    return 0;
}
