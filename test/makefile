CXX = g++
SRC_PATH = ../src
GTEST_PATH = C:/cpp/googletest/googletest/

# TODO:
# This can probably be written more efficiently

tGame : tGame.o Game.o
	$(CXX) -o tGame tGame.o $(SRC_PATH)/Game.o $(GTEST_PATH)/lib/libgtest.a

tSnake : tSnake.o Util.o
	$(CXX) -o tSnake tSnake.o $(SRC_PATH)/Util.o $(GTEST_PATH)/lib/libgtest.a

tApple : tApple.o
	$(CXX) -o tApple tApple.o $(GTEST_PATH)/lib/libgtest.a

tGame.o : tGame.cpp
	$(CXX) -c tGame.cpp -I $(SRC_PATH) -I $(GTEST_PATH)/include

tSnake.o : tSnake.cpp
	$(CXX) -c tSnake.cpp -I $(SRC_PATH) -I $(GTEST_PATH)/include

tApple.o : tApple.cpp
	$(CXX) -c tApple.cpp -I $(SRC_PATH) -I $(GTEST_PATH)/include

Game.o :
	cd $(SRC_PATH) && make Game.o

Util.o :
	cd $(SRC_PATH) && make Util.o

clean :
	rm *.o *.exe