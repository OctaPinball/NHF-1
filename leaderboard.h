#ifndef LEADERBOARD_H_INCLUDED
#define LEADERBOARD_H_INCLUDED

void freearray(char **names, int size);
void resizenames(char ***names, int size, char *newname);
void resizescore(int **scores, int size, int scoretemp);
void bubble_switch(int *score1, int *score2, char **name1, char **name2);
void bubblesort(char **names, int size, int *scores);
void sortScoreboard(char *newname, int newscore);
bool input_text(char *dest, size_t hossz, SDL_Rect teglalap, SDL_Color hatter, SDL_Color szoveg, TTF_Font *font, SDL_Renderer *renderer);
void enterName(WaveControl wavecontrol);
void showleaderboard(State *state);

#endif // LEADERBOARD_H_INCLUDED
