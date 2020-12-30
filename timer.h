#ifndef TIMER_H_INCLUDED
#define TIMER_H_INCLUDED

Uint32 projectiletime(Uint32 ms, void *param);
Uint32 movetime(Uint32 ms, void *param);
Uint32 firetime(Uint32 ms, void *param);
Uint32 enemyfiretime(Uint32 ms, void *param);
Uint32 respawntime(Uint32 ms, void *param);
void refreshTimers(Timers *timers, WaveControl *wavecontrol);

#endif // TIMER_H_INCLUDED
