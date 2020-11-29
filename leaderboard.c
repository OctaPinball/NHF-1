#include "common.h"

void resizenames(char ***names, int size, char *newname)
{
    char **newnames = (char**) malloc(size * sizeof(char*));
    for (int i = 0; i < size - 1; i++)
    {
        int charsize = strlen(*names[i]) + 1;
        newnames[i] = (char*) malloc(charsize * sizeof(char));
        strcpy(newnames[i], *names[i]);
    }
    int charsize = strlen(newname) + 1;
    newnames[size - 1] = (char*) malloc(charsize * sizeof(char));
    strcpy(newnames[size - 1], newname);
}

void sortScoreboard(Player newplayer)
{
    //Player player[11];
    //player[0] = newplayer;
    //Player temp;
    char **names = NULL; //szavak száma , karakterek száma
    char nametemp[30]; //LEHETNE POINTER!!
    int scoretemp;
    int size = 0;
    FILE *leaderboardFile = fopen("leaderboard.txt", "r");

    /*READ SCORES FROM TEXTFILE*/
    for(int i = 1; i < 10 && fscanf(leaderboardFile, "%s %d%*c", &nametemp, &scoretemp) != EOF; i++)
    {
        size++;
        resizenames(&names, size, nametemp);
        //fscanf(leaderboardFile, "%s %d%*c", player[i].name, &player[i].score);
        printf("name: %s, points: %d\n", player[i].name, player[i].score);
    }
    printf("\n\n\nhow many: %d\n\n\n",size);

    /*SORT WITH BUBBLESORT*/
    for(int i=0; i<size+1; i++)
    {
        for(int j=0; j<size; j++)
        {
            if(player[j].score < player[j+1].score)
            {
                temp = player[j];
                player[j] = player[j+1];
                player[j+1] = temp;
            }
        }
    }

    fclose(leaderboardFile);
    FILE *leaderboardFile2 = fopen("leaderboard.txt", "w");
    //void rewind ( FILE * leaderboardFile2 );

    /*WRITE SORTED SCORES TO TEXTFILE*/
    for(int i=0; i<size+1; i++)
    {
        printf("%s %d\n", player[i].name, player[i].score);
        fprintf(leaderboardFile2, "%s %d\n", player[i].name, player[i].score);
    }

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
    Player endplayer;
    endplayer.score = wavecontrol.score;
    input_text(endplayer.name, 30, r, fekete, feher, font, renderer);
    sortScoreboard(endplayer);
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
    Player player[10];
    renderValues r_name = {20, 100, NULL};
    renderValues r_score = {850, 100, NULL};
    FILE *leaderboardFile = fopen("leaderboard.txt", "r");
    for(int i = 0; i < 10 && fscanf(leaderboardFile, "%s %d%*c", player[i].name, &player[i].score) != EOF; i++)
    {
        //fscanf(leaderboardFile, "%s %d%*c", player[i].name, &player[i].score);
        printf("name: %s, points: %d\n", player[i].name, player[i].score);
        char name[30];
        char score[7];
        sprintf(name, "%s", player[i].name);
        textdraw(r_name, name, font, renderer);
        sprintf(score, "%5d", player[i].score);
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
        if (event.type == SDL_KEYUP)
            if (event.key.keysym.sym == SDLK_ESCAPE)
            {
                sdl_close(&window, &renderer, &font);
                break;
            }

    }
}
