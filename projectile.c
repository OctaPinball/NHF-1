#include "common.h"

//L�ved�k t�rl�se, t�mb cs�kkent�se
void deleteProjectile(ProjectileArray *projectileArray, int idx)
{
    SDL_DestroyTexture(projectileArray->data[idx].render.texture);
    Projectile *ujtomb = (Projectile*)malloc(((projectileArray->scale) - 1) * sizeof(Projectile));
    int j = 0;
    for (int i = 0; i < projectileArray->scale; i++)
    {
        if (i != idx)
        {
            ujtomb[j] = projectileArray->data[i];
            j++;
        }
    }
    free(projectileArray->data);
    projectileArray->data = ujtomb;
    projectileArray->scale-=1;
}
//L�ved�k tal�lat ellen�rz�se
void combinedProjectileDetection(WaveControl *wavecontrol, Creature *player, Enemies *enemy, ProjectileArray *projectileArray)
{
    for (int i = 0; i < projectileArray->scale; i++)
        if (projectileArray->data->render.y < -10 || projectileArray->data->render.y > 720)
        {
            deleteProjectile(projectileArray, i--);
        }
    for (int i = 0; i < projectileArray->scale; i++)
    {
        if (projectileArray->data[i].type == ship)
        {
            for (int j = 0; j < 30; j++)
            {
                if (sqrt(pow((double)(projectileArray->data[i].render.x - enemy->enemy[j].render.x), (double)(2)) + pow((double)(projectileArray->data[i].render.y - enemy->enemy[j].render.y), (double)(2))) < (double)(30) && enemy->enemy[j].alive == true)
                {
                    deleteProjectile(&(*projectileArray), i--);
                    enemy->enemy[j].alive = false;
                    wavecontrol->score++;
                    break;
                }
            }
        }
    }
    for (int i = 0; i < projectileArray->scale; i++)
        if (projectileArray->data[i].type == ship)
            for (int j = 0; j < projectileArray->scale; j++)
                if(sqrt(pow((double)(projectileArray->data[i].render.x - projectileArray->data[j].render.x), (double)(2)) + pow((double)(projectileArray->data[i].render.y - projectileArray->data[j].render.y), (double)(2))) < (double)(30) && projectileArray->data[j].type != ship)
                {
                    if (i < j)
                    {
                        deleteProjectile(&(*projectileArray), i--);
                        deleteProjectile(&(*projectileArray), --j);
                        break;
                    }
                    else
                    {
                        deleteProjectile(&(*projectileArray), j--);
                        deleteProjectile(&(*projectileArray), --i);
                        break;
                    }
                }
    for (int i = 0; i < projectileArray->scale; i++)
        if(sqrt(pow((double)(projectileArray->data[i].render.x - player->render.x), (double)(2)) + pow((double)(projectileArray->data[i].render.y - player->render.y), (double)(2))) < (double)(16) && player->alive == true && projectileArray->data[i].type != ship)
{
            player->alive = false;
            deleteProjectile(&(*projectileArray), i--);
}

}
//L�ved�k l�trehoz�sa Creature f�ggv�ny�ben
void createProjectile(Creature creature, ProjectileArray *projectileArray, SDL_Renderer *renderer)
{
    Projectile *ujtomb = (Projectile*)malloc((projectileArray->scale + 1) * sizeof(Projectile));
    for (int i = 0; i < projectileArray->scale; i++)
    {
        ujtomb[i] = projectileArray->data[i];
    }
    ujtomb[projectileArray->scale].type = creature.emitter;
    ujtomb[projectileArray->scale].render.x = creature.render.x;
    ujtomb[projectileArray->scale].render.y = creature.render.y;
    free(projectileArray->data);
    projectileArray->data = ujtomb;
    projectileArray->scale += 1;

    switch(projectileArray->data[projectileArray->scale - 1].type)
    {
    case ship:

        projectileArray->data[projectileArray->scale - 1].render.texture = loadTexture("resources/projectileship.png", renderer);
        projectileArray->data[projectileArray->scale - 1].speed = -16;
        break;

    case slow:

        projectileArray->data[projectileArray->scale - 1].render.texture = loadTexture("resources/projectile1.png", renderer);
        projectileArray->data[projectileArray->scale - 1].speed = 8;
        break;

    case medium:

        projectileArray->data[projectileArray->scale - 1].render.texture = loadTexture("resources/projectile2.png", renderer);
        projectileArray->data[projectileArray->scale - 1].speed = 12;
        break;

    case fast:

        projectileArray->data[projectileArray->scale - 1].render.texture = loadTexture("resources/projectile3.png", renderer);
        projectileArray->data[projectileArray->scale - 1].speed = 16;
        break;
    }
}

void fire(WaveControl *wavecontrol, Controls *input, Creature player, ProjectileArray *projectileArray, SDL_Renderer *renderer)
{

    if (input->autofire == 1)
    {
        if (wavecontrol->fireready)
        {
            wavecontrol->fireready = false;
            wavecontrol->firetime = 200;
            createProjectile(player, &(*projectileArray), renderer);
        }
    }
    else
    {
        if (input->space && wavecontrol->fireready)
        {
            wavecontrol->fireready = false;
            wavecontrol->firetime = 200;
            createProjectile(player, &(*projectileArray), renderer);
        }
    }
}

void refreshProjectile(ProjectileArray *projectileArray)
{
    for (int i = 0; i < projectileArray->scale; i++)
    {
        projectileArray->data[i].render.y = projectileArray->data[i].render.y + projectileArray->data[i].speed;
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

void enemyfire(WaveControl *wavecontrol, Enemies *enemy, ProjectileArray *projectileArray, SDL_Renderer *renderer)
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
        createProjectile(enemy->enemy[i], &(*projectileArray), renderer);
        wavecontrol->enemyfireready = false;
    }
}

