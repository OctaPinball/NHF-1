#include "common.h"

void resetWave(Timers *timers, MoveNumbers *movenumbers, WaveControl *wavecontrol, Creature **enemy, ProjectileArray *projectileArray, SDL_Renderer *renderer)
{
    wavecontrol->wave++;
    for(int i = 0; i < projectileArray->scale; i++)
        SDL_DestroyTexture(projectileArray->data[i].render.texture);
    free(projectileArray->data);
    projectileArray->data = (Projectile*) malloc(0 * sizeof(Projectile));
    projectileArray->scale = 0;
    spawnWave(enemy, renderer);
    movenumbers->movexdirection = 1;
    movenumbers->movexcount = 0;
    timers->enemyfiretimernewvalue *= 0.9;
    timers->movetimernewvalue *= 0.9;
    timers->refreshWaveTimers = true;
}

void checkWave(Timers *timers, MoveNumbers *movenumbers, WaveControl *wavecontrol, Creature **enemy, ProjectileArray *projectileArray, SDL_Renderer *renderer)
{
    for(int i = 0; i < 30; i++)
        if((*enemy)[i].alive == true)
        return;
    resetWave(timers, movenumbers, wavecontrol, enemy, projectileArray, renderer);
}

