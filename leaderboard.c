#include "common.h"

void freearray(char **names, int size){
    for (int i = 0; i < size; i++)
        free(names[i]);
    free(names);
}
//Átméretezi a names dinamikus tömböt és felveszi a newname-t
void resizenames(char ***names, int size, char *newname)
{
    char **newnames = (char**) malloc(size * sizeof(char*));
    for (int i = 0; i < size - 1; i++)
    {
        int charsize = strlen((*names)[i]) + 1;
        newnames[i] = (char*) malloc(charsize * sizeof(char));
        strcpy(newnames[i], (*names)[i]);
    }
    int charsize = strlen(newname) + 1;
    newnames[size - 1] = (char*) malloc(charsize * sizeof(char));
    strcpy(newnames[size - 1], newname);
    freearray(*names, size - 1);
    *names = newnames;
}
//Átméretezi a scores dinamikus tömböt és felveszi a scoretempet-t
void resizescore(int **scores, int size, int scoretemp)
{
    int *newscores = (int*) malloc(size * sizeof(int));
    for (int i = 0; i < size - 1; i++)
        newscores[i] = (*scores)[i];
    newscores[size - 1] = scoretemp;
    free(*scores);
    *scores = newscores;
}
//Megcseréli a neveket
void bubble_switch(int *score1, int *score2, char **name1, char **name2)
{

    int scoretemp = *score1;
    score1 = score2;
    *score2 = scoretemp;

    char *nametemp = *name1;
    *name1 = *name2;
    *name2 = nametemp;
}
//Buborékrendezés alapján rendezi a names és a scores dinamikus tömböket
void bubblesort(char **names, int size, int *scores)
{
    for(int i=0; i<size; i++)
    {
        for(int j=0; j<size - i - 1; j++)
        {
            if(scores[j] < scores[j+1])
            {
                bubble_switch(&scores[j], &scores[j+1], &names[j], &names[j+1]);
            }
        }
    }
}


void sortScoreboard(char *newname, int newscore)
{
    int *scores = (int*)malloc(0 * sizeof(int));
    char **names = (char**)malloc(0 * sizeof(char*)); //szavak száma , karakterek száma
    char nametemp[30]; //LEHETNE POINTER!!
    int scoretemp;
    int size = 0;
    FILE *leaderboardFile = fopen("leaderboard.txt", "r");

    //Beolvasás fiájlból
    for(int i = 0; i < 10 && fscanf(leaderboardFile, "%s %d%*c", nametemp, &scoretemp) != EOF; i++)
    {
        size++;
        resizenames(&names, size, nametemp);
        resizescore(&scores, size, scoretemp);
    }

        size++;
        resizenames(&names, size, newname);
        resizescore(&scores, size, newscore);


    //Buborékrendezéssel rendezés
    bubblesort(names, size, scores);


    fclose(leaderboardFile);
    FILE *leaderboardFile2 = fopen("leaderboard.txt", "w");

    //Fájlbaírás
    for(int i=0; i<size; i++)
    {
        fprintf(leaderboardFile2, "%s %d\n", names[i], scores[i]);
    }
    freearray(names, size);
    free(scores);
    fclose(leaderboardFile2);
}

/* Beolvas egy szoveget a billentyuzetrol.
 * A rajzolashoz hasznalt font es a megjelenito az utolso parameterek.
 * Az elso a tomb, ahova a beolvasott szoveg kerul.
 * A masodik a maximális hossz, ami beolvasható.
 * A visszateresi erteke logikai igaz, ha sikerult a beolvasas. */
bool input_text(char *dest, size_t hossz, SDL_Rect teglalap, SDL_Color hatter, SDL_Color szoveg, TTF_Font *font, SDL_Renderer *renderer)
{
    /* Ez tartalmazza az aktualis szerkesztest */
    char composition[SDL_TEXTEDITINGEVENT_TEXT_SIZE];
    composition[0] = '\0';
    /* Ezt a kirajzolas kozben hasznaljuk */
    char textandcomposition[hossz + SDL_TEXTEDITINGEVENT_TEXT_SIZE + 1];
    /* Max hasznalhato szelesseg */
    int maxw = teglalap.w - 2;
    int maxh = teglalap.h - 2;

    dest[0] = '\0';

    bool enter = false;
    bool kilep = false;

    SDL_StartTextInput();
    while (!kilep && !enter)
    {
        /* doboz kirajzolasa */
        boxRGBA(renderer, teglalap.x, teglalap.y, teglalap.x + teglalap.w - 1, teglalap.y + teglalap.h - 1, hatter.r, hatter.g, hatter.b, 255);
        rectangleRGBA(renderer, teglalap.x, teglalap.y, teglalap.x + teglalap.w - 1, teglalap.y + teglalap.h - 1, szoveg.r, szoveg.g, szoveg.b, 255);
        /* szoveg kirajzolasa */
        int w;
        strcpy(textandcomposition, dest);
        strcat(textandcomposition, composition);
        if (textandcomposition[0] != '\0')
        {
            SDL_Surface *felirat = TTF_RenderUTF8_Blended(font, textandcomposition, szoveg);
            SDL_Texture *felirat_t = SDL_CreateTextureFromSurface(renderer, felirat);
            SDL_Rect cel = { teglalap.x, teglalap.y, felirat->w < maxw ? felirat->w : maxw, felirat->h < maxh ? felirat->h : maxh };
            SDL_RenderCopy(renderer, felirat_t, NULL, &cel);
            SDL_FreeSurface(felirat);
            SDL_DestroyTexture(felirat_t);
            w = cel.w;
        }
        else
        {
            w = 0;
        }
        /* kurzor kirajzolasa */
        if (w < maxw)
        {
            vlineRGBA(renderer, teglalap.x + w + 2, teglalap.y + 2, teglalap.y + teglalap.h - 3, szoveg.r, szoveg.g, szoveg.b, 192);
        }
        /* megjeleniti a képernyon az eddig rajzoltakat */
        SDL_RenderPresent(renderer);

        SDL_Event event;
        SDL_WaitEvent(&event);
        switch (event.type)
        {
        /* Kulonleges karakter */
        case SDL_KEYDOWN:
            if (event.key.keysym.sym == SDLK_BACKSPACE)
            {
                int textlen = strlen(dest);
                do
                {
                    if (textlen == 0)
                    {
                        break;
                    }
                    if ((dest[textlen-1] & 0x80) == 0x00)
                    {
                        /* Egy bajt */
                        dest[textlen-1] = 0x00;
                        break;
                    }
                    if ((dest[textlen-1] & 0xC0) == 0x80)
                    {
                        /* Bajt, egy tobb-bajtos szekvenciabol */
                        dest[textlen-1] = 0x00;
                        textlen--;
                    }
                    if ((dest[textlen-1] & 0xC0) == 0xC0)
                    {
                        /* Egy tobb-bajtos szekvencia elso bajtja */
                        dest[textlen-1] = 0x00;
                        break;
                    }
                }
                while(true);
            }
            if (event.key.keysym.sym == SDLK_RETURN)
            {
                enter = true;
            }
            break;

        /* A feldolgozott szoveg bemenete */
        case SDL_TEXTINPUT:
            if (strlen(dest) + strlen(event.text.text) < hossz)
            {
                strcat(dest, event.text.text);
            }

            /* Az eddigi szerkesztes torolheto */
            composition[0] = '\0';
            break;

        /* Szoveg szerkesztese */
        case SDL_TEXTEDITING:
            strcpy(composition, event.edit.text);
            break;

        case SDL_QUIT:
            /* visszatesszuk a sorba ezt az eventet, mert
             * sok mindent nem tudunk vele kezdeni */
            SDL_PushEvent(&event);
            kilep = true;
            break;
        }
    }

    /* igaz jelzi a helyes beolvasast; = ha enter miatt allt meg a ciklus */
    SDL_StopTextInput();
    return enter;
}

void enterName(WaveControl wavecontrol)
{
    SDL_Window *window;
    SDL_Renderer *renderer;
    TTF_Font *font;
    sdl_init("SPACE INVADERS", 720, 360, &window, &renderer, &font);
    renderValues text = {42, 80, NULL};
    textdraw(text,"GREAT SCORE!   ENTER YOUR NAME!", font, renderer);
    SDL_Color feher = {255, 255, 255}, fekete = { 0, 0, 0 };
    SDL_Rect r = { 60, 180, 600, 70 };
    char playername[30];
    int playerscore = wavecontrol.score;
    input_text(playername, 30, r, fekete, feher, font, renderer);

    sortScoreboard(playername, playerscore);
}

void showleaderboard(State *state)
{
    SDL_Window *window;
    SDL_Renderer *renderer;
    TTF_Font *font;
    sdl_init("SPACE INVADERS", 1000, 710, &window, &renderer, &font);
    TTF_Font *fontbig = TTF_OpenFont("resources/pixel.ttf", 128);
    *state = inmenu;
    renderValues text = {260, 0, NULL};
    textdraw(text,"LEADERBOARD", fontbig, renderer);
    char playername[10][30];
    int playerscore[10];
    renderValues r_name = {20, 100, NULL};
    renderValues r_score = {850, 100, NULL};
    FILE *leaderboardFile = fopen("leaderboard.txt", "r");
    for(int i = 0; i < 10 && fscanf(leaderboardFile, "%s %d%*c", playername[i], &playerscore[i]) != EOF; i++)
    {
        char name[30];
        char score[7];
        sprintf(name, "%s", playername[i]);
        textdraw(r_name, name, font, renderer);
        sprintf(score, "%5d", playerscore[i]);
        textdraw(r_score, score, font, renderer);
        r_name.y += 60;
        r_score.y += 60;
    }
    fclose(leaderboardFile);

    SDL_RenderPresent(renderer);
    while (true)
    {
        SDL_RenderClear(renderer);
        SDL_Event event;
        SDL_WaitEvent(&event);
        if (event.type == SDL_QUIT)
        {
                sdl_close(&window, &renderer, &font);
                break;
        }
        if (event.type == SDL_KEYUP)
            if (event.key.keysym.sym == SDLK_ESCAPE)
            {
                sdl_close(&window, &renderer, &font);
                break;
            }
    }
}
