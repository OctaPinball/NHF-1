#include "common.h"
#include "debugmalloc.h"

//Lovedek lista felszabaditasa
void freeProjectile(ProjectileList *first)
{
    ProjectileList *seeker = first;
    while (seeker != NULL)
    {
        SDL_DestroyTexture(seeker->data.render.texture);
        ProjectileList *next_ptr = seeker->next;
        free(seeker);
        seeker = next_ptr;
    }
}

//Egy lovedek torlese
void deleteProjectile(ProjectileList **first, ProjectileList *backseeker, ProjectileList *seeker)
{
    SDL_DestroyTexture(seeker->data.render.texture);
    if (seeker == NULL)             /* nincs ilyen elem */
    {
        /* nincs teendő */
    }
    else if (backseeker == NULL)     /* az első elemet kell törölni */
    {
        ProjectileList *ujeleje = seeker->next;
        free(seeker);
        *first = ujeleje;
    }
    else                           /* a közepéről/végéről törlünk */
    {
        backseeker->next = seeker->next;
        free(seeker);
    }
}

//Ket lovedek torlese (kulonleges eset)
void doubledeleteProjectile(ProjectileList **first, ProjectileList *seeker, ProjectileList *backseeker, ProjectileList *seeker_2, ProjectileList *backseeker_2)
{
    if (seeker == backseeker_2)
    {
        deleteProjectile(first, backseeker_2, seeker_2);
        deleteProjectile(first, backseeker, seeker);
    }
    else
    {
        deleteProjectile(first, backseeker, seeker);
        deleteProjectile(first, backseeker_2, seeker_2);
    }
}

//Automatikus lovedektorles: amikor a lovedek elhagyja a jatekteret
void autodestroyProjectile(ProjectileList **first)
{
    ProjectileList *backseeker = NULL;
    for (ProjectileList *seeker = *first; seeker != NULL; seeker = seeker->next)
    {
        if (seeker->data.render.y < -10 || seeker->data.render.y > 720)
        {
            deleteProjectile(first, backseeker, seeker);
            break;
        }
        backseeker = seeker;
    }
}

//Ellenfel eltalalasanak erzekelese
void enemyhitDetection(ProjectileList **first, Enemies *enemy, WaveControl *wavecontrol)
{
    ProjectileList *seeker;
    ProjectileList *backseeker = NULL;
    for (seeker = *first; seeker != NULL; seeker = seeker->next)
    {
        if (seeker->data.type == ship)
        {
            for (int j = 0; j < 30; j++)
                if (sqrt(pow((double)(seeker->data.render.x - enemy->enemy[j].render.x), (double)(2)) + pow((double)(seeker->data.render.y - enemy->enemy[j].render.y), (double)(2))) < (double)(30) && enemy->enemy[j].alive == true)
                {
                    deleteProjectile(first, backseeker, seeker);
                    enemy->enemy[j].alive = false;
                    wavecontrol->score++;
                    seeker = *first;
                    break;
                }
        }
        backseeker = seeker;
    }
}

//Lovedekek utkozesenek vizsgalata
void projectilecollisionDetection(ProjectileList **first)
{
    ProjectileList *seeker;
    ProjectileList *backseeker = NULL;
    for (seeker = *first; seeker != NULL; seeker = seeker->next)
    {
        if (seeker->data.type == ship)
        {
            ProjectileList *seeker_2;
            ProjectileList *backseeker_2 = NULL;
            for (seeker_2 = *first; seeker_2 != NULL; seeker_2 = seeker_2->next)
            {
                if(sqrt(pow((double)(seeker->data.render.x - seeker_2->data.render.x), (double)(2)) + pow((double)(seeker->data.render.y - seeker_2->data.render.y), (double)(2))) < (double)(30) && seeker_2->data.type != ship)
                {
                    doubledeleteProjectile(first, seeker, backseeker, seeker_2, backseeker_2);
                    seeker_2 = *first;
                    seeker = *first;
                    return;
                }
                backseeker_2 = seeker_2;
            }
        }
        backseeker = seeker;
    }
}

//Jatekos eltalalasanak vizsgalata
void playerhitDetection(ProjectileList **first, Creature *player)
{
    ProjectileList *seeker;
    ProjectileList *backseeker = NULL;
    for (seeker = *first; seeker != NULL; seeker = seeker->next)
    {
        if(sqrt(pow((double)(seeker->data.render.x - player->render.x), (double)(2)) + pow((double)(seeker->data.render.y - player->render.y), (double)(2))) < (double)(16) && player->alive == true && seeker->data.type != ship)
        {
            player->alive = false;
            deleteProjectile(first, backseeker, seeker);
            seeker = *first;
            return;
        }
        backseeker = seeker;
    }
}

//Lovedektalalatok erzekelese
void combinedProjectileDetection(ProjectileList **first, Enemies *enemy, WaveControl *wavecontrol, Creature *player)
{
    autodestroyProjectile(first);

    enemyhitDetection(first, enemy, &(*wavecontrol));

    projectilecollisionDetection(first);

    playerhitDetection(first, player);
}

//Lovedek letrehozasa
void createProjectile(Creature creature, ProjectileList **first, SDL_Renderer *renderer)
{
    ProjectileList *newprojectile = (ProjectileList*) malloc(sizeof(ProjectileList));
    newprojectile->next = NULL;
    newprojectile->data.type = creature.emitter;
    newprojectile->data.render.x = creature.render.x;
    newprojectile->data.render.y = creature.render.y;
    switch(newprojectile->data.type)
    {
    case ship:

        newprojectile->data.render.texture = loadTexture("resources/projectileship.png", renderer);
        newprojectile->data.speed = -16;
        break;

    case slow:

        newprojectile->data.render.texture = loadTexture("resources/projectile1.png", renderer);
        newprojectile->data.speed = 8;
        break;

    case medium:

        newprojectile->data.render.texture = loadTexture("resources/projectile2.png", renderer);
        newprojectile->data.speed = 12;
        break;

    case fast:

        newprojectile->data.render.texture = loadTexture("resources/projectile3.png", renderer);
        newprojectile->data.speed = 16;
        break;
    }

    if (*first == NULL)
    {
        *first = newprojectile;
    }
    else
    {
        ProjectileList *seeker = *first;
        while (seeker->next != NULL)
            seeker = seeker->next;
        seeker->next = newprojectile;
    }
}

//Jatekos lovedek kilovese
void fire(WaveControl *wavecontrol, Controls *input, Creature player, ProjectileList **projectilelist, SDL_Renderer *renderer)
{
    if (input->autofire == 1)
    {
        if (wavecontrol->fireready)
        {
            wavecontrol->fireready = false;
            wavecontrol->firetime = 200;
            createProjectile(player, projectilelist, renderer);
        }
    }
    else
    {
        if (input->space && wavecontrol->fireready)
        {
            wavecontrol->fireready = false;
            wavecontrol->firetime = 200;
            createProjectile(player, projectilelist, renderer);
        }
    }
}

//Lovedekek frissitese eggyel
void refreshProjectile(ProjectileList *first)
{
    ProjectileList *seeker;
    for (seeker = first; seeker != NULL; seeker = seeker->next)
    {
        seeker->data.render.y = seeker->data.render.y + seeker->data.speed;
    }
}

//Ellenfelek tiszta loveslehetosegenek vizsgalata
bool detectProjectilePath(Creature *enemy, int i)
{
    i+=10;
    while(i < 30)
    {
        if (enemy[i].alive == true)
            return false;
        i+=10;
    }
    return true;
}

//Ellenfelek tuzelese
void enemyfire(WaveControl *wavecontrol, Enemies *enemy, ProjectileList **projectilelist, SDL_Renderer *renderer)
{
    if (wavecontrol->enemyfireready == true && enemyalive(enemy, 0, 30))
    {
        int i;
        while(true)
        {
            i = rand()%30;
            if (enemy->enemy[i].alive == true && detectProjectilePath(enemy->enemy, i) == true)
            {
                break;
            }

        }
        createProjectile(enemy->enemy[i], projectilelist, renderer);
        wavecontrol->enemyfireready = false;
    }
}
