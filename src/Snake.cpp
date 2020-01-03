#include "Snake.hpp"
#include <iostream>

Snake::Snake(std::vector<std::pair<int,int>> b,Direction d, unsigned int h, unsigned int w) : body{b}, direction{d}, height{h}, width{w} {}

enum class Exception{
    UNKNOWN_DIRECTION
};

std::pair<int,int> directionToPair(Direction d){
    // Another switch
    // TODO:
    // Map? Store the information on the data itself
    // e.g. (Direction is a struct holding a pair).
    std::pair<int,int> step;
    switch(d){
        case Direction::UP:
            step = std::make_pair(-1,0);
            break;
        case Direction::DOWN:
            step = std::make_pair(1,0);
            break;
        case Direction::LEFT:
            step = std::make_pair(0,-1);
            break;
        case Direction::RIGHT:
            step = std::make_pair(0,1);
            break;
        default:
            throw Exception::UNKNOWN_DIRECTION;
    }
    return step;
}

int mod(int a, int b){
    return (a%b + b)%b;
}

// TODO: 
// is vector best for popping and inserting at the front?
// There's probably a nicer way to do it without shifting everything.

void Snake::takeStep(std::pair<int,int> applePos){    
    std::pair<int,int> step = directionToPair(direction);
    
    // May need the tail later - in case apple hit
    std::pair<int,int> tail = body[body.size()-1];
    
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

    if(body[0]==applePos){        
        body.push_back(tail);
    }
}

void Snake::setDirection(Direction d){
    direction=d;
}

std::pair<int,int> Snake::head(){
    return body[0];
}