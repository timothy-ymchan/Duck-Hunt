#ifndef _GAME_MATH_H_
#define _GAME_MATH_H_
#include <math.h>
#include <stdlib.h>

float Math_Random();
float Math_RandomRange(float from, float to);
float Math_FixRange(float val, float min, float max);
float Math_Lerp(float from, float to, float t);
float Math_Length(float dx, float dy);

#endif
