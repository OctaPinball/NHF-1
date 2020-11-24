#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include "struct.h"
#include <stdbool.h>
#include <string.h>

#include "debugmalloc.h"

void draw(renderValues render, SDL_Renderer *renderer)
{
    SDL_Rect dest;

    dest.x = render.x;
    dest.y = render.y;
    SDL_QueryTexture(render.texture, NULL, NULL, &dest.w, &dest.h);

    SDL_RenderCopy(renderer, render.texture, NULL, &dest);
}

void textdraw(renderValues source ,char *text, Fonts fonts, SDL_Renderer *renderer){
    SDL_Surface *felirat;

    SDL_Color feher = {255, 255, 255};

    felirat = TTF_RenderUTF8_Solid(fonts.hudfont, text, feher);
    source.texture = SDL_CreateTextureFromSurface(renderer, felirat);

    draw(source, renderer);

    /*
    hova.x = (480 - felirat->w) / 2;
    hova.y = 60;
    hova.w = felirat->w;
    hova.h = felirat->h;
    SDL_RenderCopy(renderer, felirat_t, NULL, &hova);
    SDL_FreeSurface(felirat);
    SDL_DestroyTexture(felirat_t);
    */
}

void drawhud(WaveControl wavecontrol, Fonts fonts, SDL_Renderer *renderer){
    //boxRGBA(renderer, 0, 720, 1280, 784, 100, 0, 0, 0);
    //thickLineRGBA(renderer, 0, 720, 1280, 720, 5, 255, 255, 255, 0);
    renderValues score = {10, 720, NULL};
    renderValues life = {1000, 720, NULL};
    renderValues wave = {600, 720, NULL};
    char scorechar[12], lifechar[8], wavechar[10];
    sprintf(scorechar, "SCORE: %4d", wavecontrol.score);
    sprintf(lifechar, "LIFE: %d", wavecontrol.life);
    sprintf(wavechar, "WAVE: %3d", wavecontrol.wave);
    textdraw(score, scorechar, fonts, renderer);
    textdraw(life, lifechar, fonts, renderer);
    textdraw(wave, wavechar, fonts, renderer);

    SDL_RenderPresent(renderer);
}

void refreshScene(Creature player, Creature *enemy, ProjectileArray projectileArray, SDL_Renderer *renderer)
{
    SDL_RenderClear(renderer);
    //if (player.alive == true)
        draw(player.render, renderer);
    for (int i = 0; i < 30; i++)
    {
        if (enemy[i].alive == true)
        {
            draw(enemy[i].render, renderer);
        }
    }
    for (int i = 0; i < projectileArray.scale; i++)
    {
        draw(projectileArray.data[i].render, renderer);
    }
    //SDL_RenderPresent(renderer);
}



/* ablak letrehozasa */
void sdl_init(char const *felirat, int szeles, int magas, SDL_Window **pwindow, SDL_Renderer **prenderer)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        SDL_Log("Nem indithato az SDL: %s", SDL_GetError());
        exit(1);
    }
    SDL_Window *window = SDL_CreateWindow(felirat, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, szeles, magas, 0);
    if (window == NULL)
    {
        SDL_Log("Nem hozhato letre az ablak: %s", SDL_GetError());
        exit(1);
    }
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
    if (renderer == NULL)
    {
        SDL_Log("Nem hozhato letre a megjelenito: %s", SDL_GetError());
        exit(1);
    }
    SDL_RenderClear(renderer);

    *pwindow = window;
    *prenderer = renderer;
}

SDL_Texture *loadTexture(char *filename, SDL_Renderer *renderer)
{
    SDL_Texture *texture;

    //SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Loading %s", filename);

    texture = IMG_LoadTexture(renderer, filename);

    return texture;
}
