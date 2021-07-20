#pragma once
#include <SFML/Graphics.hpp>
#include "Snake.h"
#include <thread>
//#include <array>


const int W_WIDTH = 500;
const int W_HEIGHT = 500;
const int DOT_SIZE = 10;

const int SIZE_FIELD = 49;


class Game : public sf::Drawable, public sf::Transformable {

private:

    Packet getPacket;
    Snake* snake;

    int apple_x;
    int apple_y;
    int dots;
    int idSendPack;
    int idColor;
    bool targetBonus;
    bool inGame;
    std::string name;
  
    std::vector<std::array<short int, 3>> bonus;
  

    void generateBonus();
    void bonusOnSnake();
    
    
public:
    Game();
    ~Game();
    void setName(std::string);
    void setIdColor(int);
    sf::Color colorReturner(int) const;
    Packet generatePack(int);
    void generateApple();
    void appleFromHost(Packet);
    bool checkCollision();
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    void Tick(Direction, Packet);
    int getDots();
    



};
