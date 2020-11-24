#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <stdlib.h>
#include "struct.h"
#include "projectile.h"
#include "enemy.h"
#include <stdio.h>

#include "debugmalloc.h"

Uint32 movetime(Uint32 ms, void *param)
{
    SDL_Event ev;
    ev.type = SDL_USEREVENT+1;
    SDL_PushEvent(&ev);
    return ms;   /* ujabb varakozas */
}

Uint32 projectiletime(Uint32 ms, void *param)
{
    SDL_Event ev;
    ev.type = SDL_USEREVENT;
    SDL_PushEvent(&ev);
    return ms;   /* ujabb varakozas */
}

Uint32 firetime(Uint32 ms, void *param)
{
    SDL_Event ev;
    ev.type = SDL_USEREVENT+2;
    SDL_PushEvent(&ev);
    return ms;   /* ujabb varakozas */
}

Uint32 enemyfiretime(Uint32 ms, void *param)
{
    SDL_Event ev;
    ev.type = SDL_USEREVENT+3;
    SDL_PushEvent(&ev);
    return ms;   /* ujabb varakozas */
}

Uint32 respawntime(Uint32 ms, void *param)
{
    SDL_Event ev;
    ev.type = SDL_USEREVENT+4;
    SDL_PushEvent(&ev);
    return ms;   /* ujabb varakozas */
}

void refreshTimers(Timers *timers, WaveControl *wavecontrol)
{
    if(wavecontrol->firetime != timers->firetimermemory)
    {
    SDL_RemoveTimer(timers->firetimer);
    timers->firetimer = SDL_AddTimer(wavecontrol->firetime, firetime, NULL);
    timers->firetimermemory = wavecontrol->firetime;
    }
    if(timers->respawntimernewvalue != timers->respawntimermemory)
    {
        SDL_RemoveTimer(timers->respawntimer);
        timers->respawntimer = SDL_AddTimer(timers->respawntimernewvalue, respawntime, NULL);
        timers->respawntimermemory = timers->respawntimernewvalue;
    }
}
