#pragma once
#include <SFML/Graphics.hpp>
#include "Snake.h"


const int W_WIDTH = 500;
const int W_HEIGHT = 500;
const int DOT_SIZE = 10;

const int RAND_POS = 49;


class Game : public sf::Drawable, public sf::Transformable {

private:
    
    std::vector<Snake> snakes;
    int apple_x;
    int apple_y;
    int dots;

    int x[ALL_DOTS];
    int y[ALL_DOTS];

    bool inGame;

    void generateApple();
    int id;
    int count;
    
    

public:
    Direction direction;

    Game(int);
    //void initGame(); 
    void checkCollision();
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    void moveSnake(Direction, Direction);
    void setID(int);
    std::vector<int> getDots();



};
