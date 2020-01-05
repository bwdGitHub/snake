#ifndef SNAKE_HPP
#define SNAKE_HPP
#include <vector>
#include <utility>
#include "Util.hpp"

// TODO:
// A lot of implementation details (vector, std::pair) have bled into the header
// Is that ok? It's mostly needed to specify types so either:
// 1. Template out all "implementation detail" types.
// 2. Manually write a wrapper type/interface

enum class Direction{
    UP,
    DOWN,
    LEFT,
    RIGHT
};

enum class SnakeException{
    UNKNOWN_DIRECTION
};

template<typename Point=std::pair<int,int>>
Point makePoint(int,int);

template<typename Point=std::pair<int,int>>
Point directionToPair(Direction);

template<typename Point=std::pair<int,int>>
class Snake{
    Direction direction;
    // Details of the screen need to be known to let Snake do the bounds checking.
    // Not sure that's ideal?
    unsigned int height;
    unsigned int width;

    public:
        std::vector<Point> body;
        Snake(std::vector<Point>,Direction,unsigned int, unsigned int);
        bool takeStep(Point);
        void setDirection(Direction);
        Point head();
};

#include "Snake.tpp"
#endif