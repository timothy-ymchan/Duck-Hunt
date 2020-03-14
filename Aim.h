#ifndef _AIM_H_
#define _AIM_H_
#include "Global.h";

#define AIM_WIDTH 50
#define AIM_HEIGHT 50

struct Aim {
	float x,y;
	float target_x, target_y;
	int shoot;
	SDL_Texture* texture;
};

void Aim_Draw(Aim* aim);

void Aim_Update(Aim* aim, float dt);
#endif
