#include "Game.h"
#include <iostream>


Game::Game() {   
    snake = new Snake(20, SIZE_FIELD);
    int apple_x = 0;
    int apple_y = 0;
    
    inGame = true;
    
    
}

void Game::setID(int id_c) {
    id = id_c;
}
void Game::moveSnake(Direction dir, Packet pack) {

    snake->Move(dir);
    packGet = pack;
    //generatePack();

    //snakes[!id]->setDots(pack.posX.size());
    
    //snakes[!id]->setXVector(pack.posX);
    //snakes[!id]->setYVector(pack.posY);

}

Packet Game::generatePack(int id) {
    Packet tmp;
    tmp.id = id;
    tmp.apple[0] = apple_x;
    tmp.apple[1] = apple_y;
    tmp.posX = snake->getXVector();
    tmp.posY = snake->getYVector();
    tmp.dots = snake->getDots();

    return tmp;
    
    
}

    
void Game::appleFromHost(Packet pack) {
    apple_x = pack.apple[0];
    apple_y = pack.apple[1];
}


void Game::generateApple() {

	std::srand(std::time(nullptr));

    // От 1 до SIZE_FIELD включительно

    int r = std::rand() % SIZE_FIELD + 1;
    apple_x = r;

    r = std::rand() % SIZE_FIELD + 1;
    apple_y = r;	

    //pack.posXApple = apple_x;
    //pack.posYApple = apple_y;
}

bool Game::checkCollision() {

    if (snake->collisionWithAnotherSanke(packGet)){
        std::cout << "Collision snakes";
    }
        int xHead = snake->getXPos(0);
        int yHead = snake->getYPos(0);

        if ((xHead == apple_x) && (yHead == apple_y)) {

            snake->addDots(1);
            generateApple();
            return true;   
        }
        return false;   
    
}
int Game::getDots() {
    return snake->getDots();
}

void Game::drawAnotherSnake(Packet pac){
    packGet = pac;
}


void Game::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	sf::Color color = sf::Color(200, 100, 200);

	sf::RectangleShape shape(sf::Vector2f(W_WIDTH, W_HEIGHT));
	shape.setOutlineThickness(2.f);
	shape.setOutlineColor(color);
	shape.setFillColor(sf::Color::Transparent);
	shape.setPosition(0, 0);

	target.draw(shape, states);

	sf::CircleShape circle;
	circle.setRadius(DOT_SIZE / 2);
	circle.setFillColor(sf::Color::Blue);
	
	if (inGame) {

       
        circle.setPosition(apple_x * DOT_SIZE, apple_y * DOT_SIZE);
        target.draw(circle, states);
        circle.setFillColor(sf::Color::Red);

        
        int dots = snake->getDots();
            //std::cout << dots;

        for (int i = 0; i < dots; i++)
        {
            int x = snake->getXPos(i);
            int y = snake->getYPos(i);

            circle.setPosition(x * DOT_SIZE, y * DOT_SIZE);
            target.draw(circle, states);

        }

        dots = packGet.posX.size() - 1;

        for (int i = 0; i < dots; ++i) {
            circle.setPosition(packGet.posX[i] * DOT_SIZE, packGet.posY[i] * DOT_SIZE);
            target.draw(circle, states);
        }
        
	}
}


Game::~Game() {
    
    delete snake;
    
}