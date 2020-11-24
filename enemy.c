#include "struct.h"
#include "render.h"
#include <stdbool.h>
#include <time.h>


#include "debugmalloc.h"

void spawnWave(Creature **enemy, SDL_Renderer *renderer)
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            (*enemy)[(i * 10 + j)].render.x = j * 64;
            (*enemy)[(i * 10 + j)].render.y = i * 64;
            (*enemy)[(i * 10 + j)].alive = true;
            switch (i)
            {
            case 0:
            {
                (*enemy)[(i * 10 + j)].render.texture = loadTexture("resources/alien1.png", renderer);
                (*enemy)[(i * 10 + j)].emitter = slow;
                break;
            }
            case 1:
            {
                (*enemy)[(i * 10 + j)].render.texture = loadTexture("resources/alien2.png", renderer);
                (*enemy)[(i * 10 + j)].emitter = fast;
                break;
            }
            case 2:
            {
                (*enemy)[(i * 10 + j)].render.texture = loadTexture("resources/alien3.png", renderer);
                (*enemy)[(i * 10 + j)].emitter = medium;
                break;
            }
            }
        }
    }
}

void moveEnemy(MoveNumbers *enemymove, Creature **enemy)
{
    if (enemymove->movexcount == 20)
    {
        enemymove->movexdirection *= (-1);
        enemymove->movexcount = 0;
        for (int i = 0; i < 30; i++)
        {
            (*enemy)[i].render.y += 64;
        }
    }
    else
    {
        enemymove->movexcount += 1;
        for (int i = 0; i < 30; i++)
        {
            if (enemymove->movexdirection == 1)
                (*enemy)[i].render.x += 32;
            if (enemymove->movexdirection == -1)
                (*enemy)[i].render.x -= 32;
        }
    }
}


