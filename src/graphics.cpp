#include "graphics.h"

Graphics::Graphics(): menu_draw(SCREEN_HEIGHT,SCREEN_HEIGHT){}
Graphics::~Graphics(){}

void Graphics::init(Player& player1, Player& player2, Game_map& game_map){
    SDL_Init (SDL_INIT_EVERYTHING);

    window = SDL_CreateWindow(GAME_NAME,SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,SCREEN_WIDTH,SCREEN_HEIGHT, SDL_WINDOW_ALLOW_HIGHDPI);
    renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_PRESENTVSYNC);
    SDL_SetRenderDrawColor(renderer, 255,255,255,255);

    SDL_Surface * icon = IMG_Load("assets/icon.bmp");
    SDL_SetWindowIcon(window,icon);
    SDL_FreeSurface(icon);

    x_draw_offset = ((SCREEN_WIDTH/2) - (game_map.get_width()/2)*TILE)/TILE;
    y_draw_offset = ((SCREEN_HEIGHT/2) - (game_map.get_height()/2)*TILE)/TILE;


    player1_draw.init("assets/skins/char00.png",renderer, 1, TILE,x_draw_offset,y_draw_offset);
    player2_draw.init("assets/skins/char01.png",renderer, 2, TILE,x_draw_offset,y_draw_offset);

    background.init(TILE, SCREEN_WIDTH, SCREEN_HEIGHT);
    tiles.init(TILE, SCREEN_WIDTH, SCREEN_HEIGHT, x_draw_offset, y_draw_offset);

    map_index = "poison";

    background.load_bg("assets/maps/poison/background.png",renderer);
    tiles.load_tile_set("assets/maps/poison/ground.png",renderer);

    is_running = true;
}

void Graphics::update_title(Menu& menu){
    event();
    render_title(menu);
}

void Graphics::update_selection(Menu& menu){
    event();
    render_selection(menu);
}

void Graphics::update_game(Player& player1, Player& player2, Game_map& game_map, bool control_enemy, int turn){
    
    event();

    player1_draw.update(player1.get_x(), player1.get_y(), player1.get_jump_wall_power(), control_enemy, turn);
    player2_draw.update(player2.get_x(), player2.get_y(), player2.get_jump_wall_power(), control_enemy, turn);

    render_game(game_map);

}

void Graphics::update_end(Menu& menu){
    event();
    render_end(menu);
}

void Graphics::render_title(Menu& menu){
    SDL_RenderClear(renderer);

    menu_draw.draw_title(renderer);

    SDL_RenderPresent(renderer);
}

void Graphics::render_selection(Menu& menu){
    SDL_RenderClear(renderer);

    menu_draw.draw_selection(renderer);
    
    SDL_RenderPresent(renderer);
}


void Graphics::render_game(Game_map& game_map){

    SDL_RenderClear(renderer);

    background.draw(renderer);
    tiles.draw(renderer, game_map);

    if (player1_draw.get_y() > player2_draw.get_y()){
        player2_draw.render(renderer);
        player1_draw.render(renderer);
    }
    else{
        player1_draw.render(renderer);
        player2_draw.render(renderer);
    }


    SDL_RenderPresent(renderer);
}

void Graphics::render_end(Menu& menu){
    SDL_RenderClear(renderer);

    menu_draw.draw_end(renderer);

    SDL_RenderPresent(renderer);
}


void Graphics::event(){

    if (SDL_PollEvent( &window_event )){

        if (SDL_QUIT == window_event.type){
            is_running = false;
        }
    }
}

void Graphics::clean(){
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
}