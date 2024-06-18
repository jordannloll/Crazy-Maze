#include "player_draw.h"

void Player_draw::init(const char* texture, SDL_Renderer* renderer, int tile, int x_off, int y_off){

    player_tex = load_texture(texture,renderer);

    tile_size = tile;
    p_offset = (4)*(tile_size/16);

    move_speed = BASE_MOVEMENT_SPEED*(tile_size/16);
    jump_height = BASE_JUMP_HEIGHT*(tile_size/16);
    gravity = BASE_GRAVITY*(tile_size/16);
    downwards_speed = 0;

    width = tile;
    height = tile+p_offset;

    frame_width = P_FRAME_WIDTH;
    frame_height = P_FRAME_HEIGHT;


    x_offset = x_off; y_offset = y_off;
    x = 0; y = 0, z = 0;
    z = 0;

    set_rect(player_rect, 0, 0, width, height);
    set_rect(player_spr, 0, 0, frame_width, frame_height);

    image_frame = 0;
    image_speed = 8;
    image_length = 4;
    image_index = 0;
    action_index = 0;
    facing_direction = 's';
    is_jumping = false;

    last_jump_powers = 0;

}

void Player_draw::update(int next_x, int next_y, int new_jump_powers){

    //JUMP
    if (new_jump_powers < last_jump_powers){jump();}
    last_jump_powers = new_jump_powers;

    //SPRITES
    if (x > next_x*tile_size) {x-=move_speed; facing_direction = 'l';}
    else if (x < next_x*tile_size) {x+=move_speed; facing_direction = 'r';}

    if (y > next_y*tile_size) {y-=move_speed; facing_direction = 'u';}
    else if (y < next_y*tile_size) {y+=move_speed; facing_direction = 'd';}

    action_manager();

    //ANIMATION SPEEDS
    if (x == next_x*tile_size && y == next_y*tile_size) {if (image_frame == 0){image_speed = IDLE_IMAGE_SPEED;}}
    else {image_speed = WALKING_IMAGE_SPEED;}

    animation(image_frame, image_index, image_speed, image_length);

    player_rect.x = (x+(x_offset*tile_size));
    player_rect.y = ((y+(y_offset*tile_size))-p_offset-P_ELEVATION)+int(z);

    player_spr.x = image_frame*P_FRAME_WIDTH;
    player_spr.y = action_index*P_FRAME_HEIGHT;

    vertical_movement();

}

void Player_draw::render(SDL_Renderer* renderer){
    SDL_RenderCopy(renderer, player_tex, &player_spr, &player_rect);
}

void Player_draw::jump(){
    if (z==0) {is_jumping = true;}
}

void Player_draw::vertical_movement(){
    
    if (is_jumping){
        //Up
        z -= jump_height;

        //Fall
        downwards_speed += gravity;
        z += downwards_speed;

        if (z > 0){ //Grounded
            z = 0;
            downwards_speed = 0;
            is_jumping = false;
            
        }
    }
}


void Player_draw::set_skin(const char* texture , SDL_Renderer* renderer){
    player_tex = load_texture(texture,renderer);
}

void Player_draw::action_manager(){
    switch(facing_direction){
    case 'l':
        if (is_jumping == false) {action_index = WALK_LEFT;}
        else {action_index = JUMP_LEFT;}
        break;
    case 'r':
        if (is_jumping == false) {action_index = WALK_RIGHT;}
        else {action_index = JUMP_RIGHT;}
        break;
    case 'u':
        if (is_jumping == false) {action_index = WALK_UP;}
        else {action_index = JUMP_UP;}
        break;
    case 'd':
        if (is_jumping == false) {action_index = WALK_DOWN;}
        else {action_index = JUMP_DOWN;}
        break;
    }
}