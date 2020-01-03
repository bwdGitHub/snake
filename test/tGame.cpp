#include <gtest/gtest.h>
#include "Game.cpp"

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
    // This prints to std::cout
    // It'd be nice to instead be able to construct game with an arbitrary output buffer.
    EXPECT_NO_THROW(game.render());
}

int main(int argc, char** argv){
    ::testing::InitGoogleTest(&argc,argv);
    return RUN_ALL_TESTS();
}