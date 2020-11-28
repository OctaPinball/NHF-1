#ifndef RENDER_H_INCLUDED
#define RENDER_H_INCLUDED

void draw(renderValues render, SDL_Renderer *renderer);
void textdraw(renderValues source ,char *text, TTF_Font *fonts, SDL_Renderer *renderer);
void drawhud(WaveControl wavecontrol, TTF_Font *fonts, SDL_Renderer *renderer);
void refreshScene(Creature player, Creature *enemy, ProjectileArray projectileArray, SDL_Renderer *renderer);
void prepareScene(Creature player, Creature *enemy, ProjectileArray projectileArray, SDL_Renderer *renderer);
void sdl_init(char const *felirat, int szeles, int magas, SDL_Window **pwindow, SDL_Renderer **prenderer);
SDL_Texture *loadTexture(char *filename, SDL_Renderer *renderer);
#endif // RENDER_H_INCLUDED
