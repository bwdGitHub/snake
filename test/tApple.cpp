#include <gtest/gtest.h>
#include "Apple.hpp"

class ConstructorTest :
    public testing::TestWithParam<std::pair<int,int>>{};

TEST_P(ConstructorTest, positionSet){
    // A parameterized test example.
    Apple apple = Apple(GetParam());
    EXPECT_EQ(apple.position,GetParam());
}

// Parameterized test suites have to be instantiated.
// Note the parameter values here cover cases we might not even want to work (0,-1)
// But for now they pass.
INSTANTIATE_TEST_SUITE_P(ConstructorTestSuite,
    ConstructorTest,
    testing::Values(std::make_pair(1,1),std::make_pair(-1,1),std::make_pair(0,1),std::make_pair(100,200)));

// Test fixtures are classes. 
// TEST_F that specify these classes can access them as child classes.

class AppleFixture : public ::testing::Test{
    // If it is complex to setup the data for tests, a fixture can help.
    // But the fixture will construct each time, so
    // If it is heavy to setup the fixture, you may need other tricks.
    // One trick could be to create the object once and reference it,
    // but then the state of that object can be modified by various tests.
    // In general that's probably confusing.
    protected:
        Apple apple = Apple(std::make_pair(1,1));
};

TEST_F(AppleFixture, positionIsSetPublic){
    auto currentPos = apple.position;
    auto newPos = std::make_pair(currentPos.first+1,currentPos.second-1);
    apple.position = newPos;
    ASSERT_NE(currentPos,newPos);
    EXPECT_EQ(apple.position,newPos);
}

int main(int argc, char** argv){
    ::testing::InitGoogleTest(&argc,argv);
    return RUN_ALL_TESTS();
}