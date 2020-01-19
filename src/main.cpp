#include <iostream>
#include <conio.h>
#include "Game.hpp"
#include <curses.h>

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
    // For now just pass a window to the game, and see if I can quit from there
    Game game = instantiate(argc,argv);
    // Standard initialization
    initscr();
    clear();
    noecho();
    cbreak();
    WINDOW *win = newwin(game.height,game.width,0,0);        
    keypad(win,TRUE);
    box(win,0,0);
    wrefresh(win);
    curs_set(0);
    // TODO - get speed from input arguments.
    wtimeout(win,100);

    bool cursesQuit = false;
    while(!cursesQuit){
        char input = wgetch(win);
        cursesQuit = input=='q';
        game.update(input);
        game.cursesRender(win,input);                         
    }
    refresh();
    endwin();
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