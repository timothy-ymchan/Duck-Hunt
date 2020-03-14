#ifndef _DUCK_H_
#define _DUCK_H_

#define DUCK_ANIMATION_TIME 1

struct Duck {
	float x,y,z;
	float vx;
	int dead;
	SDL_Texture* texture;
	SDL_Rect hitbox;
	float spawn_time;
};

void Duck_Spawn(Duck* duck);
void Duck_Draw(Duck* duck);
void Duck_Update(Duck* duck, float dt);
int Duck_IsHit(float x, float y, Duck* duck);
int Duck_CompareAsc(const void* duck1, const void* duck2); //qsort requirement
int Duck_CompareDsc(const void* duck1, const void* duck2); //qsort requirement
#endif
