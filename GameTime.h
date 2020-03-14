#ifndef _GAME_TIME_H_
#define _GAME_TIME_H_
#include "Global.h"

extern Uint32 prevTime;

void Timer_Init();
float Timer_DeltaTime();
float Timer_GetTime();
int Timer_ReachDrawTime(int fps);

#endif
