#ifndef TILES_H
#define TILES_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "../texture_loader.h"
#include "../game_map.h"
#include "item_draw.h"
#include "vector"

class Tiles{

public:
    Tiles(){}
    ~Tiles(){}

    void init(std::vector<SDL_Texture*> grounds, int TILE_SIZE, int SCREEN_W, int SCREEN_H, int MAP_W, int MAP_H);
    void load_power_ups(SDL_Renderer* ren);
    void set_tile_set(std::vector<SDL_Texture*> grounds, int index);
    void draw(SDL_Renderer* ren, Game_map& game_map);
    
private:

    SDL_Texture * tile_tex;
    SDL_Rect tile_rect;
    SDL_Rect tile_spr;

    Item_draw jump_wall;
    Item_draw control_enemy;
    Item_draw double_move;
    Item_draw portal;


private:
    int x_offset, y_offset;
    int tile_size;
    int screen_width, screen_height;
};


#endif