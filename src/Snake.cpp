#include "Snake.hpp"

enum class Direction{
    UP,
    DOWN,
    LEFT,
    RIGHT
};

Snake::Snake(std::vector<std::pair<int,int>> b,Direction d) : body{b}, direction{d} {}

// TODO: 
// is vector best for popping and inserting at the front?
// There's probably a nicer way to do it without shifting everything.

void Snake::takeStep(std::pair<int,int> pos){
    body.pop_back();
    body.insert(body.begin(),pos);
}

void Snake::setDirection(Direction d){
    direction=d;
}

std::pair<int,int> Snake::head(){
    return body[0];
}