# Snake

## Aim
A simple implementation of [Snake](https://en.wikipedia.org/wiki/Snake_(video_game_genre)) at the terminal.

## References
I'm following [Robert Heaton's guide](https://robertheaton.com/2018/12/02/programming-project-5-snake/). I found out about this via [/u/yngwiepalpateen](https://www.reddit.com/user/yngwiepalpateen)'s [comment](https://www.reddit.com/r/programming/comments/eixhuy/the_polygons_of_another_world/fcukjjg/) whilst browsing.

## Implementation
### Language
I treated this as a learning project in C++ after reading [A Tour of C++](http://www.stroustrup.com/tour2.html). Almost certainly I forgot all the important bits, and used what I remembered in wrong and dangerous ways.

### Dependencies
The only external dependency I used in the source code was [PDCurses](https://pdcurses.org/).

In the test code I used [GoogleTest](https://github.com/google/googletest).

## Compilation
Source code will be in the *src* directory.

I'm using MinGW g++ on Windows.

### Makefiles
I'm using makefiles + gnu make. Using makefiles is pretty new to me. I'm probably breaking a bunch of standards because I only read enough about makefile syntax to make life convenient for me.

In particular, at least in the current state, the makefiles depend on the particular directories I installed things like googletest and pdcurses. Also I must have the dependency syntax messed up since `make` doesn't recompile when the `.tpp` files are changed. I've been getting my with `make clean; make`, but should work out what's going on there.

## Testing
I did a little bit of testing with [GoogleTest](https://github.com/google/googletest), see the *test* directory. There's far less than sufficient, at least for a [TDD](https://en.wikipedia.org/wiki/Test-driven_development) style workflow, but it was a good exercise to get familiar with some basic GoogleTest syntax.