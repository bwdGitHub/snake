#ifndef APPLE_H
#define APPLE_H
#include <utility>

template<typename Point=std::pair<int,int>>
class Apple {
    public:
        Apple(Point);
        Point position;
};

#include "Apple.tpp"
#endif