CXX = g++
SRC_PATH = ../src
GTEST_PATH = C:/cpp/googletest/googletest/

tGame : tGame.o Game.o
	$(CXX) -o tGame tGame.o $(SRC_PATH)/Game.o $(GTEST_PATH)/lib/libgtest.a

tGame.o : tGame.cpp
	$(CXX) -c tGame.cpp -I $(SRC_PATH) -I $(GTEST_PATH)/include

Game.o :
	cd $(SRC_PATH) && make Game.o

clean :
	rm *.o *.exe