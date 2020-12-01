#include "common.h"


int main(int argc, char *argv[])
{
    State state = inmenu;
    bool exit = false;
    while(!exit)
    {
        switch (state)
        {
        case inmenu:
            menu(&state);
            break;
        case ingame:
            game(&state);
            break;
        case inleaderboard:
            showleaderboard(&state);
            break;
        case exitprogram:
            exit = true;
            break;
        }
    }
    return 0;
}
