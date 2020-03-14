#ifndef _BLOOD_H_
#define _BLOOD_H_
#include "Global.h"
#include "GameTime.h"

#define BLOOD_DESPAWN_TIME 1
#define MAX_BLOODS 100

struct Blood {
	int x,y;
	int spawn;
	float despawn_time;
	float spawn_time ;
	float elapsed_time;
	SDL_Texture* texture;
};

void Blood_Spawn(Blood* blood, int x,int y, float despawn_time);
void Blood_Update(Blood* blood, float dt);
void Blood_Draw(Blood* blood);

#endif
