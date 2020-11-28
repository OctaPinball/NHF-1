#include "common.h"


int main(int argc, char *argv[])
{
    State state = inmenu;
    while(state != exitprogram)
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
        }
    }
    return 0;
}
