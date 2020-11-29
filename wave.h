#ifndef WAVE_H_INCLUDED
#define WAVE_H_INCLUDED

void resetWave(Timers *timers, Enemies *enemy, WaveControl *wavecontrol, ProjectileArray *projectileArray, SDL_Renderer *renderer);
void checkWave(Timers *timers, Enemies *enemy, WaveControl *wavecontrol, ProjectileArray *projectileArray, SDL_Renderer *renderer);

#endif // WAVE_H_INCLUDED
