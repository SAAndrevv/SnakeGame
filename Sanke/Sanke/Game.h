#pragma once
#include <SFML/Graphics.hpp>
#include "Snake.h"


const int W_WIDTH = 560;
const int W_HEIGHT = 530;
const int DOT_SIZE = 10;

const int RAND_POS = 59;


class Game : public sf::Drawable, public sf::Transformable {

private:
    
    Snake & snake;
    int apple_x;
    int apple_y;
    int dots;

    int x[ALL_DOTS];
    int y[ALL_DOTS];

    bool inGame;

    void generateApple();
    
    

public:
    Direction direction;

    Game(Snake &);
    //void initGame(); 
    void checkCollision();
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;



};
