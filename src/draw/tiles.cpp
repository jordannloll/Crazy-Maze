#include "tiles.h"
#include "iostream"

void Tiles::init(std::vector<SDL_Texture*> grounds, int TILE_SIZE, int SCREEN_W, int SCREEN_H, int X_OFF, int Y_OFF){
    
    tile_tex = grounds[0];
    tile_size = TILE_SIZE;
    screen_width = SCREEN_W;
    screen_height = SCREEN_H;

    x_offset = X_OFF;
    y_offset = Y_OFF;

    tile_rect.x = 0; tile_rect.y = 0;
    tile_rect.w = tile_size; tile_rect.h = tile_size;

    tile_spr.x = 0; tile_spr.y = 0;
    tile_spr.w = 16; tile_spr.h = 16;

}

void Tiles::load_power_ups(SDL_Renderer* ren){

    jump_wall.init("assets/items/pw_jump.png", ren, tile_size);
    double_move.init("assets/items/pw_double_move.png", ren, tile_size);
    control_enemy.init("assets/items/pw_control_enemy.png", ren, tile_size);
    portal.init("assets/items/portal.png", ren, tile_size);
}

void Tiles::set_tile_set(std::vector<SDL_Texture*> grounds, int index){
    tile_tex = grounds[index];
}

void Tiles::draw(SDL_Renderer* ren, Game_map& game_map){

    double_move.play_animation();
    control_enemy.play_animation();
    jump_wall.play_animation();
    portal.play_animation();
    
    
    for (int i = 0; i < game_map.get_height(); ++i){
        for (int j = 0; j < game_map.get_width(); ++j){

            //Floor tile
            tile_rect.x = (j+x_offset)*tile_size; 
            tile_rect.y = (i+y_offset)*tile_size;
            tile_spr.x = 0;

            SDL_RenderCopy(ren, tile_tex, &tile_spr, &tile_rect);

            if (game_map.get_map_index(i,j).hasBottomWall()){
                tile_spr.x = 16;
                SDL_RenderCopy(ren, tile_tex, &tile_spr, &tile_rect);
            }
            if (game_map.get_map_index(i,j).hasTopWall()){
                tile_spr.x = 32;
                SDL_RenderCopy(ren, tile_tex, &tile_spr, &tile_rect);
            }
            if (game_map.get_map_index(i,j).hasRightWall()){
                tile_spr.x = 48;
                SDL_RenderCopy(ren, tile_tex, &tile_spr, &tile_rect);
            }
            if (game_map.get_map_index(i,j).hasLeftWall()){
                tile_spr.x = 64;
                SDL_RenderCopy(ren, tile_tex, &tile_spr, &tile_rect);
            }
            if (game_map.get_map_index(i,j).get_double_play() == true){
                double_move.update(tile_rect.x,tile_rect.y);
                double_move.render(ren);
            }
            if (game_map.get_map_index(i,j).getControlEnemy() == true){
                control_enemy.update(tile_rect.x,tile_rect.y);
                control_enemy.render(ren);
            }
            if (game_map.get_map_index(i,j).getJumpWall() == true){
                jump_wall.update(tile_rect.x,tile_rect.y);
                jump_wall.render(ren);
            }

            if (game_map.get_map_index(i,j).getPortal() == true){
                portal.update(tile_rect.x,tile_rect.y);
                portal.render(ren);
            }

        }
    }
   
}