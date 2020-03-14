#include "Global.h"
#include "Aim.h"
#include "Duck.h"
#include <math.h>
#include "GameMath.h"
#include "GameVariables.h"

void Aim_Draw(Aim* aim){
	const int width = AIM_WIDTH;
       	const int height = AIM_HEIGHT;

	SDL_Rect dest;
	dest.x = (int) aim->x-width/2; 	dest.y = (int) aim->y-height/2;
	dest.w = width; 		dest.h = height;
	
	SDL_RenderCopy(renderer,aim->texture,NULL,&dest);
}

void Aim_Update(Aim* aim, float dt){
	const float threshold = 10.0;
	float deltaX = -(aim->x - aim->target_x); 
	float deltaY = -(aim->y - aim->target_y);
	const float dist = Math_Length(deltaX,deltaY);
	
	/* Move aim to target */
	if(dist < threshold ){
		//If close enough, Click to target
		aim->x = aim->target_x;
		aim->y = aim->target_y;
	} else {
		const float theta = atan2(deltaY,deltaX);

		const float v_min = 500.0f;	const float v_max = 800.0f;
		const float k = 10.0f;

		const float v = Math_FixRange(k*dist,v_min,v_max);
		const float vx = v*cos(theta);	const float vy = v*sin(theta);
		
		aim->x += vx*dt;
		aim->y += vy*dt;
	}

	/* Handle Shooting */

	if(aim->shoot){
		int i,j;
		for(i=0;i<MAX_DUCKS;i++){
			//SDL_Log("Duck %d: %f\n",i+1,ducks[i].z);
			if(Duck_IsHit(aim->x,aim->y,&ducks[i])){
				ducks[i].dead = 1;
				score ++; //Add score
				
				//Spawn Blood
				for(j=0;j<MAX_BLOODS;j++){
					if(bloods[j].spawn == 0){
						Blood_Spawn(&bloods[j],aim->x,aim->y,BLOOD_DESPAWN_TIME);
						j=MAX_BLOODS; //Spawn not more than one blood
					}
				}
				
				i=MAX_DUCKS; //Kill no more than one duck
			}
		}
		//SDL_Log("Shoot At: (%f,%f)\n",aim->x,aim->y);
		aim->shoot = 0;
	}
}
