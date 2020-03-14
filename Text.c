#include "Text.h"

TTF_Font* _font;

int Text_SetFont(char* path, int size)
{
    int error = 0;
    if(_font != NULL)
        TTF_CloseFont(_font);
    _font = TTF_OpenFont(path,size);
    if(!_font){
        SDL_Log("Unable to load font:\nPath:%s\nSize:%d\n",path,size);
        error = 1;
    }
}

void Text_Print(int x, int y, char* line, SDL_Color* color)
{
	int error = 0;
	SDL_Color text_color = TEXT_DEFAULT_COLOR;
	if(color != NULL){
		text_color.r = color->r; text_color.b = color->b; text_color.g = color->g;
	}

	SDL_Surface* text_surface = TTF_RenderText_Solid(_font,line,text_color);
	if(!text_surface){
		SDL_Log("Unable to render text: %s",line);
		error = 1;
	} else {
		SDL_Texture* text_texture = SDL_CreateTextureFromSurface(renderer,text_surface);
		if(!text_texture){
			error = 1;
		} else {
			SDL_Rect dest;
			dest.x = x;			dest.y = y;
			dest.w = text_surface->w; 	dest.h = text_surface->h;

			SDL_RenderCopy(renderer,text_texture,NULL,&dest);
			
			SDL_DestroyTexture(text_texture);
		}
		SDL_FreeSurface(text_surface);
	} 

	if(error){
		SDL_Log("Unable to render line: %s\n",line);
	}
}
