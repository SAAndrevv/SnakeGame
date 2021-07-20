#include <SFML/Graphics.hpp>
#include "Game.h"
#include "Client.h"
#include <sstream>
#include <ctime>
#include<array>

int idClient;
int enemy;
static int count = 2;
bool isGame = true;
extern bool isLose;

int last_score = 3;
Direction direction;

extern Packet getPack;
Packet copy;
Packet sendPack;
int dots;

void converAndSaveText(std::ostringstream&, sf::Text&, int, std::string);
void makeTimerText(std::ostringstream&, sf::Text&, int);


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

	
	sf::Time playTime = sf::seconds(180);
	sf::Time timer;
	sf::Clock clock;

	std::ostringstream ostr;
	std::string str = "Score ";
    sf::RenderWindow window(sf::VideoMode(540, 570), "Snake");
    window.setFramerateLimit(60);

	
	//game.setID(idClient);
	
    game.setPosition(20.f, 50.f);

	sf::Font font;
	font.loadFromFile("calibri.ttf");

	sf::Text player1("Score 3", font, 20);
	player1.setFillColor(sf::Color::Cyan);
	player1.setPosition(5.f, 5.f);

	sf::Text player2("Score 3", font, 20);
	player2.setFillColor(sf::Color::Cyan);
	player2.setPosition(450.f, 5.f);

	sf::Text timerText("3:00", font, 30);
	timerText.setFillColor(sf::Color::White);
	timerText.setPosition(240.f, 5.f);

	sf::Text endGameText("", font, 40);
	endGameText.setFillColor(sf::Color::White);
	endGameText.setPosition(200.f, 250.f);

    sf::Event event;

	while (window.isOpen())
	{
		timer = playTime - clock.getElapsedTime();
		if (timer.asSeconds() < 0) {
			isGame = false;
			if(game.getDots() > getPack.posX.size() - 1) endGameText.setString("You won");
			else if(game.getDots() < getPack.posX.size() - 1) endGameText.setString("You lose");
			else endGameText.setString("Battle draw");
				
		}

		if (isLose) {
			isGame = false;
			endGameText.setString("You lose");
			sendPack = game.generatePack(2);
		}
		else if (getPack.id == 1) {	
			game.appleFromHost(getPack);
		}
		else if (getPack.id == 2) {
			isGame = false;
			endGameText.setString("You won");
		}

		sendPacket(sendPack);

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
		
		if (isGame)
		{

			game.Tick(direction, getPack); // С клавиатуры и полученный пакет
			if (game.checkCollision()) {
				sendPack = game.generatePack(1);
			}
			else {
				sendPack = game.generatePack(0);
			}
			converAndSaveText(ostr, player1, game.getDots(), str);
			converAndSaveText(ostr, player2, getPack.dots, str);
			makeTimerText(ostr, timerText, timer.asSeconds());

		}
		
		window.clear();

		window.draw(player1);
		window.draw(player2);
		window.draw(timerText);
		window.draw(game);

		if (!isGame) {
			window.draw(endGameText);
		}

		window.display();
	}

    return 0;
}


void converAndSaveText(std::ostringstream& ostr, sf::Text& text, int numb, std::string str = "") {
	ostr << numb;
	text.setString(str + ostr.str());

	ostr.str("");
	ostr.clear();
}

void makeTimerText(std::ostringstream& ostr, sf::Text& text, int time) {
	int min = time / 60;
	int sec = time - min * 60;

	ostr << min;
	std::string minStr = ostr.str();
	ostr.str("");
	ostr.clear();

	ostr << sec;
	std::string secStr = ostr.str();
	ostr.str("");
	ostr.clear();

	if (sec > 9)
		text.setString(minStr + ":" + secStr);
	else
		text.setString(minStr + ":0" + secStr);


}