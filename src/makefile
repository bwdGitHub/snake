CXX = g++

main : main.o Game.o
	$(CXX) -o main main.o Game.o

main.o : main.cpp
	$(CXX) -c main.cpp

Game.o : Game.cpp
	$(CXX) -c Game.cpp

clean : 
	rm *.exe *.o