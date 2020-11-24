#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include "struct.h"
#include "timer.h"
#include "enemy.h"
#include "projectile.h"
#include "render.h"
#include "player.h"
#include "sdl_event.h"
#include <time.h>
#include <SDL2/SDL_ttf.h>
#include <stdlib.h>

#include "debugmalloc.h"


int main(int argc, char *argv[])
{
    srand(time(0));
    /* ablak letrehozasa */
    SDL_Window *window;
    SDL_Renderer *renderer;
    sdl_init("SPACE INVADERS", 1280, 784, &window, &renderer);

    SDL_Event event;
    SDL_WaitEvent(&event);

    Fonts fonts;
    TTF_Init();
    fonts.hudfont = TTF_OpenFont("resources/pixel.ttf", 64);
    if (!fonts.hudfont) {
        SDL_Log("Nem sikerult megnyitni a fontot! %s\n", TTF_GetError());
        exit(1);
    }

    ProjectileArray projectileArray;
    projectileArray.data = (Projectile*) malloc(0 * sizeof(Projectile));
    projectileArray.scale = 0;

    Creature player;
    MoveNumbers enemymoves = {0, 1};
    player.render.x = 704;
    player.render.y = 648;
    player.emitter = ship;
    player.render.texture = loadTexture("resources/ship.png", renderer);
    player.alive = true;
    Creature *enemy = (Creature*) malloc(30 * sizeof(Creature));

    Controls input = {-1, false, false, false, false};
    WaveControl wavecontrol = {0, 3, 0, 200, false, false};

    //Ellenfelek és időzítők létrehozása
    spawnWave(&enemy, renderer);
    Timers timers;
    timers.movetimer = SDL_AddTimer(500, movetime, NULL);
    timers.projectiletimer = SDL_AddTimer(50, projectiletime, NULL);
    timers.firetimer = SDL_AddTimer(200, firetime, NULL);
    timers.firetimermemory = 200;
    timers.enemyfiretimer = SDL_AddTimer(100, enemyfiretime, NULL);
    timers.respawntimer = SDL_AddTimer(0, respawntime, NULL);
    timers.respawntimermemory = 0;

    while (!input.quit)
    {
        //checkWave();

        checkEvents(&wavecontrol, &input, &enemymoves, &enemy, &projectileArray, &player);

        movePlayer(input, &player);

        fire(&wavecontrol, &input, player, &projectileArray, renderer);

        enemyfire(&wavecontrol, &enemy, &projectileArray, renderer);

        refreshTimers(&timers, &wavecontrol);

        respawn(&wavecontrol, &player, &timers, renderer);

        refreshScene(player, enemy, projectileArray, renderer);

        drawhud(wavecontrol, fonts, renderer);

        SDL_Delay(10);

    }

    /* szükséges elemek törlése */
    SDL_RemoveTimer(timers.movetimer);
    SDL_RemoveTimer(timers.projectiletimer);
    SDL_RemoveTimer(timers.firetimer);
    SDL_RemoveTimer(timers.enemyfiretimer);
    free(projectileArray.data);
    free(enemy);
    SDL_Quit();

    return 0;
}
