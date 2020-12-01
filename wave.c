#include "common.h"

//Wave alapállapotbahelyezés, változók reset
void resetWave(Timers *timers, Enemies *enemy, WaveControl *wavecontrol, ProjectileArray *projectileArray, SDL_Renderer *renderer)
{
    wavecontrol->wave++;
    for(int i = 0; i < projectileArray->scale; i++)
        SDL_DestroyTexture(projectileArray->data[i].render.texture);
    free(projectileArray->data);
    projectileArray->data = (Projectile*) malloc(0 * sizeof(Projectile));
    projectileArray->scale = 0;
    spawnWave(enemy, renderer);
    enemy->movenumbers.movexdirection = 1;
    enemy->movenumbers.movexcount = 0;
    enemy->movenumbers.moveline = 0;
    timers->enemyfiretimernewvalue *= 0.9;
    timers->movetimernewvalue *= 0.9;
    timers->refreshWaveTimers = true;
}

//Újra kell-e indítani wave-et?
void checkWave(Timers *timers, Enemies *enemy, WaveControl *wavecontrol, ProjectileArray *projectileArray, SDL_Renderer *renderer)
{
    if (!enemyalive(enemy, 0 , 30))
        resetWave(timers, enemy, wavecontrol, projectileArray, renderer);
}

