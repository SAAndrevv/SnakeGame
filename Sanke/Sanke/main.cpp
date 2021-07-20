#include <SFML/Graphics.hpp>
#include "Game.h"
#include "Client.h"
#include <sstream>

bool isGame = true;
extern bool isLose;

Direction direction;

extern Packet getPack;
Packet sendPack;

void makeTextScore(std::ostringstream&, sf::Text&, int, std::string, sf::Color);
void makeTimerText(std::ostringstream&, sf::Text&, int);

void StartGame(std::string name, int idColor)
{
	sendPack.name = name;
	sendPack.idColor = idColor;
	Game game;

	if (startNet()) {
		//host
		game.generateApple();
		sendPack = game.generatePack(1);	
	}
	else{
		sendPack = game.generatePack(0);
	}
	game.setIdColor(idColor);
	game.setName(name);
	sendPacket(sendPack);

	
	sf::Time playTime = sf::seconds(180);
	sf::Time timer;
	sf::Clock clock;

	std::ostringstream ostr;
    sf::RenderWindow window(sf::VideoMode(540, 570), "Snake");
    window.setFramerateLimit(60);
	
    game.setPosition(20.f, 50.f);

	sf::Font font;
	font.loadFromFile("calibri.ttf");

	sf::Text player1("", font, 25);
	player1.setPosition(5.f, 5.f);

	sf::Text player2("", font, 25);
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
		if (timer.asSeconds() < 0) { //Проверка на конец игры по таймеру
			isGame = false;
			if(game.getDots() > getPack.posX.size() - 1) endGameText.setString("You won");
			else if(game.getDots() < getPack.posX.size() - 1) endGameText.setString("You lose");
			else endGameText.setString("Battle draw");
				
		}

		if (isLose) { // Если произошла коллизия у змейки
			isGame = false;
			endGameText.setString("You lose");
			sendPack = game.generatePack(2);
		}
		else if (getPack.id == 1) {	// Если id = 1 значит другой клиент сгенерил яблоко
			game.appleFromHost(getPack);
		}
		else if (getPack.id == 2) { // Если id = 2 значит у змейки клиент произошла коллизия
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
				//if (event.key.code == sf::Keyboard::Escape) window.close();
				if (event.key.code == sf::Keyboard::Left) direction = Direction::Left;
				if (event.key.code == sf::Keyboard::Right) direction = Direction::Right;
				if (event.key.code == sf::Keyboard::Up) direction = Direction::Up;
                if (event.key.code == sf::Keyboard::Down) direction = Direction::Down;
				// Новая игра
				//if (event.key.code == sf::Keyboard::F2)
				//{
					//game.initGame();

				//}
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
			makeTextScore(ostr, player1, game.getDots(), name, game.colorReturner(sendPack.idColor));
			makeTextScore(ostr, player2, getPack.dots, getPack.name, game.colorReturner(getPack.idColor));
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
}


void makeTextScore(std::ostringstream& ostr, sf::Text& text, int numb, std::string str, sf::Color color) {
	ostr << numb;
	text.setString(str + " " + ostr.str());
	text.setFillColor(color);
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

int main() {
	std::string name;
	int idColor = 1;

	std::cout << "Enter you name: \n";
	std::cin >> name;

	std::cout << "Choce color you snake:\n1.White\n2.Red\n3.Magenta\n4.Yellow\n\nTYPE ONLY NUMBER\n";
	std::cin >> idColor;

	StartGame(name, idColor);

	return 0;
}