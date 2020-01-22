#ifndef GAME_H
#define GAME_H
#include <vector>
#include "Snake.hpp"
#include "Apple.hpp"
#include <random>
#include <curses.h>

enum class ScreenCode;

class Game {
    private:
        std::vector<std::vector<ScreenCode>> screen;
        // TODO: Should member objects be references?
        Snake<> snake;
        Apple<> apple;
        std::default_random_engine eng {}; 
        void randomizeApplePosition();      
    public:
        Game(unsigned int, unsigned int);
        unsigned int height;
        unsigned int width;
        unsigned int score;
        void render();
        void cursesRender(WINDOW *,char);
        bool update(char);
};
#endif