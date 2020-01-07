#ifndef SNAKE_HPP
#define SNAKE_HPP
#include <vector>
#include <utility>
#include "Util.hpp"

// TODO:
// 1. Manually write a wrapper type/interface for the default templates (std::pair<int,int> and std::vector<Point>)
// 2. Evaluate and test using a different container to std::vector<Point>. I think without 1. such a container will have to have a handful of methods with the same names as std::vector.

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

template<typename Point=std::pair<int,int>, typename Container=std::vector<Point>>
class Snake{
    Direction direction;
    // Details of the screen need to be known to let Snake do the bounds checking.
    // Not sure that's ideal?
    unsigned int height;
    unsigned int width;

    public:
        Container body;
        Snake(Container,Direction,unsigned int, unsigned int);
        bool takeStep(Point);
        void setDirection(Direction);
        Point head();
};

#include "Snake.tpp"
#endif