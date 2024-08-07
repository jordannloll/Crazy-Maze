#include "game.h"

Game::Game() : game_map(MAP_WIDTH,MAP_HEIGTH), player1(MAP_WIDTH,MAP_HEIGTH), player2(MAP_WIDTH,MAP_HEIGTH), frame(0) {
    initialize_game();
};

void Game::initialize_game(){
    game_map.set_treasure_at(player1, player2); 
    graphics.init(player1,player2,game_map);
   
    turn = 1;
    timer = 0;
    game_state = 0;

    p_pointer = &player1;
    control_enemy = false;
    
}

void Game::run_game() {

    while (graphics.running() == true) {

        frame++;
        run_timer();

        player1.update(); player2.update();

        if (game_state == 2){controller.input_game(turn, control_enemy);}
        else controller.input_menu();

        if (game_state == 0){
            menu.title_screen(controller);
        }
        else if (game_state == 1){
            menu.selection_screen(controller);
        }
        else if (game_state == 2) {
            handle_turns();
        }
        else if (game_state == 3){
            menu.game_end_screen(controller);
        }
        
        menu.update_screen(game_state);

        if (game_state == 2) {graphics.update_game(player1, player2, game_map, control_enemy, turn);}
        else{
            graphics.update_menu(menu,game_state,menu.get_player1_skin_index(),menu.get_player2_skin_index(), menu.get_current_map());
        }
    }

    graphics.clean();
}
void Game::set_turns(int turn){
    if (turn == 1) {turn = 2;}
    else {turn = 1;}
}
void Game::handle_turns() {

    if (turn == 1) {p_pointer = &player1;}
    else if (turn == 2) {p_pointer = &player2;}

    if (p_pointer->get_if_moved() == false){
        
        p_pointer->handle_movement(controller.get_player_input(),game_map);
        
    } else {
        // if victory
        if(p_pointer->get_treasure()==true){
            std::cout << "winner: " << p_pointer << std::endl;
            graphics.running() == false;
        }
        if(p_pointer->hasDoublePlay()==true){
            p_pointer->useDoublePlay();
        }
        else {
            if (turn == 1) {turn = 2;}
            else {turn = 1;}
            control_enemy = false;
        }

        if (p_pointer->hasControlEnemy()==true) {
            control_enemy = true;
            p_pointer->useControlEnemy();
        }
        p_pointer->set_has_moved(false);

        timer = 1;
    }
}

void Game::run_timer(){
    if (timer >= 0){timer--;}
    else {timer = 0;}
}