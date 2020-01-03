#include <iostream>
#include <vector>
#include "Game.hpp"

enum class ScreenCode
{
    EMPTY
};

char renderMap(ScreenCode c)
{
    // TODO:
    // Wanted to do this as a map:
    // std::map<ScreenCode,char> renderMap; renderMap.insert({ScreenCode::EMPTY,' '});
    // but it wasn't compiling.
    switch (c)
    {
    case ScreenCode::EMPTY:
        return ' ';
    default:
        return ' ';
    }
}

Game::Game(unsigned int h, unsigned int w):height{h},width{w}
{   
    // Initialize "screen" with EMPTY    
    for (auto row = 0; row < height; row++)
    {
        std::vector<ScreenCode> column;
        screen.push_back(column);
        for (auto col = 0; col < width; col++)
        {
            screen[row].push_back(ScreenCode::EMPTY);
        }
    }
}

void Game::render()
{
    for (auto row = 0; row < height; row++)
    {
        for (auto col = 0; col < width; col++)
        {
            std::cout << renderMap(screen[row][col]);
        }
        std::cout << "\n";
    }
}