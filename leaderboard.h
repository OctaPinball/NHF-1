#ifndef LEADERBOARD_H_INCLUDED
#define LEADERBOARD_H_INCLUDED

void sortScoreboard(Player newplayer);
bool input_text(char *dest, size_t hossz, SDL_Rect teglalap, SDL_Color hatter, SDL_Color szoveg, TTF_Font *font, SDL_Renderer *renderer);
void enterName(WaveControl wavecontrol, TTF_Font *font);

#endif // LEADERBOARD_H_INCLUDED
