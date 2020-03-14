#include "GameMath.h"

float Math_Random(){
	return ((float)rand())/RAND_MAX;
}

float Math_RandomRange(float from, float to)
{
	return Math_Lerp(from,to,Math_Random());
}

float Math_FixRange(float val, float min, float max)
{
	return fmin(fmax(min,val),max);
}

float Math_Lerp(float from, float to, float t)
{
	return from*(1-t) + to*t;
}

float Math_Length(float dx, float dy)
{
	return sqrtf(dx*dx + dy*dy);
}
