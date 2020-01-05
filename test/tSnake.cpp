#include <gtest/gtest.h>
#include "Snake.hpp"

TEST(Constructor,basicSmall){
    std::vector<std::pair<int,int>> v;
    std::pair<int,int> p = std::make_pair(1,2);
    v.push_back(p);
    Direction dir = Direction::UP;
    Snake<> snake = Snake<>(v,dir,5,6);
    EXPECT_EQ(snake.body,v);
    EXPECT_EQ(snake.head(),p);
}

TEST(Constructor,basicMedium){
    std::vector<std::pair<int,int>> v;
    for(auto i = 0; i<5; i++){
        std::pair<int,int> p = std::make_pair(i+1,i+2);
        v.push_back(p);
    }
    Direction dir = Direction::DOWN;
    Snake<> snake = Snake<>(v,dir,3,4);
    EXPECT_EQ(snake.body,v);
    EXPECT_EQ(snake.head(),v[0]);
}

TEST(takeStep,noApple){
    std::vector<std::pair<int,int>> v;
    v.push_back(std::make_pair(1,10));
    v.push_back(std::make_pair(2,9));
    v.push_back(std::make_pair(3,7));
    // The logic is only the head is moved
    // body[i] becomes body[i-1]
    // If an apple is hit, the body extends.
    Direction dir = Direction::LEFT;
    // The screen size is provided at construction time for wrap-around logic.
    // Need it big enough here to not wrap.
    Snake<> snake = Snake<>(v,dir,20,20);
    // Fake apple position that isn't hit by the head.
    std::pair<int,int> applePos = std::make_pair(11,11);
    snake.takeStep(applePos);
    std::vector<std::pair<int,int>> expV;
    expV.push_back(std::make_pair(1,9));
    expV.push_back(std::make_pair(1,10));
    expV.push_back(std::make_pair(2,9));
    EXPECT_EQ(expV,snake.body);
}

TEST(takeStep,apple){
    std::vector<std::pair<int,int>> v;
    v.push_back(std::make_pair(1,10));
    v.push_back(std::make_pair(2,9));
    v.push_back(std::make_pair(3,7));
    // The logic is only the head is moved
    // body[i] becomes body[i-1]
    // If an apple is hit, the body extends.
    Direction dir = Direction::LEFT;
    // The screen size is provided at construction time for wrap-around logic.
    // Need it big enough here to not wrap.
    Snake<> snake = Snake<>(v,dir,20,20);
    // Fake apple position that is hit by the head after step.
    std::pair<int,int> applePos = std::make_pair(1,9);
    snake.takeStep(applePos);
    std::vector<std::pair<int,int>> expV;
    expV.push_back(std::make_pair(1,9));
    expV.push_back(std::make_pair(1,10));
    expV.push_back(std::make_pair(2,9));
    expV.push_back(std::make_pair(3,7));
    EXPECT_EQ(expV,snake.body);
}

TEST(takeStep,wrapLogic){
    std::vector<std::pair<int,int>> v;
    v.push_back(std::make_pair(1,10));
    v.push_back(std::make_pair(2,9));
    v.push_back(std::make_pair(3,7));
    // The logic is only the head is moved
    // body[i] becomes body[i-1]
    // If an apple is hit, the body extends.
    Direction dir = Direction::RIGHT;
    // The screen size is provided at construction time for wrap-around logic.
    // Moving RIGHT increases the second of the pair by 1. 
    // To get the "wall" as the next step RIGHT, you need to have a width of v[0].second+2
    // to account for both walls.
    Snake<> snake = Snake<>(v,dir,20,v[0].first+2);
    // Fake apple position that isn't hit by the head.
    std::pair<int,int> applePos = std::make_pair(11,11);
    snake.takeStep(applePos);
    std::vector<std::pair<int,int>> expV;
    expV.push_back(std::make_pair(1,1));
    expV.push_back(std::make_pair(1,10));
    expV.push_back(std::make_pair(2,9));
    EXPECT_EQ(expV,snake.body);
}

int main(int argc, char** argv){
    ::testing::InitGoogleTest(&argc,argv);
    return RUN_ALL_TESTS();
}