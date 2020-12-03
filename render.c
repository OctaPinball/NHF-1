#include "common.h"

//Tárgy megrajzolása
void draw(renderValues render, SDL_Renderer *renderer)
{
    SDL_Rect dest;

    dest.x = render.x;
    dest.y = render.y;
    SDL_QueryTexture(render.texture, NULL, NULL, &dest.w, &dest.h);

    SDL_RenderCopy(renderer, render.texture, NULL, &dest);
}

//Szöveg texture-é alakítása
void textdraw(renderValues source ,char *text, TTF_Font *fonts, SDL_Renderer *renderer){
    SDL_Surface *felirat;

    SDL_Color feher = {255, 255, 255};

    felirat = TTF_RenderUTF8_Solid(fonts, text, feher);
    source.texture = SDL_CreateTextureFromSurface(renderer, felirat);

    draw(source, renderer);
    SDL_FreeSurface(felirat);
    SDL_DestroyTexture(source.texture);
}

//Kijelezni kívánt adatok elrendezése
void drawhud(WaveControl wavecontrol, TTF_Font *fonts, SDL_Renderer *renderer){
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

//Minden elem megrajzolása
void refreshScene(Creature player, Enemies enemy, ProjectileList *first, SDL_Renderer *renderer)
{
    SDL_RenderClear(renderer);
    //if (player.alive == true)
        draw(player.render, renderer);
    for (int i = 0; i < 30; i++)
    {
        if (enemy.enemy[i].alive == true)
        {
            draw(enemy.enemy[i].render, renderer);
        }
    }
    ProjectileList *seeker;
    for (seeker = first; seeker != NULL; seeker = seeker->next)
    {
        draw(seeker->data.render, renderer);
    }
}



void sdl_init(char const *felirat, int szeles, int magas, SDL_Window **pwindow, SDL_Renderer **prenderer, TTF_Font **pfont)
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
    TTF_Init();
    TTF_Font *font = TTF_OpenFont("resources/pixel.ttf", 64);
    if (font == NULL) {
        SDL_Log("Nem sikerult megnyitni a fontot! %s\n", TTF_GetError());
        exit(1);
    }
    SDL_RenderClear(renderer);

    *pfont = font;
    *pwindow = window;
    *prenderer = renderer;
}

void sdl_close(SDL_Window **pwindow, SDL_Renderer **prenderer, TTF_Font **pfont) {
    SDL_DestroyRenderer(*prenderer);
    *prenderer = NULL;

    SDL_DestroyWindow(*pwindow);
    *pwindow = NULL;

    TTF_CloseFont(*pfont);
    *pfont = NULL;

    SDL_Quit();
}

SDL_Texture *loadTexture(char *filename, SDL_Renderer *renderer)
{
    SDL_Texture *texture;

    SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Loading %s", filename);

    texture = IMG_LoadTexture(renderer, filename);

    return texture;
}
