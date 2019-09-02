#include "Snake.hpp"
#include "SnakeBody.hpp"

#include <string>
#include <iostream>

Snake::Snake() {
}

void Snake::move(){                                                 // This is called every time the snake should move.
    int currentHeadPosX = snakeHead->x;
    int currentHeadPosY = snakeHead->y;

	snakeHead->moveTo(snakeHead->x + this->moveX, snakeHead->y + this->moveY);
    // todo move
}

void Snake::setMoveDirection(int moveX, int moveY) {                // This is called whenever one arrow key is pressed. Values are [-1,0,1] for x and y.
	if (snakeHead->totalSnakeBodies > 1 && this->moveX == -moveX && this->moveY == -moveY)
		return;
	this->moveX = moveX;
    this->moveY = moveY;
}

void Snake::init(int initialLength, int x, int y, int moveX, int moveY) {   // This is called every time the game starts or restarts. Make sure not to leak resources.
	delete snakeHead;
	length = initialLength;
    this->moveX = moveX;
    this->moveY = moveY;
    snakeHead = new SnakeBody(x,y);
}

void Snake::grow() {                                                // Should increment the length and append a SnakeBody
	length++;
	SnakeBody* nextBody = snakeHead;
	while (nextBody->next != nullptr) 
	{
		nextBody = nextBody->next;
	}
	nextBody->next = new SnakeBody(snakeHead->x, snakeHead->y);

}

bool Snake::collide(int x, int y) {                                 // Returns true if one of the SnakeBody objects has the position (x,y)
	SnakeBody* nextBody = snakeHead;
	while (nextBody->next != nullptr)
	{
		if (nextBody->next->x == x && nextBody->next->y == y) 
		{
			return true;
		}
		nextBody = nextBody->next;
		std::cout << "1 down; ";
	}
	return false;
}
