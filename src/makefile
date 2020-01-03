CXX = g++

main : main.o Game.o Snake.o
	$(CXX) -o main main.o Game.o Snake.o

main.o : main.cpp
	$(CXX) -c main.cpp

Game.o : Game.cpp
	$(CXX) -c Game.cpp

Snake.o : Snake.cpp Snake.hpp
	$(CXX) -c Snake.cpp

clean : 
	rm *.exe *.o