#ifndef TEXTURE_LOADER_H
#define TEXTURE_LOADER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

SDL_Texture* load_texture(const char* file, SDL_Renderer* renderer);
void set_rect(SDL_Rect& rect, int x, int y, int w, int h);
    
#endif