CXX = g++
CURSES_INCLUDES = C:/cpp/pdcurses/PDCurses
CURSES_LIB = C:/cpp/pdcurses/PDCurses/wincon/pdcurses.a

# TODO: this isn't working - updating Snake.tpp doesn't cause a rebuild of Game.o
# 1. Is including header/tpp dependencies necessary?


main : main.o FrontEnd.o Game.o Util.o Snake.hpp Snake.tpp Apple.hpp Apple.tpp
	$(CXX) -o main main.o FrontEnd.o Game.o Util.o $(CURSES_LIB)

main.o : main.cpp
	$(CXX) -c main.cpp -I $(CURSES_INCLUDES)

FrontEnd.o : FrontEnd.cpp
	$(CXX) -c FrontEnd.cpp -I $(CURSES_INCLUDES)

Game.o : Game.cpp
	$(CXX) -c Game.cpp -I $(CURSES_INCLUDES)

Util.o : Util.cpp
	$(CXX) -c Util.cpp

clean : 
	rm *.exe *.o