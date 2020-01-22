#include "Game.hpp"
#include <curses.h>
#include <cstring>

Game instantiate(const int argc, const char** argv){
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
    wtimeout(win,delay);
    return win;
}

enum class ColorPair{
    // Convenience enum to relate the colours initialized in 
    // initCurses() to the windows they're intended for.
    // Though these have to be static_cast<short> anyway...
    Game=1,
    Score=2
};

void initCurses(){
    // Initialize conditions for the curses terminal.
    initscr();
    clear();
    noecho();
    cbreak();
    curs_set(0);
    start_color();
    init_pair(static_cast<short>(ColorPair::Game),COLOR_GREEN,COLOR_BLACK);
    init_pair(static_cast<short>(ColorPair::Score),COLOR_WHITE,COLOR_BLUE);
}

WINDOW* startWindow(int width, int yStart, int xStart){
    // Initialize the window to show the start screen.
    // Don't take a height - it needs to be at least 5,
    // could allow height input and assert but no reason to yet.
    WINDOW* startWin = newwin(5,width,yStart,xStart);
    mvwprintw(startWin,0,0,"SNAKE");
    mvwprintw(startWin,1,0,"'e' - Start");
    mvwprintw(startWin,2,0,"'wasd' - Move");
    mvwprintw(startWin,3,0,"'r' - Restart");
    mvwprintw(startWin,4,0,"'q' - Quit");
    wbkgd(startWin,COLOR_PAIR(static_cast<short>(ColorPair::Game)));
    wrefresh(startWin);
    return startWin;
}

bool startScreenWait(WINDOW* win, char startChar, char quitChar){
    // Wait for valid input from user.
    // This is a bit of a weird pattern, this while loop can only end if valid input is pressed
    // Since there's only two choices we only need to return if one was pressed
    bool validInput = false;
    bool startGame = false;
    while(!validInput){
        char input = wgetch(win);
        startGame = input==startChar;
        validInput = startGame || input==quitChar;
    }
    return startGame;
}

int main(const int argc, const char** argv){
    // Make argc and argv const so I can re-instantiate game later and know it'll be in the start state.

    Game game = instantiate(argc,argv);

    initCurses();

    WINDOW* startWin = startWindow(game.width,0,0);
    bool startGame = startScreenWait(startWin,'e','q');
    if(startGame){
        wclear(startWin);
        wrefresh(startWin);
        delwin(startWin);

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
    }
    refresh();
    endwin();   
    return 0;
}