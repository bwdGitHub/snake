#include <iostream>
#include <conio.h>
#include "Game.hpp"

Game instantiate(int argc, char** argv){
    // TODO
    // Validate inputs 
    // bad inputs will be problematic down the line
    // e.g. a negative int seems to be readable here 
    // Does it become a massive unsigned int by overflow
    // Or just remain negative?
    // Instead - just ban it.
    unsigned int height = 8;
    unsigned int width = 16;
    if(argc==3){
        height = std::stoi(argv[1]);
        width = std::stoi(argv[2]);
    }
    return Game(height,width);
}

int main(int argc, char** argv){
    Game game = instantiate(argc,argv);
    bool quit = false;
    while(!quit){
        game.render();
        // TODO:
        // This is a hacky way to listen for inputs.
        // curses/ncurses is a library that's meant to be good for this.
        char key = getch();
        if(key=='q'){
            quit = true;
        }
        else{
            game.update(key);
        }
    }
    return 0;
}