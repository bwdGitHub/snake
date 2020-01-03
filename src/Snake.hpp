#ifndef SNAKE_H
#define SNAKE_H
#include <vector>
#include <utility>

// TODO:
// A lot of implementation details (vector, std::pair) have bled into the header
// Is that ok? It's mostly needed to specify types so either:
// 1. Template out all "implementation detail" types.
// 2. Manually write a wrapper type/interface

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