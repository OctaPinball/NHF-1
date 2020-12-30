#include "common.h"
#include "debugmalloc.h"


//Játékos mozgatása
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

//Játékos újraélesztése
void respawn(Controls *input, WaveControl *wavecontrol, Creature *player, Timers *timers, SDL_Renderer *renderer){
    if (player->alive == false && wavecontrol->inrespawn == false)
    {
        player->render.texture = loadTexture("resources/ship_dead.png", renderer);
        wavecontrol->life--;
        if (wavecontrol->life != 0)
            wavecontrol->inrespawn = true;
        else
            input->quit = true;
    }
    if (player->alive == true &&wavecontrol->inrespawn == true)
    {
        player->render.texture = loadTexture("resources/ship.png", renderer);
        wavecontrol->inrespawn = false;
    }
}
