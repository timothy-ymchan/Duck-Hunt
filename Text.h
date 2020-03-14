#ifndef _TEXT_H_
#define _TEXT_H_
#include "Global.h"

#define TEXT_DEFAULT_COLOR {255,255,255}

extern TTF_Font* _font;

int Text_SetFont(char* path,int size);
void Text_Print(int x, int y,char* line,SDL_Color* color);

#endif
