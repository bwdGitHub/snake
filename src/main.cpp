#include <iostream>
#include "Game.cpp"

class Snake {};

class Apple {};

int main(int argc, char** argv){
    Game game = Game(10,20);
    game.render();
    return 0;
}