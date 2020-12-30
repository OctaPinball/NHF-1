#include "common.h"
#include "debugmalloc.h"

//SDL eventek vizsgalata
void checkEvents(WaveControl *wavecontrol, Controls *input, Enemies *enemy, ProjectileList **projectilelist, Creature *player){
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_KEYUP:
            switch (event.key.keysym.sym)
            {
            case SDLK_LEFT:
                input->left = false;
                break;
            case SDLK_RIGHT:
                input->right = false;
                break;
            case SDLK_SPACE:
                input->space = false;
                break;
            case SDLK_ESCAPE:
                input->quit = true;
                break;
            }
            break;
        case SDL_KEYDOWN:
            switch (event.key.keysym.sym)
            {
            case SDLK_LEFT:
                input->left = true;
                break;
            case SDLK_RIGHT:
                input->right = true;
                break;
            case SDLK_e:
                input->autofire *= -1;
                break;
            case SDLK_SPACE:
                input->space = true;
                break;
            }
            break;
        case SDL_QUIT:
            input->quit = true;
            break;
        case SDL_USEREVENT:
            refreshProjectile(*projectilelist);
            combinedProjectileDetection(projectilelist, enemy, wavecontrol, player);
            break;
        case (SDL_USEREVENT+1):
            moveEnemy(&(*input), &(*enemy));
            break;
        case (SDL_USEREVENT+2):
            wavecontrol->fireready = true;
            wavecontrol->firetime = 0;
            break;
        case (SDL_USEREVENT+3):
            wavecontrol->enemyfireready = true;
            break;
        case (SDL_USEREVENT+4):
            player->alive = true;
            break;

        }
    }
}
