#include <iostream>

class Snake {};

class Apple {};

class Game {
    public:
        Game(unsigned int h, unsigned int w) : height{h},width{w} {}
        unsigned int height;
        unsigned int width;

        void render(){
            std::cout<<"H: "<<this->height<<"\n";
            std::cout<<"W: "<<this->width<<"\n";
        }

};

int main(int argc, char** argv){
    Game game = Game(10,20);
    game.render();
    return 0;
}