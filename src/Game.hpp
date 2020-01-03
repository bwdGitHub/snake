#ifndef GAME_H
#define GAME_H
#include <vector>

enum class ScreenCode;

class Game {
    private:
        std::vector<std::vector<ScreenCode>> screen;
    public:
        Game(unsigned int, unsigned int);
        unsigned int height;
        unsigned int width;
        void render();
};
#endif