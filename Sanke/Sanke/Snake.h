#pragma once
#include <vector>
#undef min
#undef max
#include <SFML/Graphics.hpp>

struct Packet
{
	
	//int posXApple;
	//int posYApple;
	//int dots;
	//int apple[2];
	std::vector<short int> posX;
	std::vector<short int> posY;
	//int id;

};

enum class Direction { Left, Right, Up, Down };
const int ALL_DOTS = 3600;

class Snake {

public:
	Snake();
	Snake(int, int);
	//void initSnake();
	bool Move(Direction);
	int getXPos(int) const;
	int getYPos(int) const;
	void setXPos(int, int);
	void setYPos(int, int);
	int getDots() const;
	void addDots(int);
	//void setDirection(Direction);
	float getDelay();
	void setDelay(float);
	//bool collisionWithAnotherSanke(Snake &);

	std::vector<short int> getXVector();
	std::vector<short int> getYVector();

	//void setXVector(std::vector<short int>);
	//void setYVector(std::vector<short int>);

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
	//int x[ALL_DOTS];
	//int y[ALL_DOTS];

	//void checkCollision();



};
