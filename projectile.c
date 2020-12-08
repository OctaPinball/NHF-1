#include "common.h"


void freeProjectile(ProjectileList *first)
{
    ProjectileList *seeker = first;
    while (seeker != NULL)
    {
        ProjectileList *next_ptr = seeker->next;
        free(seeker);
        seeker = next_ptr;
    }
}

void deleteProjectile(ProjectileList **first, ProjectileList *backseeker, ProjectileList *seeker)
{
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

void autodestroyProjectile(ProjectileList **first)
{
    //ProjectileList *seeker;
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
                    deleteProjectile(first, backseeker, seeker);
                    deleteProjectile(first, backseeker_2, seeker_2);
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

void playerhitDetection(ProjectileList **first, Creature *player)
{
    ProjectileList *seeker;
    ProjectileList *backseeker = NULL;
    for (seeker = *first; seeker != NULL; seeker = seeker->next)
    {
        if(sqrt(pow((double)(seeker->data.render.x - player->render.x), (double)(2)) + pow((double)(seeker->data.render.y - player->render.y), (double)(2))) < (double)(16) && player->alive == true && seeker->data.type != ship)
        {
            //player->alive = false;
            deleteProjectile(first, backseeker, seeker);
            seeker = *first;
            return;
        }
        backseeker = seeker;
    }
}

void combinedProjectileDetection2(ProjectileList **first, Enemies *enemy, WaveControl *wavecontrol, Creature *player)
{
    autodestroyProjectile(first);

    enemyhitDetection(first, enemy, &(*wavecontrol));

    projectilecollisionDetection(first);

    playerhitDetection(first, player);

    ProjectileList *seeker;
    int i = 0;
    for (seeker = *first; seeker != NULL; seeker = seeker->next)
        i++;
    printf("%d\n", i);
}

void combinedProjectileDetection(ProjectileList **first, Enemies *enemy, WaveControl *wavecontrol, Creature *player)
{
    ProjectileList *seeker;
    ProjectileList *backseeker = NULL;
    for (seeker = *first; seeker != NULL; seeker = seeker->next)
    {
        if (seeker->data.render.y < -10 || seeker->data.render.y > 720)
        {
            deleteProjectile(first, backseeker, seeker);
            break;
        }
        backseeker = seeker;
    }


    backseeker = NULL;
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


    backseeker = NULL;
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
                    deleteProjectile(first, backseeker, seeker);
                    deleteProjectile(first, backseeker_2, seeker_2);
                    seeker_2 = *first;
                    seeker = *first;
                    break;
                }
                backseeker_2 = seeker_2;
            }
        }
        backseeker = seeker;
    }


    backseeker = NULL;
    for (seeker = *first; seeker != NULL; seeker = seeker->next)
    {
        if(sqrt(pow((double)(seeker->data.render.x - player->render.x), (double)(2)) + pow((double)(seeker->data.render.y - player->render.y), (double)(2))) < (double)(16) && player->alive == true && seeker->data.type != ship)
        {
            //player->alive = false;
            deleteProjectile(first, backseeker, seeker);
            seeker = *first;
            break;
        }
        backseeker = seeker;
    }
}

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
        /* üres listánál ez lesz az első elem */
        *first = newprojectile;
        printf("%d %d\n", newprojectile->data.render.x, newprojectile->data.render.y);
    }
    else
    {
        /* ha nem üres a lista, az utolsó után fűzzük */
        ProjectileList *seeker = *first;
        while (seeker->next != NULL)
            seeker = seeker->next;
        seeker->next = newprojectile;
        printf("\njej");
    }
}

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

void refreshProjectile(ProjectileList *first)
{
    ProjectileList *seeker;
    for (seeker = first; seeker != NULL; seeker = seeker->next)
    {
        seeker->data.render.y = seeker->data.render.y + seeker->data.speed;
    }
}

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

