#include "Snake.h"
#include <iostream>


Snake::Snake(int size_field) {
    sField = size_field;
    time = 0.0f;
    timer = 0.0f;
    delay = 0.3f;
    std::srand(std::time(nullptr));
	dots = 3;
    x.resize(dots + 1);
    y.resize(dots + 1);

    int xStart = std::rand() % (sField - 3) + 1;
    int yStart = std::rand() % sField + 1;
    

	for (int i = 0; i < dots; ++i) {
		x[i] = xStart - i;
		y[i] = yStart;
	}
}

bool Snake::Move(Direction direction) {
    static Direction lastRemoveDirection = Direction::Right;
    static Direction lastDirection = Direction::Left;
    time = clock.getElapsedTime().asSeconds();
    timer += time;
    clock.restart();

    if (timer > delay) {

        if (direction == lastRemoveDirection) {
            direction = lastDirection;
            //std::cout << "Wrong move";
            //return;
        }

        for (int i = dots; i > 0; i--) {

            x[i] = x[i - 1];
            y[i] = y[i - 1];
        }

        if (direction == Direction::Left) {
            lastRemoveDirection = Direction::Right;
            x[0]--;
        }

        if (direction == Direction::Right) {
            lastRemoveDirection = Direction::Left;
            x[0]++;
        }

        if (direction == Direction::Up) {
            lastRemoveDirection = Direction::Down;
            y[0]--;
        }

        if (direction == Direction::Down) {
            lastRemoveDirection = Direction::Up;
            y[0]++;
        }

        lastDirection = direction;

       
        timer = 0;
        
    }

    return checkCol();
}

int Snake::getXPos(int ind) const{
    return x[ind];
}

int Snake::getYPos(int ind) const{
    return y[ind];
}


int Snake::getDots() const{
    return dots;
}

void Snake::addDots(int count) {
    dots += count;

    x.resize(dots + 1);
    y.resize(dots + 1);
    
}

std::vector<short int> Snake::getXVector() {
    return x;
}

std::vector<short int> Snake::getYVector() {
    return y;
}

void Snake::setDelay(float d) {
    delay -= d;
}

bool Snake::checkCol() {

    for (int i = dots; i > 0; i--) {
        
        if ((dots > 4)&& (x[0] == x[i]) && (y[0] == y[i])) {
            return true;;
        }
    }
    if (y[0] > sField) {
        y[0] = 1;
    }

    if (y[0] < 1) {
        y[0] = sField;
    }

    if (x[0] > sField) {
        x[0] = 1;
    }

    if (x[0] < 1) {
        x[0] = sField;
    }
    return false;
}

bool Snake::collisionWithAnotherSanke(Packet pac) {
    int lenghSnake = pac.posX.size() - 1;

    for (int i = 0; i < lenghSnake; ++i) {
        if (x[0] == pac.posX[i] && y[0] == pac.posY[i])
            return true;
    }
   return false;
}