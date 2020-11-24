#ifndef ENEMY_H_INCLUDED
#define ENEMY_H_INCLUDED

void spawnWave(Creature **enemy, SDL_Renderer *renderer);
void moveEnemy(MoveNumbers *enemymove, Creature **enemy);

#endif // ENEMY_H_INCLUDED
