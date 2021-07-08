#include "Game.h"


Game::Game() {

    inGame = true;
    initGame();
}

void Game::initGame() {
	dots = 3;

	for (int i = 0; i < dots; ++i) {
		x[i] = 50 - i * 10;
		y[i] = 50;
	}

    generateApple();
}

void Game::generateApple() {

	std::srand(std::time(nullptr));

    int r = std::rand() % W_WIDTH / 10 - 1;
    apple_x = (r * DOT_SIZE);

    r = std::rand() % W_HEIGHT / 10 - 1;
    apple_y = (r * DOT_SIZE);

	
}

void Game::move() {
    for (int i = dots; i > 0; i--) {
        x[i] = x[i - 1];
        y[i] = y[i - 1];
    }

    if (direction == Direction::Left) {
        x[0] -= DOT_SIZE;
    }

    if (direction == Direction::Right) {
        x[0] += DOT_SIZE;
    }

    if (direction == Direction::Up) {
        y[0] -= DOT_SIZE;
    }

    if (direction == Direction::Down) {
        y[0] += DOT_SIZE;
    }
}

void Game::checkCollision() {

    if ((x[0] == apple_x) && (y[0] == apple_y)) {

        dots++;
        generateApple();
    }

    for (int i = dots; i > 0; i--) {

        if ((i > 4) && (x[0] == x[i]) && (y[0] == y[i])) {
            inGame = false;
        }
    }

    if (y[0] >= W_HEIGHT) {
        y[0] = DOT_SIZE / 2;
    }

    if (y[0] < 0) {
        y[0] = W_HEIGHT - DOT_SIZE / 2;
    }

    if (x[0] >= W_WIDTH) {
        x[0] = DOT_SIZE / 2;
    }

    if (x[0] < 0) {
        x[0] = W_WIDTH - DOT_SIZE / 2;
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

		for (int i = 0; i < dots; i++)
		{
			circle.setPosition(x[i], y[i]);
			target.draw(circle, states);

		}	
	}
}