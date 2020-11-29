#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

void initiatevariables(ProjectileArray *projectileArray, Creature *player, Enemies *enemystruct, Timers *timers, SDL_Renderer *renderer);
void game(State *state);

#endif // GAME_H_INCLUDED
