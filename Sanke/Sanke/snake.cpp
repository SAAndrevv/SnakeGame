#include "Snake.h"
#include <iostream>

Snake::Snake() {
    
    //std::cout << "Def Snake";
}

Snake::Snake(int start) {
	dots = 3;
    delay = 0.2;
    x.resize(dots + 1);
    y.resize(dots + 1);
    

	for (int i = 0; i < dots; ++i) {
		x[i] = start - i;
		y[i] = 5;
	}
    //std::cout << "Cast Snake";
}

bool Snake::Move(Direction direction) {
    
    for (int i = dots; i > 0; i--) {
        
        x[i] = x[i - 1];
        y[i] = y[i - 1];
    }

    if (direction == Direction::Left) {
        x[0]--;
    }

    if (direction == Direction::Right) {
        x[0]++;
    }

    if (direction == Direction::Up) {
        y[0]--;
    }

    if (direction == Direction::Down) {
        y[0]++;
    }

    return checkCol();
}

int Snake::getXPos(int ind) const{
    return x[ind];
}

int Snake::getYPos(int ind) const{
    return y[ind];
}

void Snake::setXPos(int ind, int val){
    x[ind] = val;
}

void Snake::setYPos(int ind, int val) {
    y[ind] = val;
}

int Snake::getDots() const{
    return dots;
}

void Snake::setDots(int count) {
    dots += count;

    x.resize(dots + 1);
    y.resize(dots + 1);
    
}

//void Snake::setDirection(Direction _direction) {
    //direction = _direction;
//}

std::vector<int> Snake::getXVector() {
    return x;
}

std::vector<int> Snake::getYVector() {
    return y;
}

float Snake::getDelay() {
    return delay;
}

void Snake::setDelay(float d) {
    delay += d;
}

bool Snake::checkCol() {

    for (int i = dots; i > 0; i--) {
        
        if ((dots > 4)&& (x[0] == x[i]) && (y[0] == y[i])) {
            std::cout << "Lose";
            return false;
        }
    }
    return true;
}