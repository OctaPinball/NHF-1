#include "common.h"

ButtonType buttonDetect(event){
    if
}

void menu(void){
    SDL_Window *window;
    SDL_Renderer *renderer;
    sdl_init("SPACE INVADERS", 1280, 720, &window, &renderer);
    while(true)
    {
        SDL_Event event;
        SDL_WaitEvent(&event);
        switch (event.type) {
            case SDL_MOUSEMOTION:
            case SDL_MOUSEBUTTONDOWN:
                if (event.button.button == SDL_BUTTON_LEFT) {
        }
    }


}
