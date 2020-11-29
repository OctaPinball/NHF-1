#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

void movePlayer(Controls input, Creature *player);
void respawn(Controls *input, WaveControl *wavecontrol, Creature *player, Timers *timers, SDL_Renderer *renderer);

#endif // PLAYER_H_INCLUDED
