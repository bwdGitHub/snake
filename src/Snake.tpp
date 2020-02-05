#ifndef SNAKE_TPP
#define SNAKE_TPP
#include "Snake.hpp"
#include <iostream>
#include <algorithm>
#include <map>

template<typename Point,typename Container>
Snake<Point,Container>::Snake(Container b,Direction d, unsigned int h, unsigned int w) : body{b}, direction{d}, height{h}, width{w}, hasSelfIntersected{false} {}

template<typename Point,typename Container>
bool Snake<Point,Container>::takeStep(Point applePos){    
    Point step = directionToPair<>(direction);
    
    // May need the original tail later - in case apple hit
    Point tail = body[body.size()-1];
    
    for(auto i=body.size()-1;i>0;i--){
        // have to iterate backwards here...
        body[i] = body[i-1];
    }

    // Now update the head
    body[0]+=step;

    // Wrap through the walls
    // To be on the interior the position needs to be between 1 and boundary-1.
    body[0].first = 1+mod(body[0].first-1,height-2);
    body[0].second = 1+mod(body[0].second-1,width-2);

    // Self intersection logic
    auto iter = find(body.begin()+1,body.end(),body[0]);
    if(iter!=body.end()){
        hasSelfIntersected = true;
    }

    bool appleHit = body[0]==applePos;
    if(appleHit){        
        body.push_back(tail);
    }
    return appleHit;
}

template<typename Point>
void operator+=(Point& pt1,const Point & pt2){
    pt1.first += pt2.first;
    pt1.second += pt2.second;
}

template<typename Point,typename Container>
void Snake<Point,Container>::setDirection(Direction d){
    direction=d;
}

template<typename Point,typename Container>
Point Snake<Point,Container>::head(){
    return body[0];
}

// For a specialized implementation, this has to be inlined.
// I didn't read fully why...
// See https://stackoverflow.com/questions/48402633/why-do-templates-specialisations-need-to-be-inlined
template<> inline
std::pair<int,int> makePoint(int a, int b){
    return std::make_pair(a,b);
}

template<typename Point>
std::map<Direction, Point> directionToPoint{
    {Direction::UP, makePoint<Point>(-1,0)},
    {Direction::DOWN, makePoint<Point>(1,0)},
    {Direction::LEFT, makePoint<Point>(0,-1)},
    {Direction::RIGHT, makePoint<Point>(0,1)}
};

template<typename Point>
Point directionToPair(Direction d){
    Point step = directionToPoint<Point>[d];
    return step;
}

#endif