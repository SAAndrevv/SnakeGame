#pragma once
#include <SFML/Graphics.hpp>


const int W_WIDTH = 560;
const int W_HEIGHT = 530;
const int DOT_SIZE = 10;
const int ALL_DOTS = 3600;
const int RAND_POS = 59;

enum class Direction {Left, Right , Up, Down};

class Game : public sf::Drawable, public sf::Transformable {

private:
    
    int apple_x;
    int apple_y;

    int x[ALL_DOTS];
    int y[ALL_DOTS];

    bool inGame;

    void generateApple();
    void checkApple();

public:
    int dots;
    Direction direction;

    Game();
    void initGame(); 
    void move();
    void checkCollision();
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;



};
