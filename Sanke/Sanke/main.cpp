#include <SFML/Graphics.hpp>
#include "Game.h"

#include <sstream>
#include <ctime>

int last_score = 3;

int main()
{
	std::ostringstream ostr;
	std::string str = "Score ";
    sf::RenderWindow window(sf::VideoMode(600, 600), "Snake");
    window.setFramerateLimit(60);

    
	Snake snake;
	Game game(snake);
    game.setPosition(20.f, 50.f);

	sf::Font font;
	font.loadFromFile("calibri.ttf");

	sf::Text text("Score 3", font, 20);
	text.setFillColor(sf::Color::Cyan);
	text.setPosition(5.f, 5.f);

    sf::Event event;

	sf::Clock clock;
	float time = 0.0f;
	float timer = 0.0f;
	float delay = 0.0f;

	while (window.isOpen())
	{
		delay = 0.3f;
		time = clock.getElapsedTime().asSeconds();
		timer += time;
		clock.restart();

		while (window.pollEvent(event))
		{


			if (event.type == sf::Event::Closed) window.close();
			if (event.type == sf::Event::KeyPressed)
			{
				// ѕолучаем нажатую клавишу - выполн€ем соответствующее действие
				if (event.key.code == sf::Keyboard::Escape) window.close();
				if (event.key.code == sf::Keyboard::Left) snake.setDirection(Direction::Left);
				if (event.key.code == sf::Keyboard::Right) snake.setDirection(Direction::Right);
				if (event.key.code == sf::Keyboard::Up) snake.setDirection(Direction::Up);
				if (event.key.code == sf::Keyboard::Down) snake.setDirection(Direction::Down);
				// Ќова€ игра
				if (event.key.code == sf::Keyboard::F2)
				{
					//game.initGame();

				}
			}

			if (timer > delay)
			{
				game.checkCollision();
				snake.Move();
				timer = 0;
			}
		}
		if (last_score != snake.getDots()) {
			last_score = snake.getDots();
			ostr << last_score;
			text.setString(str + ostr.str());

			ostr.str("");
			ostr.clear();
			
		}
	

		window.clear();
		window.draw(text);
		window.draw(game);
		window.display();
	}

    return 0;
}