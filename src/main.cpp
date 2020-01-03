#include <iostream>
#include "Game.hpp"

class Snake {};

class Apple {};

int main(int argc, char** argv){
    Game game = Game(10,15);   
    game.render();
    return 0;
}