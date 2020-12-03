#ifndef PROJECTILE_H_INCLUDED
#define PROJECTILE_H_INCLUDED

void freeProjectile(ProjectileList *first);
void deleteProjectile(ProjectileList *first, ProjectileList *backseeker, ProjectileList *seeker);
void autodestroyProjectile(ProjectileList *first);
void enemyhitDetection(ProjectileList *first, Enemies *enemy, WaveControl *wavecontrol);
void projectilecollisionDetection(ProjectileList *first);
void combinedProjectileDetection(ProjectileList *first, Enemies *enemy, WaveControl *wavecontrol);
void createProjectile(Creature creature, ProjectileList *first, SDL_Renderer *renderer);
void fire(WaveControl *wavecontrol, Controls *input, Creature player, ProjectileList *projectilelist, SDL_Renderer *renderer);
void refreshProjectile(ProjectileList *first);
bool detectProjectilePath(Creature *enemy, int i);
void enemyfire(WaveControl *wavecontrol, Enemies *enemy, ProjectileList *projectilelist, SDL_Renderer *renderer);

#endif // PROJECTILE_H_INCLUDED
