#ifndef PROJECTILE_H_INCLUDED
#define PROJECTILE_H_INCLUDED

void deleteProjectile(ProjectileArray *projectileArray, int idx);
void autodestroyProjectile(ProjectileArray *projectileArray, int i);
void detectProjectileHit(Creature *player, Creature **enemy, ProjectileArray *projectileArray);
void combinedProjectileDetection(WaveControl *wavecontrol, Creature *player, Creature **enemy, ProjectileArray *projectileArray);
void createProjectile(Creature creature, ProjectileArray *projectileArray, SDL_Renderer *renderer);
void fire(WaveControl *wavecontrol, Controls *input, Creature player, ProjectileArray *projectileArray, SDL_Renderer *renderer);
void refreshProjectile(ProjectileArray *projectileArray);
bool detectProjectilePath(Creature *enemy, int i);
void enemyfire(WaveControl *wavecontrol, Creature **enemy, ProjectileArray *projectileArray, SDL_Renderer *renderer);

#endif // PROJECTILE_H_INCLUDED
