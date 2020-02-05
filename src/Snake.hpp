#ifndef SNAKE_HPP
#define SNAKE_HPP
#include <vector>
#include <utility>
#include "Util.hpp"

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
    unsigned int height;
    unsigned int width;    

    public:
        Container body;
        Snake(Container,Direction,unsigned int, unsigned int);
        bool takeStep(Point);
        void setDirection(Direction);
        Point head();
        bool hasSelfIntersected;
};

#include "Snake.tpp"
#endif