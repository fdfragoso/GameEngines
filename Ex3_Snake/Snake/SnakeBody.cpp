
#include "SnakeBody.hpp"

#include <string>
#include <iostream>

int SnakeBody::totalSnakeBodies = 0;

SnakeBody::SnakeBody(int x, int y) {
    this->x = x;
    this->y = y;
    totalSnakeBodies++;                                 // incremented every time a new SnakeBody is created
}

SnakeBody::~SnakeBody() {
	delete next;
    totalSnakeBodies--;                                 // decremented every time a new SnakeBody is created
}

void SnakeBody::moveTo(int x, int y) {
	if (next != nullptr) 
	{
		next->moveTo(this->x, this->y);
	}
	this->x = x;
    this->y = y;
}
