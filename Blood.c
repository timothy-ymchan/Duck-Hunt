#include "Global.h"
#include "Blood.h"
#include "GameMath.h"
#include <math.h>

void Blood_Spawn(Blood* blood, int x, int y, float despawn_time){
	blood->x = x;	blood->y = y;
	blood->despawn_time = despawn_time;
	blood->spawn_time = Timer_GetTime();
	blood->spawn = 1;
}

void Blood_Update(Blood* blood, float dt){
	if(blood->spawn){
		float deltaTime = Timer_GetTime() - blood->spawn_time;
	
		if(deltaTime > blood->despawn_time){
			blood->spawn = 0;
			blood->elapsed_time = 1.0f;
		}

		blood->elapsed_time = deltaTime/blood->despawn_time;
	}
}

void Blood_Draw(Blood* blood){
	if(blood->spawn){
		float t = blood->elapsed_time;
		t = -t*(t-2);//ease out

		int frame = (int) Math_Lerp(1,16,t);	
		
		const int i = frame%4;		const int j = frame/4;
		const int frame_size = 512;
		SDL_Rect src;
		src.x = frame_size*i;		src.y =frame_size*j;
		src.w = frame_size;		src.h = frame_size;
		
		
		const int display_size = 200;
		SDL_Rect dest;
		dest. x = (int) blood->x - display_size/2;	dest.y = (int) blood->y -display_size/2;
		dest.w = display_size;				dest.h = display_size;

		SDL_RenderCopy(renderer,blood->texture,&src,&dest);
	}
}



