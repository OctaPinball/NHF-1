#ifndef WAVE_H_INCLUDED
#define WAVE_H_INCLUDED

void resetWave(Timers *timers, MoveNumbers *movenumbers, WaveControl *wavecontrol, Creature **enemy, ProjectileArray *projectileArray, SDL_Renderer *renderer);
void checkWave(Timers *timers, MoveNumbers *movenumbers, WaveControl *wavecontrol, Creature **enemy, ProjectileArray *projectileArray, SDL_Renderer *renderer);

#endif // WAVE_H_INCLUDED
