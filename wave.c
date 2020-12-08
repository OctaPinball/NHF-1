#include "common.h"

//Wave alapállapotbahelyezés, változók reset
void resetWave(Timers *timers, Enemies *enemy, WaveControl *wavecontrol, ProjectileList **first, SDL_Renderer *renderer)
{
    wavecontrol->wave++;
    for (ProjectileList *seeker = *first; seeker != NULL; seeker = seeker->next)
        SDL_DestroyTexture(seeker->data.render.texture);
    freeProjectile(*first);
    *first = NULL;
    spawnWave(enemy, renderer);
    enemy->movenumbers.movexdirection = 1;
    enemy->movenumbers.movexcount = 0;
    enemy->movenumbers.moveline = 0;
    timers->enemyfiretimernewvalue *= 0.9;
    timers->movetimernewvalue *= 0.9;
    timers->refreshWaveTimers = true;
}

//Újra kell-e indítani wave-et?
void checkWave(Timers *timers, Enemies *enemy, WaveControl *wavecontrol, ProjectileList **projectilelist, SDL_Renderer *renderer)
{
    if (!enemyalive(enemy, 0 , 30))
        resetWave(timers, enemy, wavecontrol, projectilelist, renderer);
}

