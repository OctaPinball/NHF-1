#include "common.h"


//Ellenfelek alapállapotba helyezése
void spawnWave(Enemies *enemy, SDL_Renderer *renderer)
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            enemy->enemy[(i * 10 + j)].render.x = j * 64;
            enemy->enemy[(i * 10 + j)].render.y = i * 64;
            enemy->enemy[(i * 10 + j)].alive = true;
            if (enemy->enemy[(i * 10 + j)].render.texture != NULL)
                SDL_DestroyTexture(enemy->enemy[(i * 10 + j)].render.texture);
            switch (i)
            {
            case 0:
            {
                enemy->enemy[(i * 10 + j)].render.texture = loadTexture("resources/alien1.png", renderer);
                enemy->enemy[(i * 10 + j)].emitter = slow;
                break;
            }
            case 1:
            {
                enemy->enemy[(i * 10 + j)].render.texture = loadTexture("resources/alien2.png", renderer);
                enemy->enemy[(i * 10 + j)].emitter = fast;
                break;
            }
            case 2:
            {
                enemy->enemy[(i * 10 + j)].render.texture = loadTexture("resources/alien3.png", renderer);
                enemy->enemy[(i * 10 + j)].emitter = medium;
                break;
            }
            }
        }
    }
}
//Ellenfelek ellenõrzése, hogy életben vannak-e
bool enemyalive(Enemies *enemy, int i, int j)
{
    for (int k = i; k < j; k++)
        if (enemy->enemy[k].alive == true)
            return true;
    return false;
}
//Ellenfelek eggyel mozgatása
void moveEnemy(Controls *input, Enemies *enemy)
{
    if (enemy->movenumbers.movexcount == 20)
    {
        enemy->movenumbers.movexdirection *= (-1);
        enemy->movenumbers.movexcount = 0;
        enemy->movenumbers.moveline++;
        for (int i = 0; i < 30; i++)
        {
            enemy->enemy[i].render.y += 64;
        }
    }
    else
    {
        enemy->movenumbers.movexcount += 1;
        for (int i = 0; i < 30; i++)
        {
            if (enemy->movenumbers.movexdirection == 1)
                enemy->enemy[i].render.x += 32;
            if (enemy->movenumbers.movexdirection == -1)
                enemy->enemy[i].render.x -= 32;
        }
    }
    if (enemy->movenumbers.moveline == 8 && enemyalive(enemy, 20, 30) == true)
        input->quit = true;
    if (enemy->movenumbers.moveline == 9 && enemyalive(enemy, 10, 20) == true)
        input->quit = true;
    if (enemy->movenumbers.moveline == 10 && enemyalive(enemy, 0, 10) == true)
        input->quit = true;
}


