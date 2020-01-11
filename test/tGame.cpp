#include <gtest/gtest.h>
#include "Game.hpp"
#include "Util.hpp"

TEST(Game,UnsignedInt){
    // Can construct Game with unsigned ints
    // Member variables set as expected
    unsigned int h = 10;
    unsigned int w = 20;
    auto game = Game(h,w);
    EXPECT_EQ(game.height,h);
    EXPECT_EQ(game.width,w);
}

TEST(Game,Int){
    // Can construct Game with int.
    int h = 10;
    int w = 20;
    auto game = Game(h,w);
    EXPECT_EQ(game.height,h);
    EXPECT_EQ(game.width,w);
}

TEST(render,NoExcept){   
    // 4x4 seems to be a sensible minimum - currently unenforced. 
    // TODO: Why does 4x4 freeze? 5x5 seems to pass the test.
    // TODO: render prints to std::out, which messes the test log up, would be good to avoid.
    auto game = Game(5,5);
    EXPECT_NO_THROW(game.render());
    EXPECT_EQ(game.height,5);
}

// TODO:
// Currently the game seems to exit badly after collecting too many apples
// Guess: My "viablePositions" for the apple update ends up empty and I try to access it.

// TODO:
// It'd be good to test things like the snake and apple but they're part of the private API
// How can tests get around this?

int main(int argc, char** argv){
    // TODO:
    // This main function shouldn't be necessary if you link with libgtest_main.a
    // But that doesn't work for me.
    ::testing::InitGoogleTest(&argc,argv);
    return RUN_ALL_TESTS();
}