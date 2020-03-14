#ifndef _GAME_VARIABLES_H_
#define _GAME_VARIABLES_H_
#include "Duck.h"
#include "Aim.h"
#include "Blood.h"

#ifndef MAX_DUCKS
	#define MAX_DUCKS 5
#endif
#ifndef MAX_BLOODS
	#define MAX_BLOODS 100
#endif

extern Duck ducks[MAX_DUCKS];
extern Aim aim;
extern Blood bloods[MAX_BLOODS];
extern int score;

#endif
