#ifndef _GLOBAL_H_
#define _GLOBAL_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

extern SDL_Window* window;
extern SDL_Renderer* renderer;
extern SDL_Event event;


/* SDL Functions */
int Window_Init(int width, int height,char* title);
void Window_Quit();

#endif
