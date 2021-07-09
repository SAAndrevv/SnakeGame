#include "Snake.h"
#include <iostream>

Snake::Snake() {
	dots = 3;

	for (int i = 0; i < dots; ++i) {
		x[i] = 50 - i * 10;
		y[i] = 50;
	}
}

void Snake::Move() {
    
    for (int i = dots; i > 0; i--) {
        
        x[i] = x[i - 1];
        y[i] = y[i - 1];
    }

    if (direction == Direction::Left) {
        x[0] -= DOT_SIZE;
    }

    if (direction == Direction::Right) {
        x[0] += DOT_SIZE;
    }

    if (direction == Direction::Up) {
        y[0] -= DOT_SIZE;
    }

    if (direction == Direction::Down) {
        y[0] += DOT_SIZE;
    }
}

//void Snake::checkCollision() {

    //if ((x[0] == apple_x) && (y[0] == apple_y)) {

        //dots++;
        //generateApple();
    //}

    //for (int i = dots; i > 0; i--) {

        //if ((i > 4) && (x[0] == x[i]) && (y[0] == y[i])) {
            //inGame = false;
        //}
    //}

    //if (y[0] >= W_HEIGHT) {
        //y[0] = DOT_SIZE / 2;
    //}

    //if (y[0] < 0) {
        //y[0] = W_HEIGHT - DOT_SIZE / 2;
    //}

    //if (x[0] >= W_WIDTH) {
        //x[0] = DOT_SIZE / 2;
    //}

    //if (x[0] < 0) {
        //x[0] = W_WIDTH - DOT_SIZE / 2;
    //}
//}

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
    
}

void Snake::setDirection(Direction _direction) {
    direction = _direction;
}