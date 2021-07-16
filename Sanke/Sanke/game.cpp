#include "Game.h"
#include <iostream>


Game::Game(int c) {
    count = c;
    snakes.resize(c);
    //std::cout << "Test";
    for (int i = 0; i < c; i++) {
        snakes[i] = Snake(i * 10 + 20);
        //std::cout << i << std::endl;
    }
    inGame = true;
    generateApple();
    
}

void Game::setID(int id_c) {
    id = id_c;
}
void Game::moveSnake(Direction dir, Direction dir2) {
    
    //std::cout << dir1;
    
    for (int i = 0; i < snakes.size(); ++i) {
        if (i == id) {
            snakes[i].Move(dir);
        }
        else {
            
            snakes[i].Move(dir2);
        }

    }
    //for (Snake & snake : snakes) {
        //snake.Move(dir);
    //}
    
}


void Game::generateApple() {

	std::srand(std::time(nullptr));

    int r = std::rand() % RAND_POS;
    apple_x = (r * DOT_SIZE);

    r = std::rand() % RAND_POS;
    apple_y = (r * DOT_SIZE);	
}

void Game::checkCollision() {
    for (Snake &snake : snakes) {

        int xHead = snake.getXPos(0);
        int yHead = snake.getYPos(0);

        if ((xHead * DOT_SIZE == apple_x) && (yHead * DOT_SIZE == apple_y)) {

            snake.setDots(1);

            generateApple();
        }

        if (yHead >= W_HEIGHT) {
            snake.setYPos(0, 1);
            //y[0] = DOT_SIZE / 2;
        }

        if (yHead < 1) {
            snake.setYPos(0, RAND_POS);
            //y[0] = W_HEIGHT - DOT_SIZE / 2;
        }

        if (xHead >= W_WIDTH) {
            snake.setXPos(0, 1);
            //x[0] = DOT_SIZE / 2;
        }

        if (xHead < 1) {
            snake.setXPos(0, RAND_POS);
            //x[0] = W_WIDTH - DOT_SIZE / 2;
        }
    }
}
std::vector<int> Game::getDots() {
    std::vector<int> tmp;
    for (int i = 0; i < count; ++i) {
        tmp.push_back(snakes[i].getDots());
    }
    return tmp;
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

       
        circle.setPosition(apple_x, apple_y);
        target.draw(circle, states);
        circle.setFillColor(sf::Color::Red);

        for (Snake snake : snakes) {
            int dots = snake.getDots();
            //std::cout << dots;

            for (int i = 0; i < dots; i++)
            {
                int x = snake.getXPos(i);
                int y = snake.getYPos(i);

                circle.setPosition(x * DOT_SIZE, y * DOT_SIZE);
                target.draw(circle, states);

            }
        }
	}
}