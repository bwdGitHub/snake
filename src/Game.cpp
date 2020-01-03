#include <iostream>
#include <vector>
#include "Game.hpp"

enum class ScreenCode
{
    EMPTY,
    VERT_WALL,
    HORIZ_WALL,
    CORNER,
    SNAKE_HEAD,
    SNAKE_BODY
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

    case ScreenCode::SNAKE_BODY:
        return 'O';
        
    case ScreenCode::SNAKE_HEAD:
        return 'X';

    default:
        return ' ';
    }
}

Snake initialSnake(){
    // Initialize Snake
    // TODO: do this randomly
    // TODO: also check it's on-screen
    std::pair<int,int> body1{1,1};
    std::pair<int,int> body2{2,1};
    std::vector<std::pair<int,int>> body;
    body.push_back(body1);
    body.push_back(body2);
    Snake snake = Snake(body, Direction::UP);
    return snake;
}

Game::Game(unsigned int h, unsigned int w):height{h},width{w},snake{initialSnake()}
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
    // Separate loop over Snake body.
    // TODO: clean this up, also there's bound to be a better way.
    std::vector<std::pair<int,int>> body = snake.body;
    for(auto pos : body){
        screen[pos.first][pos.second] = ScreenCode::SNAKE_BODY;
    }
    // More wastefulness here - just overwrite the head
    std::pair<int,int> head = snake.head();
    screen[head.first][head.second] = ScreenCode::SNAKE_HEAD;
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

void Game::update(char key){
    // not implemented
}