#include "Global.h"

/* SDL Variables */
SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
SDL_Event event = {0};

/* SDL Functions */

int Window_Init(int width, int height,char* title)
{
	int error = 0;
	if(SDL_CreateWindowAndRenderer(width,height,NULL,&window,&renderer)){
		error = 1;
	} else {
		SDL_SetWindowTitle(window,title);
		//SDL_ShowCursor(SDL_DISABLE);
		SDL_EventState(SDL_JOYAXISMOTION,SDL_DISABLE);
		SDL_EventState(SDL_JOYBALLMOTION,SDL_DISABLE);
		SDL_EventState(SDL_JOYHATMOTION,SDL_DISABLE);
		SDL_EventState(SDL_JOYBUTTONDOWN,SDL_DISABLE);
		SDL_EventState(SDL_JOYBUTTONUP,SDL_DISABLE);
		SDL_EventState(SDL_JOYDEVICEADDED,SDL_DISABLE);
		SDL_EventState(SDL_JOYDEVICEREMOVED,SDL_DISABLE);
	
	}
	return error;
}


void Window_Quit(){
	if(renderer)
		SDL_DestroyRenderer(renderer);
	if(window)
		SDL_DestroyWindow(window);

}
