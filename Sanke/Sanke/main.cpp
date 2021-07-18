#include <SFML/Graphics.hpp>
#include "Game.h"
#include "Client.h"
#include <sstream>
#include <ctime>

int idClient;
int enemy;
static int count = 2;

int last_score = 3;
Direction direction;

extern Packet getPack;
Packet copy;
Packet sendPack;
int dots;


int main()
{
	Game game;

	if (startNet()) {
		idClient = 0; //host
		game.generateApple();
		sendPack = game.generatePack(1);	
	}
	else{
		idClient = 1;	
		sendPack = game.generatePack(0);
	}
	sendPacket(sendPack);
	//std::cout << "test1 " << sendPack.apple[0] << " " << sendPack.apple[1] << std::endl;
	
	

	//std::cout << sendPack.posXApple << " " << sendPack.posYApple << std::endl;
	//std::cout << sendPack.posX[0] << " " << sendPack.posY[0] << std::endl;
	//while(!getPack.posXApple)
	

	//bool t = true;
	std::ostringstream ostr;
	std::string str = "Score ";
    sf::RenderWindow window(sf::VideoMode(540, 570), "Snake");
    window.setFramerateLimit(60);

	
	game.setID(idClient);
	
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
	//if (idClient) {
		//game.appleFromHost(getPack);
		
		//std::cout << getPack.posXApple << " " << getPack.posYApple << std::endl;
	//}

	//sf::Clock clock;
	//float time = 0.0f;
	//float timer = 0.0f;
	//float delay = 0.0f;

	while (window.isOpen())
	{
		//copy = getPack;
		if (getPack.id == 1) {
			
			game.appleFromHost(getPack);
			//std::cout << "test2 " << getPack.apple[0] << " " << getPack.apple[1] << std::endl;
			//Sleep(50000);
			//while (1);
		}
		//copy = getPack;
		//std::cout << getPack.posXApple << " " << getPack.posYApple << std::endl;
		//delay = 0.3f;
		//time = clock.getElapsedTime().asSeconds();
		//timer += time;
		//clock.restart();

		//sf::Time dt = clock.restart();
       // float dtAsSeconds = dt.asSeconds();
		//sendPack.dir = direction;
		//sendPack = game.generatePack();
		//sendPacket(sendPack);
		//game.drawAnotherSnake(copy);

		while (window.pollEvent(event))
		{


			if (event.type == sf::Event::Closed) window.close();
			if (event.type == sf::Event::KeyPressed)
			{
				// Получаем нажатую клавишу - выполняем соответствующее действие
				if (event.key.code == sf::Keyboard::Escape) window.close();
				if (event.key.code == sf::Keyboard::Left) direction = Direction::Left;
				if (event.key.code == sf::Keyboard::Right) direction = Direction::Right;
				if (event.key.code == sf::Keyboard::Up) direction = Direction::Up;
                if (event.key.code == sf::Keyboard::Down) direction = Direction::Down;
				// Новая игра
				if (event.key.code == sf::Keyboard::F2)
				{
					//game.initGame();

				}
			}			
		}
		
		//if (timer > delay) // && 
		//{
			
		game.Tick(direction, getPack); // С клавиатуры и полученный пакет
		if (game.checkCollision()) {
			sendPack = game.generatePack(1);
		}
		else{
			sendPack = game.generatePack(0);
		}

		sendPacket(sendPack);
		

		ostr << game.getDots();
		text1.setString(str + ostr.str());

		ostr.str("");
		ostr.clear();

		ostr << getPack.dots;
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