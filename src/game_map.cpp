#include "game_map.h"
#include "iostream"


Game_map::Game_map(int width, int height) : height(height), width(width) {

    std::srand(std::time(0));
    map.resize(height,std::vector<Cell>(width));

    for (auto& row : map) {
        for (Cell& cell : row) { 

            cell.update_Powers(height,width);

            if(cell.getPortal()==true){
                int other_X= 0 + std::rand()%(height);
                int other_Y= 0 + std::rand()%(width);
                map[other_X][other_Y].setPortal(true);
            }
        }
    }

     for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            Cell& cell = map[i][j];
            cell.update_Powers(height, width);

            
            std::cout << "  Portal: " << (cell.getPortal() ? "Yes" : "No") << std::endl;
            std::cout << "  Double Play: " << (cell.getDP() ? "Yes" : "No") << std::endl;
            std::cout << "  Control Enemy: " << (cell.getControlEnemy() ? "Yes" : "No") << std::endl;
            std::cout << "  Jump Wall: " << (cell.getJumpWall() ? "Yes" : "No") << std::endl;
            printf("\n");
        }
    }

    init_map(0,0);

}

Game_map::~Game_map() {

    for(auto& tMap: map){
        tMap.clear();
    }
    map.clear();

}

void Game_map::init_map(int x,int y)
{
    int randMove;
    int newX;
    int newY;

    map[x][y].setVisited(true);

    for(int i=0;i<4;i++){
            randMove=0 + std::rand()%(4);


        if(randMove==0){ //se mueve a la izquierda
            newX=x;
            newY=y-1;
        }else if(randMove==1){//se mueve a la derecha
            newX=x;
            newY=y+1;
        }else if(randMove==2){//mueve arriba
            newX=x-1;
            newY=y;
        }else if(randMove==3){//mueve abajo
            newX=x+1;
            newY=y;
        }

        if(newX>=0 && newY>=0 && newX<this->height && newY<this->width && (map[newX][newY].isVisited())==false){

            if(newX<x){//arriba
                
                map[x][y].setTopWall(false);
                map[newX][newY].setBottomWall(false);

            }else if(newX>x){//abajo
                map[x][y].setBottomWall(false);
                map[newX][newY].setTopWall(false);

            }else if(newY<y){//izquierda
                map[x][y].setLeftWall(false);
                map[newX][newY].setRightWall(false);

            }else if(newY>y){//derecha
                map[x][y].setRightWall(false);
                map[newX][newY].setLeftWall(false);

            }
            init_map(newX,newY);
        }
    }
}



void Game_map::printMap2()
{/*
    for (const auto& row : map) {
        for (const Cell& cell : row) {
            if (cell.hasTopWall()) std::cout << " _";
            else std:: cout << "  ";
        }
        std::cout << std::endl;
        for (const Cell& cell : row) {
            if (cell.hasLeftWall()) std:: cout << "|";
            else std::cout << " ";
            std::cout << " ";
        }
        if (row.back().hasRightWall()) std::cout << "|";
        std::cout << std::endl;
    }
    */
}