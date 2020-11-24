#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include "struct.h"
#include <stdbool.h>
#include "projectile.h"
#include "enemy.h"

#include "debugmalloc.h"

void checkEvents(WaveControl *wavecontrol, Controls *input, MoveNumbers *enemymoves, Creature **enemy, ProjectileArray *projectileArray, Creature *player){
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
            refreshProjectile(&(*projectileArray));
            combinedProjectileDetection(&(*wavecontrol), &(*player), &(*&(*enemy)), &(*projectileArray));
            //detectProjectileHit(&(*player), &(*enemy), &(*projectileArray));
            //autodestroyProjectile(&(*projectileArray), 0);
            //printf("tikk");
            break;
        case (SDL_USEREVENT+1):
            //printf("tikk");
            moveEnemy(&(*enemymoves), &(*&(*enemy)));
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