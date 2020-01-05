#ifndef GAME_H
#define GAME_H
#include <vector>
#include "Snake.hpp"
#include "Apple.hpp"
#include <random>

enum class ScreenCode;

class Game {
    private:
        std::vector<std::vector<ScreenCode>> screen;
        // TODO: Should member objects be references?
        Snake<> snake;
        Apple<> apple;
        std::default_random_engine eng {};        
    public:
        Game(unsigned int, unsigned int);
        unsigned int height;
        unsigned int width;
        void render();
        void update(char);
        void randomizeApplePosition();
};
#endif