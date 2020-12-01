#ifndef PROJECTILE_H_INCLUDED
#define PROJECTILE_H_INCLUDED

void deleteProjectile(ProjectileArray *projectileArray, int idx);
void combinedProjectileDetection(WaveControl *wavecontrol, Creature *player, Enemies *enemy, ProjectileArray *projectileArray);
void createProjectile(Creature creature, ProjectileArray *projectileArray, SDL_Renderer *renderer);
void fire(WaveControl *wavecontrol, Controls *input, Creature player, ProjectileArray *projectileArray, SDL_Renderer *renderer);
void refreshProjectile(ProjectileArray *projectileArray);
bool detectProjectilePath(Creature *enemy, int i);
void enemyfire(WaveControl *wavecontrol, Enemies *enemy, ProjectileArray *projectileArray, SDL_Renderer *renderer);

#endif // PROJECTILE_H_INCLUDED
