#include "common.h"

void game(void){
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

    for(int i = 0; i < 30; i++)
        enemy[i].render.texture = NULL;

    Controls input = {-1, false, false, false, false};
    WaveControl wavecontrol = {1, 3, 0, 200, false, false};

    //Ellenfelek �s id�z�t�k l�trehoz�sa
    spawnWave(&enemy, renderer);
    Timers timers;
    timers.refreshWaveTimers = false;
    timers.movetimer = SDL_AddTimer(500, movetime, NULL);
    timers.movetimernewvalue = 500;
    timers.projectiletimer = SDL_AddTimer(50, projectiletime, NULL);
    timers.firetimer = SDL_AddTimer(200, firetime, NULL);
    timers.firetimermemory = 200;
    timers.enemyfiretimer = SDL_AddTimer(100, enemyfiretime, NULL);
    timers.enemyfiretimernewvalue = 100;
    timers.respawntimer = SDL_AddTimer(0, respawntime, NULL);
    timers.respawntimermemory = 0;

    while (!input.quit)
    {
        checkWave(&timers, &enemymoves, &wavecontrol, &enemy, &projectileArray, renderer);

        checkEvents(&wavecontrol, &input, &enemymoves, &enemy, &projectileArray, &player);

        movePlayer(input, &player);

        fire(&wavecontrol, &input, player, &projectileArray, renderer);

        enemyfire(&wavecontrol, &enemy, &projectileArray, renderer);

        refreshTimers(&timers, &wavecontrol);

        respawn(&wavecontrol, &player, &timers, renderer);

        //prepareScene(player, enemy, projectileArray, renderer);

        refreshScene(player, enemy, projectileArray, renderer);

        drawhud(wavecontrol, fonts, renderer);

        SDL_Delay(10);

    }

    /* sz�ks�ges elemek t�rl�se */
    SDL_RemoveTimer(timers.movetimer);
    SDL_RemoveTimer(timers.projectiletimer);
    SDL_RemoveTimer(timers.firetimer);
    SDL_RemoveTimer(timers.enemyfiretimer);
    SDL_RemoveTimer(timers.respawntimer);
    TTF_CloseFont(fonts.hudfont);
    free(projectileArray.data);
    free(enemy);
    SDL_Quit();
}
