#define SDL_MAIN_HANDLED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

#include "Global.h"
#include "GameTime.h"
#include "GameMath.h"
#include "Duck.h"
#include "Aim.h"
#include "Text.h"
#include "Blood.h"
#include "GameVariables.h"

/* Utilities */
SDL_Texture* Util_LoadTexture(char* path);

/* Game Variables */
int loop = 1;

SDL_Texture* bg_texture[5];
SDL_Texture* blood_texture;
SDL_Texture* duck_texture;
Duck ducks[MAX_DUCKS] = {0};
Blood bloods[MAX_BLOODS] = {0};
Aim aim = {0};

int score = 0;

/* Game Functions */
int Game_Init();
void Game_Quit();
void Game_Draw();
void Game_Update();
void Game_HandleEvent();


void Background_Draw();

/* Main Function */
float last_frame = 0;
float this_frame = 0;
int fps;

int main(int argc, char* args[])
{
	loop = !Game_Init();
	while(loop){

		

		if(Timer_ReachDrawTime(60)){

			/* Event Handling */
			Game_HandleEvent();

			/* Update */
			Game_Update();

			/* Draw */
			Game_Draw();
		}
		
	}
	Game_Quit();
}

/* Utility */

SDL_Texture* Util_LoadTexture(char* path){
	SDL_Texture* texture = NULL;
	SDL_Surface* image;
	image = IMG_Load(path);
	if(!image){
		SDL_Log("IMG_Load: %s %s\n",path,IMG_GetError());
		texture = NULL;
	} else {
		//SDL_SetColorKey(image,SDL_TRUE,SDL_MapRGB(image->format,0xFF*0,0xFF*0,0xFF*0));
		texture = SDL_CreateTextureFromSurface(renderer,image);
		if(texture == NULL){
			SDL_Log("Unable to create texture from %s\nSDL_Error: %s\n",path,SDL_GetError());
		}
		SDL_FreeSurface(image);
	}
	return texture;
}

/* Game Functions */

int Game_Init(){
	int error = 0;
	/* Initialize SDL */
	if(SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO) != 0){
		SDL_Log("Unable to initialize SDL: %s\n",SDL_GetError());
		error = 1;
	}

	/* Initialize Window */
	if(Window_Init(SCREEN_WIDTH,SCREEN_HEIGHT,"Duck Hunt")){
		SDL_Log("Unable to create window / renderer: %s\n",SDL_GetError());
		error = 1;
	}

	/* Initialize SDL2_Img */
	int imgFlags = IMG_INIT_PNG;
	if(IMG_Init(imgFlags) != imgFlags){
		SDL_Log("Unable to initialize SDL2_IMG: %s\n",IMG_GetError());
		error = 1;
	}

	/* Initialize SDL2_ttf */
	if(TTF_Init() == -1){
		SDL_Log("Unable to initialize SDL2_ttf: %s\n",TTF_GetError());
		error = 1;
	}

	/* Initialize Game Time */
	Timer_Init();

	/* Load Images */
	duck_texture = Util_LoadTexture("./asset/duck.png");
	blood_texture = Util_LoadTexture("./asset/blood.png");
	bg_texture[0] = Util_LoadTexture("./asset/background/parallax-mountain-bg.png");
	bg_texture[1] = Util_LoadTexture("./asset/background/parallax-mountain-montain-far.png");
	bg_texture[2] = Util_LoadTexture("./asset/background/parallax-mountain-mountains.png");
	bg_texture[3] = Util_LoadTexture("./asset/background/parallax-mountain-trees.png");

	/* Load Font */
	Text_SetFont("./asset/OdibeeSans-Regular.ttf",24);


	/* Initialize Aim */
	aim.x = SCREEN_WIDTH/2;
	aim .y = SCREEN_HEIGHT/2;
	aim.texture = Util_LoadTexture("./asset/aim.png");

	
	/* Initialize Blood */
	int j;
	for(j=0;j<MAX_BLOODS;j++){
		bloods[j].texture = blood_texture;
		bloods[j].spawn = 0;
	}

	/* Initialize Ducks */
	int i;
	srand(time(NULL));
	for(i=0;i<MAX_DUCKS;i++)
	{
		ducks[i].texture = duck_texture;
		Duck_Spawn(&ducks[i]);
	}

	/* Initalize Score */
	score = 0;
	return error;
}

void Game_Quit(){
	Window_Quit();
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}


void Game_HandleEvent(){
	while(SDL_PollEvent(&event) != 0){
	//if(SDL_WaitEvent(&event) != 0){
		if(event.type == SDL_QUIT){
			loop = 0;
		} else if(event.type == SDL_MOUSEMOTION){
			aim.target_x = event.motion.x;
			aim.target_y = event.motion.y;
		} else if(event.type == SDL_MOUSEBUTTONDOWN){
			if(event.button.button == SDL_BUTTON_LEFT){
				aim.shoot = 1;
			}
		}
	}
}
	

void Game_Update() {
	float dt = Timer_DeltaTime();
	int i;

	for(i=0;i<MAX_DUCKS;i++)
		Duck_Update(&ducks[i],dt);
	
	qsort(ducks,MAX_DUCKS,sizeof(Duck),Duck_CompareAsc);
	Aim_Update(&aim,dt);
	
	for(i=0;i<MAX_BLOODS;i++)
		Blood_Update(&bloods[i],dt);
	
	this_frame = Timer_GetTime();
	fps = 1.0f/(this_frame-last_frame);
	last_frame = this_frame;
}

void Game_Draw() {
	//Clear screen
	SDL_RenderClear(renderer);
	
	//Draw Background
	Background_Draw();

	//Draw Ducks
	int i;
	qsort(ducks,MAX_DUCKS,sizeof(Duck),Duck_CompareDsc);
	for(i=0;i<MAX_DUCKS;i++)
		Duck_Draw(&ducks[i]);

	//Draw Aim
	Aim_Draw(&aim);
	
	//Draw Blood
	for(i=0;i<MAX_BLOODS;i++)
		Blood_Draw(&bloods[i]);	

	//Draw Score
	char buffer[51];
	sprintf(buffer,"Score: %d",score);
	Text_Print(10,10,buffer,NULL);
	
	// FPS Meter
	sprintf(buffer,"FPS: %d",fps);
	Text_Print(550,10,buffer,NULL);
	
	//Update screen
	SDL_RenderPresent(renderer);
}


void Background_Draw()
{
	
	int width, height;	
	SDL_Rect src,dest;

	/* Sun set */
	SDL_QueryTexture(bg_texture[0],NULL,NULL,&width,&height);
	
	const float screen_aspect = ((float)SCREEN_WIDTH)/SCREEN_HEIGHT;	

	width = (int) Math_FixRange(screen_aspect*height,0,width);
	
	src.x = (int)width*0.15;	src.y = 0;
	src.w = width;			src.h = height;
	
	SDL_RenderCopy(renderer,bg_texture[0],&src,NULL);


	/* Back Mountain */
	SDL_QueryTexture(bg_texture[1],NULL,NULL,&width,&height);

	height = (int) Math_FixRange(width/screen_aspect,0,height);

	src.x = 0;		src.y = 0;
	src.w = width;		src.h = height;

	SDL_RenderCopy(renderer,bg_texture[1],&src,NULL);

	/* Front Mountain*/
	SDL_QueryTexture(bg_texture[2],NULL,NULL,&width,&height);
	
	width = (int) Math_FixRange(screen_aspect*height,0,width);
	src.x = 0;		src.y = 0;
	src.w = width;		src.h = height;


	//dest.x = 0;		dest.y = SCREEN_HEIGHT*0;
	//dest.w = SCREEN_WIDTH;	dest.h = SCREEN_HEIGHT*1;
	SDL_RenderCopy(renderer,bg_texture[2],&src,NULL);	

	/* Trees */
	SDL_QueryTexture(bg_texture[3],NULL,NULL,&width,&height);
	
	width = (int) Math_FixRange(screen_aspect*height,0,width);
	src.x = 0;		src.y = 0;
	src.w = width;		src.h = height;

	SDL_RenderCopy(renderer,bg_texture[3],&src,NULL);
}
