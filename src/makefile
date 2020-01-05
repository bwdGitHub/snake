CXX = g++

main : main.o Game.o Util.o Snake.hpp Snake.tpp Apple.hpp Apple.tpp 
	$(CXX) -o main main.o Game.o Util.o

main.o : main.cpp
	$(CXX) -c main.cpp 

Game.o : Game.cpp
	$(CXX) -c Game.cpp

Util.o : Util.cpp
	$(CXX) -c Util.cpp

clean : 
	rm *.exe *.o