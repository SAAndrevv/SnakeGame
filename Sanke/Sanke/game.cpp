#include "Game.h"
#include <iostream>
#include <thread>

bool isLose = false;

Game::Game() {   
    snake = new Snake(SIZE_FIELD);
    int apple_x = 0;
    int apple_y = 0;
    std::srand(std::time(nullptr));
    inGame = true;
    targetBonus = false;
    
}

void Game::Tick(Direction dir, Packet pack) {
    packGet = pack;  
    if (targetBonus) {
        std::thread thr(&Game::bonusOnSnake, this);
        thr.detach();
    }
    if (snake->Move(dir))
        isLose = true;
    generateBonus();
    
}


void Game::generateBonus() {
    static bool triger;
    if (idSendPack == 1)
        triger = true;
    else if (packGet.id == 1) {
        triger = false;

    }
    
    if(triger){
        int rand = std::rand() % 10000;
        if (rand <= 10) {
            int bonusId = std::rand() %  3; 
            int x = std::rand() % SIZE_FIELD + 1;
            int y = std::rand() % SIZE_FIELD + 1;
            std::array<short int, 3> tmp{ bonusId, x, y };
            bonus.push_back(tmp);
        }
    }
    else {
        bonus = packGet.bonus;
    }
       
}

Packet Game::generatePack(int id) {
    idSendPack = id;

    Packet tmp;   
    tmp.id = id;
    tmp.apple[0] = apple_x;
    tmp.apple[1] = apple_y;
    tmp.posX = snake->getXVector();
    tmp.posY = snake->getYVector();
    tmp.dots = snake->getDots();
    tmp.idColor = idColor;
    tmp.name = name;
    tmp.bonus = bonus;

    return tmp;   
}

void Game::setName(std::string myName) {
    name = myName;
}

    
void Game::appleFromHost(Packet pack) {
    apple_x = pack.apple[0];
    apple_y = pack.apple[1];
}


void Game::generateApple() {
    // От 1 до SIZE_FIELD включительно

    apple_x = std::rand() % SIZE_FIELD + 1;
    
    apple_y = std::rand() % SIZE_FIELD + 1;
    	
}

bool Game::checkCollision() {

    if (snake->collisionWithAnotherSanke(packGet)){
        isLose = true;
    }
        int xHead = snake->getXPos(0);
        int yHead = snake->getYPos(0);

        if ((xHead == apple_x) && (yHead == apple_y)) {

            snake->addDots(1);
            generateApple();
            return true;   
        }
        int i = 0;
        for (auto& bon : bonus) {
            if ((xHead == bon[1]) && (yHead == bon[2])) {
                switch (bon[0])
                {
                case(0): // ускорение
                    snake->setDelay(0.02f);
                    break;
                case(1): //увеличение змейки
                    snake->addDots(3);
                    break;
                case(3):
                    targetBonus = true;
                default:
                    break;
                }
                bonus.erase(bonus.begin() + i);
                return true;
                

            }
            i++;
        }

        return false;   
    
}
int Game::getDots() {
    return snake->getDots();
}

sf::Color Game::colorReturner(int idColor) const {
    switch (idColor)
    {
    case(1):
        return sf::Color::White;
        break;
    case(2):
        return sf::Color::Red;
        break;
    case(3):
        return sf::Color::Magenta;
        break;
    case(4):
        return sf::Color::Yellow;
        break;
    default:
        return sf::Color::Red;
        break;
    }
}

void Game::drawAnotherSnake(Packet pac){
    packGet = pac;
}

void Game::setIdColor(int idColor_) {
    idColor = idColor_;
}

void Game::bonusOnSnake() {
    targetBonus = false;
    sf::Clock time;
    sf::Time bonusTimer = sf::seconds(20);
    int origIdColor = idColor;
    idColor = packGet.idColor;
    while ((bonusTimer - time.getElapsedTime()).asSeconds() > 0);
        
    
    idColor = origIdColor;

}


void Game::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	sf::Color color = sf::Color(200, 100, 200);

	sf::RectangleShape shape(sf::Vector2f(W_WIDTH, W_HEIGHT));
	shape.setOutlineThickness(2.f);
	shape.setOutlineColor(color);
	shape.setFillColor(sf::Color::Transparent);
	shape.setPosition(0, 0);

	target.draw(shape, states);

	sf::CircleShape circle;
	circle.setRadius(DOT_SIZE / 2);
	circle.setFillColor(sf::Color::Blue);
	
	if (inGame) {

       
        circle.setPosition(apple_x * DOT_SIZE, apple_y * DOT_SIZE);
        target.draw(circle, states);
        circle.setFillColor(colorReturner(idColor));

        
        int dots = snake->getDots();
            //std::cout << dots;

        for (int i = 0; i < dots; i++)
        {
            int x = snake->getXPos(i);
            int y = snake->getYPos(i);

            circle.setPosition(x * DOT_SIZE, y * DOT_SIZE);
            target.draw(circle, states);

        }

        dots = packGet.dots;
        circle.setFillColor(colorReturner(packGet.idColor));
        for (int i = 0; i < dots; ++i) {
            circle.setPosition(packGet.posX[i] * DOT_SIZE, packGet.posY[i] * DOT_SIZE);
            target.draw(circle, states);
        }

        for (auto& bon : bonus) {
            switch (bon[0])
            {
            case(0): // ускорение
                circle.setFillColor(sf::Color::Green);
                break;
            case(1): //увеличение змейки
                circle.setFillColor(sf::Color::Yellow);
                break;
            case(3): // маскировка
                circle.setFillColor(sf::Color::White); 
                break;
            }
            circle.setPosition(bon[1] * DOT_SIZE, bon[2] * DOT_SIZE);
            target.draw(circle, states);
           
        }
        
	}
}


Game::~Game() {
    
    delete snake;
    
}