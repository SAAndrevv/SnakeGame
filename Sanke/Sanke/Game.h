#pragma once
#include <SFML/Graphics.hpp>
#include "Snake.h"
#include <array>


const int W_WIDTH = 500;
const int W_HEIGHT = 500;
const int DOT_SIZE = 10;

const int SIZE_FIELD = 49;




class Game : public sf::Drawable, public sf::Transformable {

private:

    Packet pack;
    Packet packGet;
    Snake* snake;
    int apple_x;
    int apple_y;
    int dots;

    int x[ALL_DOTS];
    int y[ALL_DOTS];

    bool inGame;
    std::vector<std::array<short int, 3>> bonus;

    
    int id;
    int count;
    void generateBonus();
    
    

public:
    Direction direction;

    Game();
    ~Game();
    //void addSnake(Packet);
    Packet generatePack(int);
    void generateApple();
    void appleFromHost(Packet);
    void appleToClient();
    //void initGame(); 
    bool checkCollision();
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    void Tick(Direction, Packet);
    void setID(int);
    void drawAnotherSnake(Packet);
    int getDots();
    



};
