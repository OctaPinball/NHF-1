#ifndef PROJECTILE_H_INCLUDED
#define PROJECTILE_H_INCLUDED

void freeProjectile(ProjectileList *first);
void deleteProjectile2(ProjectileList **first, ProjectileList *backseeker, ProjectileList *seeker);
ProjectileList *deleteProjectile(ProjectileList *first, ProjectileList *backseeker, ProjectileList *seeker);
void autodestroyProjectile(ProjectileList **first);
void enemyhitDetection(ProjectileList **first, Enemies *enemy, WaveControl *wavecontrol);
void projectilecollisionDetection(ProjectileList **first);
void playerhitDetection(ProjectileList **first, Creature *player);
void combinedProjectileDetection2(ProjectileList **first, Enemies *enemy, WaveControl *wavecontrol, Creature *player);
void doubledeleteProjectile(ProjectileList **first, ProjectileList *seeker, ProjectileList *backseeker, ProjectileList *seeker_2, ProjectileList *backseeker_2);
void combinedProjectileDetection(ProjectileList **first, Enemies *enemy, WaveControl *wavecontrol, Creature *player);
void createProjectile(Creature creature, ProjectileList **first, SDL_Renderer *renderer);
void fire(WaveControl *wavecontrol, Controls *input, Creature player, ProjectileList **projectilelist, SDL_Renderer *renderer);
void refreshProjectile(ProjectileList *first);
bool detectProjectilePath(Creature *enemy, int i);
void enemyfire(WaveControl *wavecontrol, Enemies *enemy, ProjectileList **projectilelist, SDL_Renderer *renderer);

#endif // PROJECTILE_H_INCLUDED
