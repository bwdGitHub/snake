#include <gtest/gtest.h>
#include "Game.hpp"

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
    auto game = Game(1,1);
    // TODO:
    // This seems to be failing currently (badly - gtest doesn't even get to finish)
    // Probably because 1x1 is an edge case and I access a value I shouldn't.

    // TODO:
    // This prints to std::cout
    // It'd be nice to instead be able to construct game with an arbitrary output buffer.
    EXPECT_NO_THROW(game.render());
}

// TODO:
// Currently the game seems to exit badly after collecting too many apples
// Guess: My "viablePositions" for the apple update ends up empty and I try to access it.

int main(int argc, char** argv){
    // TODO:
    // This main function shouldn't be necessary if you link with libgtest_main.a
    // But that doesn't work for me.
    ::testing::InitGoogleTest(&argc,argv);
    return RUN_ALL_TESTS();
}