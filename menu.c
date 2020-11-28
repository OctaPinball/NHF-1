#include "common.h"

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

void menu(State *state)
{
    SDL_Window *window;
    SDL_Renderer *renderer;
    sdl_init("SPACE INVADERS", 1280, 720, &window, &renderer);
    Buttons buttons;
    buttons.button1.x = 350;
    buttons.button1.y = 328;
    buttons.button1.texture = loadTexture("resources/button_inactive.png", renderer);
    buttons.button2.x = 350;
    buttons.button2.y = 448;
    buttons.button2.texture = loadTexture("resources/button_inactive.png", renderer);
    buttons.button3.x = 350;
    buttons.button3.y = 568;
    buttons.button3.texture = loadTexture("resources/button_inactive.png", renderer);
    renderValues background;
    background.x = 0;
    background.y = 0;
    background.texture = loadTexture("resources/menu_background.png", renderer);
    bool exitmenu = false;
    while(!exitmenu)
    {
        SDL_RenderClear(renderer);
        SDL_Event event;
        SDL_WaitEvent(&event);
        SDL_DestroyTexture(buttons.button1.texture);
        SDL_DestroyTexture(buttons.button2.texture);
        SDL_DestroyTexture(buttons.button3.texture);
        buttons.button1.texture = loadTexture("resources/button_inactive.png", renderer);
        buttons.button2.texture = loadTexture("resources/button_inactive.png", renderer);
        buttons.button3.texture = loadTexture("resources/button_inactive.png", renderer);
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
                    SDL_DestroyTexture(buttons.button1.texture);
                    buttons.button1.texture = loadTexture("resources/button_active.png", renderer);
                    break;
                case b_leaderboard:
                    SDL_DestroyTexture(buttons.button2.texture);
                    buttons.button2.texture = loadTexture("resources/button_active.png", renderer);
                    break;
                case b_exit:
                    SDL_DestroyTexture(buttons.button3.texture);
                    buttons.button3.texture = loadTexture("resources/button_active.png", renderer);
                    break;
                }
                break;
            case SDL_QUIT:
                *state = exitprogram;
                exitmenu = true;
                break;

            }
        draw(background, renderer);
        draw(buttons.button1, renderer);
        draw(buttons.button2, renderer);
        draw(buttons.button3, renderer);
        SDL_RenderPresent(renderer);
    }
    SDL_DestroyTexture(background.texture);
    SDL_DestroyTexture(buttons.button1.texture);
    SDL_DestroyTexture(buttons.button2.texture);
    SDL_DestroyTexture(buttons.button3.texture);
    SDL_Quit();
}
