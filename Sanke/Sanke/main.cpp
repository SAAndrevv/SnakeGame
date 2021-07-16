#include <SFML/Graphics.hpp>
#include "Game.h"
#include "Client.h"
#include <sstream>
#include <ctime>

int you;
int enemy;
static int count = 2;

int last_score = 3;
Direction direction;

extern Direction getPack;
std::vector<int> dots;


int main()
{
	if (startNet()) {
		you = 0;
	}
	else{
		you = 1;
	}

	bool t = true;
	std::ostringstream ostr;
	std::string str = "Score ";
    sf::RenderWindow window(sf::VideoMode(540, 570), "Snake");
    window.setFramerateLimit(60);

    
	
	Game game(count);
	game.setID(you);
    game.setPosition(20.f, 50.f);

	sf::Font font;
	font.loadFromFile("calibri.ttf");

	sf::Text text1("Score 3", font, 20);
	text1.setFillColor(sf::Color::Cyan);
	text1.setPosition(5.f, 5.f);

	sf::Text text2("Score 3", font, 20);
	text2.setFillColor(sf::Color::Cyan);
	text2.setPosition(450.f, 5.f);

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

		sf::Time dt = clock.restart();
 
        float dtAsSeconds = dt.asSeconds();

		sendPacket(direction);

		while (window.pollEvent(event))
		{


			if (event.type == sf::Event::Closed) window.close();
			if (event.type == sf::Event::KeyPressed)
			{
				// ѕолучаем нажатую клавишу - выполн€ем соответствующее действие
				if (event.key.code == sf::Keyboard::Escape) window.close();
				if (event.key.code == sf::Keyboard::Left) direction = Direction::Left;
				if (event.key.code == sf::Keyboard::Right) direction = Direction::Right;
				if (event.key.code == sf::Keyboard::Up) direction = Direction::Up;
                if (event.key.code == sf::Keyboard::Down) direction = Direction::Down;
				// Ќова€ игра
				if (event.key.code == sf::Keyboard::F2)
				{
					//game.initGame();

				}
			}			
		}
		
		if (t && timer > delay)
			{

				game.checkCollision();
				game.moveSnake(direction, getPack);
				timer = 0;
			}

		dots = game.getDots();

		ostr << dots[0];
		text1.setString(str + ostr.str());

		ostr.str("");
		ostr.clear();

		ostr << dots[1];
		text2.setString(str + ostr.str());

		ostr.str("");
		ostr.clear();
	

		window.clear();
		window.draw(text1);
		window.draw(text2);
		window.draw(game);
		window.display();
	}

    return 0;
}