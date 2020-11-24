#ifndef STRUCT_H_INCLUDED
#define STRUCT_H_INCLUDED
#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <stdbool.h>
#include <SDL2/SDL_ttf.h>

typedef enum ProjectileType
{
    ship,
    slow,
    medium,
    fast
} ProjectileType;

typedef struct renderValues
{
    int x;
    int y;
    SDL_Texture *texture;
} renderValues;

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
    SDL_TimerID movetimer;
    SDL_TimerID projectiletimer;
    SDL_TimerID firetimer;
    int firetimermemory;
    SDL_TimerID enemyfiretimer;
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
