#include "Snake.h"
#include <iostream>



Snake::Snake() {
    time = 0.0f;
    timer = 0.0f;
    delay = 0.0;
    
}

Snake::Snake(int start, int size_field) {
    sField = size_field;
    time = 0.0f;
    timer = 0.0f;
    delay = 0.2f;
   
	dots = 3;
    x.resize(dots + 1);
    y.resize(dots + 1);
    

	for (int i = 0; i < dots; ++i) {
		x[i] = start - i;
		y[i] = 5;
	}
}


bool Snake::Move(Direction direction) {
    
    time = clock.getElapsedTime().asSeconds();
    timer += time;
    clock.restart();

    if (timer > delay) {

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

void Snake::setXPos(int ind, int val){
    x[ind] = val;
}

void Snake::setYPos(int ind, int val) {
    y[ind] = val;
}

int Snake::getDots() const{
    return dots;
}

void Snake::addDots(int count) {
    dots += count;

    x.resize(dots + 1);
    y.resize(dots + 1);
    
}

//void Snake::setDirection(Direction _direction) {
    //direction = _direction;
//}

std::vector<short int> Snake::getXVector() {
    return x;
}

std::vector<short int> Snake::getYVector() {
    return y;
}
//void Snake::setXVector(std::vector<short int> xVect) {
    //x = xVect;
//}

//void Snake::setYVector(std::vector<short int> yVect) {
    //y = yVect;
//}

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
    return true;
}

//bool Snake::collisionWithAnotherSanke(Snake &snake) {
    //int lenghSnake = snake.getDots();

    //for (int i = 0; i < lenghSnake; ++i) {
        //if (x[0] == snake.getXPos(i) && y[0] == snake.getYPos(i))
            //return true;
    //}
   // return false;
//}