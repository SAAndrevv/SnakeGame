#pragma once
#include <vector>

enum class Direction { Left, Right, Up, Down };
const int ALL_DOTS = 3600;

class Snake {

public:
	Snake();
	Snake(int);
	//void initSnake();
	bool Move(Direction);
	int getXPos(int) const;
	int getYPos(int) const;
	void setXPos(int, int);
	void setYPos(int, int);
	int getDots() const;
	void setDots(int);
	//void setDirection(Direction);
	float getDelay();
	void setDelay(float);

	std::vector<int> getXVector();
	std::vector<int> getYVector();

private:
	
	//Direction direction;
	static const int DOT_SIZE = 10;
	bool checkCol();

	float delay;
	int dots;
	std::vector<int> x;
	std::vector<int> y;
	//int x[ALL_DOTS];
	//int y[ALL_DOTS];

	//void checkCollision();



};
