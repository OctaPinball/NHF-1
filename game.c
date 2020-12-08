#include "common.h"

void initiatevariables(Creature *player, Enemies *enemystruct, Timers *timers, SDL_Renderer *renderer) //Változók értékadása
{
    //Játékos
    player->render.x = 704;
    player->render.y = 648;
    player->emitter = ship;
    player->render.texture = loadTexture("resources/ship.png", renderer);
    player->alive = true;

    //Ellenfelek
    for(int i = 0; i < 30; i++)
    {
        enemystruct->enemy[i].render.texture = NULL;
        enemystruct->enemy[i].alive = false;
    }
    enemystruct->movenumbers.moveline = 0;
    enemystruct->movenumbers.movexcount = 0;
    enemystruct->movenumbers.movexdirection = 1;

    //Időzítők
    timers->refreshWaveTimers = false;
    timers->movetimernewvalue = 500;
    timers->projectiletimer = SDL_AddTimer(50, projectiletime, NULL);
    timers->firetimer = SDL_AddTimer(200, firetime, NULL);
    timers->firetimermemory = 200;
    timers->enemyfiretimernewvalue = 100;
    timers->respawntimermemory = 0;
}

void game(State *state){
    srand(time(0));
    /* ablak letrehozasa */
    SDL_Window *window;
    SDL_Renderer *renderer;
    TTF_Font *font;
    sdl_init("SPACE INVADERS", 1280, 784, &window, &renderer, &font);

    //Változók létrehozása
    ProjectileList *projectilelist = NULL;
    Creature player;
    Enemies enemystruct;
    Timers timers;
    Controls input = {-1, false, false, false, false};
    WaveControl wavecontrol = {0, 3, 0, 200, false, false, 0};

    //Változók értékadása
    initiatevariables(&player, &enemystruct, &timers, renderer);

    while (!input.quit)
    {
        checkWave(&timers, &enemystruct, &wavecontrol, &projectilelist, renderer);

        checkEvents(&wavecontrol, &input, &enemystruct, &projectilelist, &player);

        movePlayer(input, &player);

        fire(&wavecontrol, &input, player, &projectilelist, renderer);

        enemyfire(&wavecontrol, &enemystruct, &projectilelist, renderer);

        refreshTimers(&timers, &wavecontrol);

        respawn(&input, &wavecontrol, &player, &timers, renderer);

        refreshScene(player, enemystruct, projectilelist, renderer);

        drawhud(wavecontrol, font, renderer);

        SDL_Delay(10);

    }

    /* szükséges elemek törlése */
    SDL_RemoveTimer(timers.movetimer);
    SDL_RemoveTimer(timers.projectiletimer);
    SDL_RemoveTimer(timers.firetimer);
    SDL_RemoveTimer(timers.enemyfiretimer);
    SDL_RemoveTimer(timers.respawntimer);
    freeProjectile(projectilelist);
    sdl_close(&window, &renderer, &font);
    SDL_Quit();
    enterName(wavecontrol);
    *state = inmenu;
}
