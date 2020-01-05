#ifndef APPLE_H
#define APPLE_H
#include <utility>

// By using a template here, in principle someone can use different implementations of Point.
// A minor downside is that all Apple calls have to be Apple<>

// TODO:
// It feels like this would be more robust if an interface was provided by me,
// currently it is implicit that because std::pair<int,int> is the default, your Point should be similar.
template<typename Point=std::pair<int,int>>
class Apple {
    public:
        Apple(Point);
        Point position;
};

#include "Apple.tpp"
#endif