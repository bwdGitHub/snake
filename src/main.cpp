#include <iostream>
#include <conio.h>
#include "Game.hpp"
#include <curses.h>
#include <cstring>
#include <cstdio>

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

WINDOW* initializeGameWindow(int h,int w,double delay){
    WINDOW *win = newwin(h,w,0,0);        
    keypad(win,TRUE);
    box(win,0,0);
    wrefresh(win);
    curs_set(0);
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
    init_pair(2,COLOR_WHITE,COLOR_BLUE);


    double delay = 100;
    if(argc>3){
        // TODO
        // The delay is not used if a char is picked up by wgetch
        // This makes it non-uniform, which is noticeable at slow speed.
        delay = std::stod(argv[3]);
    }
    WINDOW* win = initializeGameWindow(game.height,game.width,delay);
    WINDOW* scoreWin = newwin(3,game.width,game.height,0);
    wbkgd(win,COLOR_PAIR(1));
    wbkgd(scoreWin,COLOR_PAIR(2));
    wrefresh(scoreWin);
    char scoreStr[] = "Score: ";
    char score[3];
    mvwprintw(scoreWin,0,0,scoreStr);
    wrefresh(scoreWin);



    bool cursesQuit = false;    
    bool hasLost = false;
    while(!cursesQuit){
        char input = wgetch(win);
        cursesQuit = input=='q';
        if(input=='r'){
            // reset
            hasLost = false;
            game = instantiate(argc,argv);
            // Reset the score window here.
            // Currently undecided if it's better to have Game do all rendering
            // Or just use what we know from Game to update for some stuff.
            wclear(scoreWin);
            mvwprintw(scoreWin,0,0,scoreStr);
            wrefresh(scoreWin);
        }     
        if(!hasLost){
            hasLost = game.update(input);
            sprintf(score,"%d",game.score);
            mvwprintw(scoreWin,0,strlen(scoreStr)+1,score);
            wrefresh(scoreWin);
            game.cursesRender(win,input); 
        }
        if(hasLost){
            wclear(scoreWin);
            mvwprintw(scoreWin,0,0,"You Lose!");
            mvwprintw(scoreWin,1,0,"'r' - Restart");
            mvwprintw(scoreWin,2,0,"'q' - Quit");
            wrefresh(scoreWin);
        }                        
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