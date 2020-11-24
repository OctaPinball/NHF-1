#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include "struct.h"
#include <stdbool.h>
#include "time.h"
#include "render.h"

#include "debugmalloc.h"


void movePlayer(Controls input, Creature *player){
        if (input.left && player->render.x > 0)
        {
            player->render.x -= 32;
        }
        if (input.right && player->render.x < 1216)
        {
            player->render.x += 32;
        }
}


void respawn(WaveControl *wavecontrol, Creature *player, Timers *timers, SDL_Renderer *renderer){
    if (player->alive == false && timers->respawntimermemory == 0)
    {
        player->render.texture = loadTexture("resources/ship_dead.png", renderer);
        wavecontrol->life--;
        if (wavecontrol->life != 0)
            timers->respawntimernewvalue = 3000;
    }
    if (player->alive == true && timers->respawntimermemory != 0)
    {
        player->render.texture = loadTexture("resources/ship.png", renderer);
        timers->respawntimernewvalue = 0;
    }
}
