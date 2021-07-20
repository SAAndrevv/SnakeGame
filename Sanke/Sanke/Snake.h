#pragma once
#include <vector>
#include <array>
#undef min
#undef max
#include <SFML/Graphics.hpp>

struct Packet
{
	std::array<short int, 2> apple;
	std::vector<short int> posX;
	std::vector<short int> posY;
	int id;
	int dots;
	std::vector<std::array<short int, 3>> bonus;
};


enum class Direction { Left, Right, Up, Down };
const int ALL_DOTS = 3600;

class Snake {

public:
	Snake(int);
	bool Move(Direction);
	int getXPos(int) const;
	int getYPos(int) const;
	int getDots() const;
	void addDots(int);
	void setDelay(float);
	bool collisionWithAnotherSanke(Packet);

	std::vector<short int> getXVector();
	std::vector<short int> getYVector();


private:
	sf::Clock clock;
	float time;
	float timer;
	float delay;
	//Direction direction;
	static const int DOT_SIZE = 10;
	bool checkCol();
	int sField;

	int dots;
	std::vector<short int> x;
	std::vector<short int> y;

};
