#ifndef SNAKE_H
#define SNAKE_H
#include <vector>
#include <utility>

enum class Direction;

class Snake{
    std::vector<std::pair<int,int>> body;
    Direction direction;

    public:
        Snake(std::vector<std::pair<int,int>>,Direction);
        void takeStep(std::pair<int,int>);
        void setDirection(Direction);
        std::pair<int,int> head();
};
#endif