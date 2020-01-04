CXX = g++
SRC_PATH = ../src
GTEST_PATH = C:/cpp/googletest/googletest/

tGame : tGame.o Game.o Snake.o Apple.o
	$(CXX) -o tGame tGame.o $(SRC_PATH)/Game.o $(SRC_PATH)/Snake.o $(SRC_PATH)/Apple.o $(GTEST_PATH)/lib/libgtest.a

tSnake : tSnake.o Snake.o
	$(CXX) -o tSnake tSnake.o $(SRC_PATH)/Snake.o $(GTEST_PATH)/lib/libgtest.a

tApple : tApple.o Apple.o
	$(CXX) -o tApple tApple.o $(SRC_PATH)/Apple.o $(GTEST_PATH)/lib/libgtest.a

tGame.o : tGame.cpp
	$(CXX) -c tGame.cpp -I $(SRC_PATH) -I $(GTEST_PATH)/include

tSnake.o : tSnake.cpp
	$(CXX) -c tSnake.cpp -I $(SRC_PATH) -I $(GTEST_PATH)/include

tApple.o : tApple.cpp
	$(CXX) -c tApple.cpp -I $(SRC_PATH) -I $(GTEST_PATH)/include

Game.o :
	cd $(SRC_PATH) && make Game.o

Snake.o :
	cd $(SRC_PATH) && make Snake.o

Apple.o :
	cd $(SRC_PATH) && make Apple.o

clean :
	rm *.o *.exe