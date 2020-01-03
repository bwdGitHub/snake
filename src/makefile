CXX = g++

main : main.o Game.o Snake.o Apple.o
	$(CXX) -o main main.o Game.o Snake.o Apple.o

main.o : main.cpp
	$(CXX) -c main.cpp

Game.o : Game.cpp
	$(CXX) -c Game.cpp

Snake.o : Snake.cpp Snake.hpp
	$(CXX) -c Snake.cpp

Apple.o : Apple.cpp Apple.hpp
	$(CXX) -c Apple.cpp

clean : 
	rm *.exe *.o