#include <iostream>
#include <vector>
#include "Game.hpp"

enum class ScreenCode
{
    EMPTY,
    VERT_WALL,
    HORIZ_WALL,
    CORNER
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

    case ScreenCode::VERT_WALL:
        return '|';

    case ScreenCode::HORIZ_WALL:
        return '-';

    case ScreenCode::CORNER:
        return '+';

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
        bool isRowEdge = (row==0)||(row==height-1);
        for (auto col = 0; col < width; col++)
        {
            // TODO:
            // This is ugly, got to be a better way.
            bool isColEdge = (col==0)||(col==width-1);
            bool isCorner = isRowEdge&&isColEdge;
            ScreenCode c = ScreenCode::EMPTY;
            if(isCorner){
                c = ScreenCode::CORNER;
            }
            else{
                if(isColEdge){
                    c = ScreenCode::VERT_WALL;
                }
                if(isRowEdge){
                    c = ScreenCode::HORIZ_WALL;
                }
            }
            screen[row].push_back(c);
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