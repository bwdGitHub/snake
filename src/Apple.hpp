#ifndef APPLE_H
#define APPLE_H
#include <utility>

class Apple {
    public:
        Apple(std::pair<int,int>);
        std::pair<int,int> position;
};
#endif