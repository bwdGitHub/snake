#include "FrontEnd.hpp"
#include <cstring>
#include <cctype>

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

WINDOW* initializeScoreWindow(int gameHeight, int gameWidth){
    // Initialize the main window for the scores.
    // It needs to appear below the game window.
    // It needs to have at least 3 rows to show the "You Lose" text.
    // It is nice to have it the same width as the game window.

    WINDOW* win = newwin(3,gameWidth,gameHeight,0);
    wbkgd(win,COLOR_PAIR(static_cast<short>(ColorPair::Score)));
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
        input = std::tolower(input);
        startGame = input==startChar;
        validInput = startGame || input==quitChar;
    }
    return startGame;
}

void reset(Game &game, WINDOW* scoreWin, const char scoreStr[]){
    // Reset behaviour 
    // - replace the reference to the game object with it's initial state
    // - set the score window back to initial state (since this logic happens twice I should abstract it out)
    game = Game(game.height,game.width);
    wclear(scoreWin);
    mvwprintw(scoreWin, 0, 0, scoreStr);
    wrefresh(scoreWin);
}

void displayLoseMessage(WINDOW* scoreWin){
    // Use the score window to show the "Game over" messages.
    wclear(scoreWin);
    mvwprintw(scoreWin, 0, 0, "You Lose!");
    mvwprintw(scoreWin, 1, 0, "'r' - Restart");
    mvwprintw(scoreWin, 2, 0, "'q' - Quit");
    wrefresh(scoreWin);
}

void runGame(Game game, WINDOW* win, WINDOW* scoreWin){
    // Main game loop.
    bool cursesQuit = false;
    bool hasLost = false;
    char score[3];
    char scoreStr[] = "Score: ";
    mvwprintw(scoreWin,0,0,scoreStr);
    while (!cursesQuit)
    {
        char input = wgetch(win);
        input = std::tolower(input);
        cursesQuit = input == 'q';
        if (input == 'r')
        {
            // reset
            hasLost = false;
            reset(game,scoreWin,scoreStr);
        }
        if (!hasLost)
        {
            hasLost = game.update(input);
            sprintf(score, "%d", game.score);
            mvwprintw(scoreWin, 0, strlen(scoreStr) + 1, score);
            wrefresh(scoreWin);
            game.cursesRender(win, input);
        }
        if (hasLost)
        {
            displayLoseMessage(scoreWin);
        }
    }
}

void beginGame(int height, int width, double delay){
    // Abstract out the main block - I think for testing later it's going to be important
    // that main is a trivial as possible - it's the one thing I can't get at easy.
    Game game = Game(height,width);

    initCurses();

    WINDOW* startWin = startWindow(game.width,0,0);
    bool startGame = startScreenWait(startWin,'e','q');
    if(startGame){        
        wclear(startWin);
        wrefresh(startWin);
        delwin(startWin);

        char scoreStr[] = "Score: ";

        WINDOW* win = initializeGameWindow(game.height,game.width,delay);
        WINDOW* scoreWin = initializeScoreWindow(game.height,game.width);

        runGame(game,win,scoreWin);
    }
    refresh();
    endwin();
}

void parseAndBeginGame(int argc, char** argv){
    // Abstract out everything from main - think this will help testing later.

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
    beginGame(height,width,delay);  
}