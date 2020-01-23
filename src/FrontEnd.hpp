#ifndef FRONTEND_H
#define FRONTEND_H

#include "Game.hpp"
#include <curses.h>
#include <tuple>

std::tuple<int,int,double> inputParse(int,char**);

WINDOW* initializeGameWindow(int,int,double);

WINDOW* initializeScoreWindow(int,int);

void initCurses();

WINDOW* startWindow(int,int,int);

bool startScreenWait(WINDOW*,char,char);

void reset(Game&,WINDOW*,const char[]);

void displayLoseMessage(WINDOW*);

void runGame(Game,WINDOW*,WINDOW*);

void beginGame(int,int,double);

void parseAndBeginGame(int,char**);
#endif