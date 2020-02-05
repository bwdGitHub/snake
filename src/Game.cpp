#include <iostream>
#include <vector>
#include "Game.hpp"
#include <algorithm>
#include <map>
#include <chrono>


int randomInteger(std::default_random_engine& eng, int start, int end){
std::uniform_int_distribution<> dist{start,end};
return dist(eng);
}

enum class ScreenCode
{
    EMPTY,
    VERT_WALL,
    HORIZ_WALL,
    CORNER,
    SNAKE_HEAD,
    SNAKE_BODY,
    APPLE
};

std::map<ScreenCode,char> renderMap{
    std::make_pair(ScreenCode::EMPTY,' '),
    std::make_pair(ScreenCode::VERT_WALL,'|'),
    std::make_pair(ScreenCode::HORIZ_WALL,'-'),
    std::make_pair(ScreenCode::CORNER,'+'),
    std::make_pair(ScreenCode::SNAKE_BODY,'o'),
    std::make_pair(ScreenCode::SNAKE_HEAD,'X'),
    std::make_pair(ScreenCode::APPLE,'*')};

Snake<> initialSnake(std::default_random_engine& eng, unsigned int h, unsigned int w){
    // Initialize Snake
    std::pair<int,int> body1{randomInteger(eng,1,h-2),randomInteger(eng,1,w-2)};
    std::vector<std::pair<int,int>> body{body1};
    int dir = randomInteger(eng,0,3);
    Direction d = static_cast<Direction>(dir);
    Snake<> snake = Snake<> (body, d, h, w);
    return snake;
}

unsigned long arbitraryNumber(){
    return std::chrono::high_resolution_clock::now().time_since_epoch()/std::chrono::milliseconds(1);
}

Game::Game(unsigned int h, unsigned int w):    
    height{h},
    width{w},
    score{0},    
    apple{Apple<> (std::make_pair(-1,-1))},
    snake{Snake<> (std::vector<std::pair<int,int>>{},Direction::UP,h,w)}     
{
    // Initialize the seed.
    unsigned long seed = arbitraryNumber();
    eng.seed(seed);

    // The initial snake and apple are not in random positions as the engine wasn't seeded.
    // So recreate the snake and 
    snake = initialSnake(eng,h,w);
    // Randomize the first apple
    randomizeApplePosition();
    // Initialize "screen" with EMPTY
    for (auto row = 0; row < height; row++)
    {
        std::vector<ScreenCode> column;
        screen.push_back(column);
        bool isRowEdge = (row==0)||(row==height-1);
        for (auto col = 0; col < width; col++)
        {
            // TODO:
            // This is ugly, got to be a better way.
            bool isColEdge = (col==0)||(col==width-1);
            bool isCorner = isRowEdge&&isColEdge;
            ScreenCode c = ScreenCode::EMPTY;
            if(isCorner){
                c = ScreenCode::CORNER;
            }
            else{
                if(isColEdge){
                    c = ScreenCode::VERT_WALL;
                }
                if(isRowEdge){
                    c = ScreenCode::HORIZ_WALL;
                }
            }
            screen[row].push_back(c);            
        }
    }
}

void Game::render()
{   
    // Have to clear the screen to kill the previous snake
    // TODO: Again - got to be a better way.
    for(auto row = 1; row<height-1; row++){
        for(auto col = 1; col<width-1; col++){
            screen[row][col] = ScreenCode::EMPTY;
        }
    }

    // Render apple
    screen[apple.position.first][apple.position.second] = ScreenCode::APPLE;

    // Separate loop over Snake body.
    // TODO: clean this up, also there's bound to be a better way.
    std::vector<std::pair<int,int>> body = snake.body;
    for(auto pos : body){
        screen[pos.first][pos.second] = ScreenCode::SNAKE_BODY;
    }
    // More wastefulness here - just overwrite the head
    std::pair<int,int> head = snake.head();
    screen[head.first][head.second] = ScreenCode::SNAKE_HEAD;

    for (auto row = 0; row < height; row++)
    {
        for (auto col = 0; col < width; col++)
        {
            std::cout << renderMap[screen[row][col]];
        }
        std::cout << "\n";
    }
}

void Game::cursesRender(WINDOW * win, char input){
    // TODO - Because I clear I think I have to redraw the box on every update
    // Maybe you can just clear the interior?
    // Or have a separate "interior" window (would make the wrap-around logic easier)
    wclear(win);
    box(win,0,0);   

    // TODO: get the chars from renderMap.
    //auto appleChar = renderMap[ScreenCode::APPLE];
    //const char* appleCharPtr = &appleChar;

    mvwprintw(win,apple.position.first,apple.position.second,"*");
    for(auto pt:snake.body){
        mvwprintw(win,pt.first,pt.second,"O");
    }
    mvwprintw(win,snake.head().first,snake.head().second,"X");
    wrefresh(win);    
}

enum class Exception{
    UNKNOWN_KEY
};

Direction keyToDirection(char key){
    // Simple switch
    // Map better?    
    switch(key){
        case 'w':
            return Direction::UP;
        case 'a':
            return Direction::LEFT;
        case 's':
            return Direction::DOWN;
        case 'd':
            return Direction::RIGHT;
        default:
            throw Exception::UNKNOWN_KEY;
    }
}

bool Game::update(char key){
    
    // TODO: lowercase the key
    if(key=='w'||key=='a'||key=='s'||key=='d'){
        Direction newDirection = keyToDirection(key);
        snake.setDirection(newDirection);
    }
    bool appleHit = snake.takeStep(apple.position);
    if(appleHit){
        score++;
        randomizeApplePosition();
    }
    return snake.hasSelfIntersected;

}

void Game::randomizeApplePosition(){
    std::vector<std::pair<int,int>> viablePositions;
    // TODO:
    // more bad design -
    // just loop over all screen positions and don't push back those that are snake.
    for(int i = 1; i<height-1; i++){        
        for(int j = 1; j<width-1; j++){
            std::pair<int,int> p = std::make_pair(i,j);
            auto iter = find(snake.body.begin(),snake.body.end(),p);
            if(iter==snake.body.end()){
                viablePositions.push_back(p);
            }

        }
    }
    int n = viablePositions.size();
    int i = randomInteger(eng,1,n);
    apple.position = viablePositions[i];
}