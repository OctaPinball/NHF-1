#include "common.h"
#include "debugmalloc.h"

//Egermutato a gombon valo vizsgalata
ButtonType buttonDetect(SDL_Event event)
{
    if (event.button.x > 350 &&  event.button.x < 930 &&event.button.y > 328 && event.button.y < 392)
        return b_new_game;
    if (event.button.x > 350 &&  event.button.x < 930 &&event.button.y > 448 && event.button.y < 512)
        return b_leaderboard;
    if (event.button.x > 350 &&  event.button.x < 930 &&event.button.y > 568 && event.button.y < 632)
        return b_exit;
    return -1;

}

//Menu letrehozasa
void menu(State *state)
{
    SDL_Window *window;
    SDL_Renderer *renderer;
    TTF_Font *font;
    sdl_init("SPACE INVADERS", 1280, 720, &window, &renderer, &font);
    renderValues buttons[3];
    for (int i = 0; i < 3; i++)
    {
        buttons[i].x = 350;
        buttons[i].y = 328 + i * 120;
        buttons[i].texture = loadTexture("resources/button_inactive.png", renderer);
    }
    renderValues background = {0, 0, loadTexture("resources/menu_background.png", renderer)};
    bool exitmenu = false;
    while(!exitmenu)
    {
        SDL_RenderClear(renderer);
        SDL_Event event;
        SDL_WaitEvent(&event);
        for (int i = 0; i < 3; i++)
        {
            SDL_DestroyTexture(buttons[i].texture);
            buttons[i].texture = loadTexture("resources/button_inactive.png", renderer);
        }
        switch (event.type)
        {
        case SDL_MOUSEBUTTONDOWN:
            if (event.button.button == SDL_BUTTON_LEFT)
            {
                switch (buttonDetect(event))
                {
                case b_new_game:
                    *state = ingame;
                    exitmenu = true;
                    break;
                case b_leaderboard:
                    *state = inleaderboard;
                    exitmenu = true;
                    break;
                case b_exit:
                    *state = exitprogram;
                    exitmenu = true;
                    break;
                }
            }
            break;
        case SDL_MOUSEMOTION:
            switch (buttonDetect(event))
            {

            case b_new_game:
                SDL_DestroyTexture(buttons[0].texture);
                buttons[0].texture = loadTexture("resources/button_active.png", renderer);
                break;
            case b_leaderboard:
                SDL_DestroyTexture(buttons[1].texture);
                buttons[1].texture = loadTexture("resources/button_active.png", renderer);
                break;
            case b_exit:
                SDL_DestroyTexture(buttons[2].texture);
                buttons[2].texture = loadTexture("resources/button_active.png", renderer);
                break;
            }
            break;
        case SDL_QUIT:
            *state = exitprogram;
            exitmenu = true;
            break;

        }
        // Menü hátterének és gombjainak megrajzolása
        draw(background, renderer);
        for (int i = 0; i < 3; i++)
            draw(buttons[i], renderer);
        SDL_RenderPresent(renderer);
    }
    // Felszabadítás és SDL bezárása
    SDL_DestroyTexture(background.texture);
    for (int i = 0; i < 3; i++)
        SDL_DestroyTexture(buttons[i].texture);
    sdl_close(&window, &renderer, &font);
}
