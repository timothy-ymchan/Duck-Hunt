#include "GameTime.h"

Uint32 prevTime = 0;
float prevDraw = 0;

void Timer_Init() {
    prevTime = 0;
    prevDraw = 0;
}

float Timer_DeltaTime() {
    Uint32 curTime = SDL_GetTicks();
    float deltaTime = ((float)(curTime-prevTime))/(1000.0f);
    prevTime = curTime;
    return deltaTime;
}

float Timer_GetTime(){
    Uint32 curTime = SDL_GetTicks();
    return (float)curTime/1000.0f;
}

int Timer_ReachDrawTime(int fps){
    const float threshold = 1.0f/fps;
    if(Timer_GetTime() - prevDraw > threshold){
        prevDraw = Timer_GetTime();
        return 1;
    }
    return 0;
}
