#ifndef SNAKE_TPP
#define SNAKE_TPP
#include "Snake.hpp"
#include <iostream>
#include <algorithm>

template<typename Point>
Snake<Point>::Snake(std::vector<Point> b,Direction d, unsigned int h, unsigned int w) : body{b}, direction{d}, height{h}, width{w} {}

// TODO: 
// is vector best for popping and inserting at the front?
// There's probably a nicer way to do it without shifting everything.
template<typename Point>
bool Snake<Point>::takeStep(Point applePos){    
    Point step = directionToPair<>(direction);
    
    // May need the tail later - in case apple hit
    Point tail = body[body.size()-1];
    
    // TODO:
    // This whole thing can almost certainly be done better.     
    // The movement is "head follows step, body moves up one"
    // First do the body  
    for(auto i=body.size()-1;i>0;i--){
        // have to iterate backwards here...
        body[i] = body[i-1];
    }
    // Now update the head
    body[0].first += step.first;
    body[0].second += step.second;
    // Wrap through the walls
    // To be on the interior the position needs to be between 1 and boundary-1.
    body[0].first = 1+mod(body[0].first-1,height-2);
    body[0].second = 1+mod(body[0].second-1,width-2);

    // Self intersection logic
    auto iter = find(body.begin()+1,body.end(),body[0]);
    if(iter!=body.end()){
        // TODO: need to propagate back up to Game or main to say
        // Game over
        // A neat hack would be to throw an exception,
        // catch it in main
        // and then have the "game over" logic.
        // That seems like it might be dodgy though.
        // In any case this is a simple proof of concept for now.
        std::cout << "you lose" << "\n";
    }

    bool appleHit = body[0]==applePos;
    if(appleHit){        
        body.push_back(tail);
    }
    return appleHit;
}

template<typename Point>
void Snake<Point>::setDirection(Direction d){
    direction=d;
}

template<typename Point>
Point Snake<Point>::head(){
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
Point directionToPair(Direction d){
    // Another switch
    // TODO:
    // Map? Store the information on the data itself
    // e.g. (Direction is a struct holding a pair).
    Point step;
    switch(d){
        case Direction::UP:
            step = makePoint<Point>(-1,0);
            break;
        case Direction::DOWN:
            step = makePoint<Point>(1,0);
            break;
        case Direction::LEFT:
            step = makePoint<Point>(0,-1);
            break;
        case Direction::RIGHT:
            step = makePoint<Point>(0,1);
            break;
        default:
            throw SnakeException::UNKNOWN_DIRECTION;
    }
    return step;
}

#endif