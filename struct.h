#ifndef STRUCT_H_INCLUDED
#define STRUCT_H_INCLUDED
#include "common.h"

typedef enum State
{
    ingame,
    inmenu,
    inleaderboard,
    gamend,
    exitprogram,
} State;

typedef enum ButtonType
{
    b_new_game,
    b_leaderboard,
    b_exit,
} ButtonType;

typedef enum ProjectileType
{
    ship,
    slow,
    medium,
    fast
} ProjectileType;

typedef struct Player
{
    char name[30];
    int score;
} Player;

typedef struct renderValues
{
    int x;
    int y;
    SDL_Texture *texture;
} renderValues;

typedef struct Buttons
{
    renderValues button1;
    renderValues button2;
    renderValues button3;
} Buttons;

typedef struct Creature
{
    renderValues render;
    ProjectileType emitter;
    bool alive;
} Creature;

typedef struct Projectile
{
    renderValues render;
    int speed;
    ProjectileType type;
} Projectile;

typedef struct ProjectileArray
{
    Projectile *data;
    int scale;
} ProjectileArray;

typedef struct MoveNumbers
{
    int movexcount;
    int movexdirection;
} MoveNumbers;

typedef struct WaveControl
{
    int wave;
    int life;
    int score;
    int firetime;
    bool enemyfireready;
    bool fireready;
} WaveControl;

typedef struct Timers
{
    bool refreshWaveTimers;
    SDL_TimerID movetimer;
    int movetimernewvalue;
    SDL_TimerID projectiletimer;
    SDL_TimerID firetimer;
    int firetimermemory;
    SDL_TimerID enemyfiretimer;
    int enemyfiretimernewvalue;
    SDL_TimerID respawntimer;
    int respawntimermemory;
    int respawntimernewvalue;
} Timers;

typedef struct Fonts
{
    TTF_Font *hudfont;
} Fonts;

typedef struct Controls
{
    int autofire;
    bool quit;
    bool left;
    bool right;
    bool space;
} Controls;

#endif // STRUCT_H_INCLUDED
