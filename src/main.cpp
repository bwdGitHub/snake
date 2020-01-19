#include <iostream>
#include <conio.h>
#include "Game.hpp"
#include <curses.h>

Game instantiate(int argc, const char** argv){
    // TODO
    // Validate inputs 
    // bad inputs will be problematic down the line
    // e.g. a negative int seems to be readable here 
    // Does it become a massive unsigned int by overflow
    // Or just remain negative?
    // Instead - just ban it.
    unsigned int height = 8;
    unsigned int width = 16;
    if(argc>=3){
        height = std::stoi(argv[1]);
        width = std::stoi(argv[2]);
    }
    return Game(height,width);
}

WINDOW* initializeGameWindow(int h,int w, double delay){
    WINDOW *win = newwin(h,w,0,0);        
    keypad(win,TRUE);
    box(win,0,0);
    wrefresh(win);
    curs_set(0);
    // TODO - get speed from input arguments.
    wtimeout(win,delay);
    return win;
}

int main(const int argc, const char** argv){
    // Make argc and argv const so I can re-instantiate game later and know it'll be in the start state.
    // For now just pass a window to the game, and see if I can quit from there
    Game game = instantiate(argc,argv);
    // Standard initialization
    //initializeCurses();
    initscr();
    clear();
    noecho();
    cbreak();
    start_color();
    init_pair(1,COLOR_GREEN,COLOR_BLACK);


    double delay = 100;
    if(argc>3){
        // TODO
        // The delay is not used if a char is picked up by wgetch
        // This makes it non-uniform, which is noticeable at slow speed.
        delay = std::stod(argv[3]);
    }
    WINDOW* win = initializeGameWindow(game.height,game.width,delay);
    wbkgd(win,COLOR_PAIR(1));

    bool cursesQuit = false;    
    while(!cursesQuit){
        char input = wgetch(win);
        cursesQuit = input=='q';
        if(input=='r'){
            // reset
            game = instantiate(argc,argv);
        }
        game.update(input);
        game.cursesRender(win,input);                         
    }
    refresh();
    endwin();

    // TODO
    // Switch this on as a fallback from input args?
    // bool quit = false;
    // while(!quit){
    //     game.render();
    //     // TODO:
    //     // This is a hacky way to listen for inputs.
    //     // curses/ncurses is a library that's meant to be good for this.
    //     char key = getch();
    //     if(key=='q'){
    //         quit = true;
    //     }
    //     else{
    //         game.update(key);
    //     }
    // }    
    return 0;
}