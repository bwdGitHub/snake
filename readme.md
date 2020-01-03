# Snake

## Aim
A simple implementation of [Snake](https://en.wikipedia.org/wiki/Snake_(video_game_genre)) at the terminal.

## References
Following [Robert Heaton's guide](https://robertheaton.com/2018/12/02/programming-project-5-snake/).

Credit to [/u/yngwiepalpateen](https://www.reddit.com/user/yngwiepalpateen)'s [comment](https://www.reddit.com/r/programming/comments/eixhuy/the_polygons_of_another_world/fcukjjg/) that linked me to this. I'm not any of the commenters in that thread, just noticed it while browsing.

## Implementation
### Language
Going to try this in C++. Why? Because I'm trying to learn it.

## Compilation
Source code will be in the *src* directory.

I'm using MinGW g++ on Windows.

### Makefiles
I intend to use makefiles + gnu make.

#### <a name="makefileDisclaimer"></a> Disclaimer 
Using makefiles is pretty new to me. Almost certainly I'm breaking a bunch of standards, so they're probably not a good example to follow.

## Testing
I intend to use [GoogleTest](https://github.com/google/googletest) to write tests for the code. These will be located in the *test* directory. 

The makefile there should have variables that define where I have GoogleTest located. I compiled libgtest.a once and use it. This means you'll have to do the same if you want to use my makefile unchanged. This probably isn't best practice - instead maybe the makefile should say how to compile libgtest.a, and make knows when it has to do this. In short, see [Disclaimer](#makefileDisclaimer).