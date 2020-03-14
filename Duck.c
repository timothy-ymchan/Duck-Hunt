#include "Global.h"
#include "Duck.h"
#include <stdlib.h>
#include "GameMath.h"
#include "GameTime.h"

void Duck_Spawn(Duck* duck){

	duck->y = Math_RandomRange(0,SCREEN_HEIGHT/3);
	duck->dead = 0;
	duck->z = Math_Random();
	duck->vx = 100.0f*Math_RandomRange(1.0f,2.0f);
	duck->vx *= (Math_Random() > 0.5)? -1:1;	
	duck->x = (duck->vx > 0)? 0: SCREEN_WIDTH;

	//const int min_width = 80; const int min_height = 53;
	//const int max_width = 100; const int max_height = 66;
	
	int w,h;
	SDL_QueryTexture(duck->texture,NULL,NULL,&w,&h);
	const float aspect = ((float)h)/w;

	const int min_width = 80; const int min_height = (int)80*aspect;
	const int max_width = 100; const int max_height = (int)100*aspect;

	float z = duck->z;	
	int width = (int)  Math_Lerp(max_width,min_width,z);	
	int height = (int) Math_Lerp(max_height,min_height,z);	

	
	duck->hitbox.x = duck->hitbox.y = 0;
	duck->hitbox.w = width;
	duck->hitbox.h = height;	

	duck->spawn_time = Timer_GetTime();	
}

void Duck_Draw(Duck* duck)
{
	if(!duck->dead){
		const int sprite_width = 762;
		const int sprite_height = 605;


		float t = (Timer_GetTime() - duck->spawn_time)/DUCK_ANIMATION_TIME;
		if(t>1)
			duck->spawn_time = Timer_GetTime();
		t -= (int) t;

		

		int frame = (int) Math_Lerp(0,4,t);
		
		int i = frame / 2,		j = frame % 2; 
		//int i = 0, j = 0;

		SDL_Rect src;
		src.x = i*sprite_width;		src.y = j*sprite_height;
		src.w = sprite_width;		src.h = sprite_height;

		SDL_Rect dest; 
		dest.x = (int) duck->x;		dest.y = (int) duck->y;
		dest.w = duck->hitbox.w;	dest.h = duck->hitbox.h;

		SDL_RendererFlip flip;	
		if(duck->vx < 0)
			flip = (SDL_RendererFlip) SDL_FLIP_VERTICAL;
		else
			flip = (SDL_RendererFlip) SDL_FLIP_NONE;
		
		SDL_RenderCopyEx(renderer,duck->texture,&src,&dest,0,NULL,flip);

		
		/*float x0 = duck->x + duck->hitbox.x;
		float y0 = duck->y + duck->hitbox.y;

		dest.x = (int)x0;		dest.y = (int)y0;	

		SDL_SetRenderDrawColor(renderer,255,255,255,255);
		SDL_RenderDrawRect(renderer,&dest);
		SDL_SetRenderDrawColor(renderer,0,0,0,0);*/
	}
}


void Duck_Update(Duck* duck, float dt)
{
	if(duck->dead){
		Duck_Spawn(duck);
	} else {
		const float v = duck->vx;
		duck->x += v*dt;
		if(duck->x > SCREEN_WIDTH || duck->x < 0)
			duck->dead = 1;
	}

}

int Duck_IsHit(float x, float y, Duck* duck) {
	float x0 = duck->x + duck->hitbox.x;
	float y0 = duck->y + duck->hitbox.y;
	float x1 = x0 + duck->hitbox.w;
	float y1 = y0 + duck->hitbox.h;

	return (x0<= x && x<=x1 && y0<=y && y <= y1);
}


int Duck_CompareAsc(const void* duck1, const void* duck2){
	const Duck* d1 = (Duck*) duck1;
	const Duck* d2 = (Duck*) duck2;

	if(d1->z > d2->z)
		return +1;
	else if(d1->z < d2->z)
		return -1;
	else
		return 0;
}

int Duck_CompareDsc(const void* duck1, const void* duck2){

	const Duck* d1 = (Duck*) duck1;
	const Duck* d2 = (Duck*) duck2;

	if(d1->z > d2->z)
		return -1;
	else if(d1->z < d2->z)
		return +1;
	else
		return 0;
}
