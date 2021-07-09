#include "Game.h"
#include <iostream>


Game::Game(Snake & s) : snake(s){
    
    inGame = true;
    generateApple();
    
}


void Game::generateApple() {

	std::srand(std::time(nullptr));

    int r = std::rand() % W_WIDTH / 10 - 1;
    apple_x = (r * DOT_SIZE);

    r = std::rand() % W_HEIGHT / 10 - 1;
    apple_y = (r * DOT_SIZE);	
}

void Game::checkCollision() {
    int xHead = snake.getXPos(0);
    int yHead = snake.getYPos(0);

    if ((xHead == apple_x) && (yHead == apple_y)) {  
        
        snake.setDots(1);
        
        generateApple();
    }

    for (int i = snake.getDots(); i > 0; i--) {

        if ((i > 4) && (xHead == snake.getXPos(i)) && (yHead == snake.getYPos(i))) {
            //inGame = false;
        }
    }

    if (yHead >= W_HEIGHT) {
        snake.setYPos(0, DOT_SIZE / 2);
        //y[0] = DOT_SIZE / 2;
    }

    if (yHead < 0) {
        snake.setYPos(0, W_HEIGHT - DOT_SIZE / 2);
        //y[0] = W_HEIGHT - DOT_SIZE / 2;
    }

    if (xHead >= W_WIDTH) {
        snake.setXPos(0, DOT_SIZE / 2);
        //x[0] = DOT_SIZE / 2;
    }

    if (xHead < 0) {
        snake.setXPos(0, W_WIDTH - DOT_SIZE / 2);
        //x[0] = W_WIDTH - DOT_SIZE / 2;
    }
}


void Game::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	sf::Color color = sf::Color(200, 100, 200);

	sf::RectangleShape shape(sf::Vector2f(560, 530));
	shape.setOutlineThickness(2.f);
	shape.setOutlineColor(color);
	shape.setFillColor(sf::Color::Transparent);
	shape.setPosition(0, 0);

	target.draw(shape, states);

	sf::CircleShape circle;
	circle.setRadius(DOT_SIZE / 2);
	circle.setFillColor(sf::Color::Blue);
	
	if (inGame) {

       
        circle.setPosition(apple_x, apple_y);
        target.draw(circle, states);
        circle.setFillColor(sf::Color::Red);

        int dots = snake.getDots();
        //std::cout << dots;

		for (int i = 0; i < dots; i++)
		{
            int x = snake.getXPos(i);
            int y = snake.getYPos(i);

			circle.setPosition(x, y);
			target.draw(circle, states);

		}	
	}
}