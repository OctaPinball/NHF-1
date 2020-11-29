#ifndef ENEMY_H_INCLUDED
#define ENEMY_H_INCLUDED

void spawnWave(Enemies *enemy, SDL_Renderer *renderer);
bool enemyalive(Enemies *enemy, int i, int j);
void moveEnemy(Controls *input, Enemies *enemy);

#endif // ENEMY_H_INCLUDED
