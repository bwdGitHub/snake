#include "Game.hpp"
#include <curses.h>
#include <cstring>
#include <tuple>

std::tuple<int,int,double> inputParse(int argc, char** argv){
    int height = 8;
    int width = 16;
    double delay = 100;
    if(argc>2){
        height = std::stoi(argv[1]);
        width = std::stoi(argv[2]);
    }
    if(argc>3){
        delay = std::stod(argv[3]);
    }
    return std::make_tuple(height,width,delay);
}

enum class ColorPair{
    // Convenience enum to relate the colours initialized in 
    // initCurses() to the windows they're intended for.
    // Though these have to be static_cast<short> anyway...
    Game=1,
    Score=2
};

WINDOW* initializeGameWindow(int h,int w,double delay){
    // Initialize the main window for the game.

    WINDOW *win = newwin(h,w,0,0);        
    keypad(win,TRUE);
    box(win,0,0);
    wrefresh(win);
    wtimeout(win,delay);
    wbkgd(win,COLOR_PAIR(static_cast<short>(ColorPair::Game)));
    return win;
}

WINDOW* initializeScoreWindow(int gameHeight, int gameWidth, char scoreStr[]){
    // Initialize the main window for the scores.
    // It needs to appear below the game window.
    // It needs to have at least 3 rows to show the "You Lose" text.
    // It is nice to have it the same width as the game window.

    WINDOW* win = newwin(3,gameWidth,gameHeight,0);
    wbkgd(win,COLOR_PAIR(static_cast<short>(ColorPair::Score)));
    mvwprintw(win, 0, 0, scoreStr);
    wrefresh(win);
    return win;
}

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

int main(int argc, char** argv){

    // R.e. argument parsing, the following are two options
    // https://www.boost.org/doc/libs/1_36_0/doc/html/program_options.html
    // https://www.gnu.org/savannah-checkouts/gnu/libc/manual/html_node/Getopt.html
    // For now I can use a tuple since I'm not trying to be extensive.
    //
    // R.e. const - I kind of want to be certain I don't accidentally change the user inputs
    // For now marking the following variables as const seems to be one way - but it's pretty weak,
    // you can re-declare these and get no warnings with my currrent compiler options, at least if
    // the re-declaration is in a new scope (in that case you're just getting a new temp in a new scope)

    const std::tuple<int,int,double> inputs = inputParse(argc,argv);
    const int height = std::get<0>(inputs);
    const int width = std::get<1>(inputs);
    const double delay = std::get<2>(inputs);

    Game game = Game(height,width);

    initCurses();

    WINDOW* startWin = startWindow(game.width,0,0);
    bool startGame = startScreenWait(startWin,'e','q');
    if(startGame){        
        wclear(startWin);
        wrefresh(startWin);
        delwin(startWin);

        char scoreStr[] = "Score: ";
        char score[3];

        WINDOW* win = initializeGameWindow(game.height,game.width,delay);
        WINDOW* scoreWin = initializeScoreWindow(game.height,game.width,scoreStr);

        bool cursesQuit = false;    
        bool hasLost = false;
        while(!cursesQuit){
            char input = wgetch(win);
            cursesQuit = input=='q';
            if(input=='r'){
                // reset
                hasLost = false;
                game = Game(height,width);
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