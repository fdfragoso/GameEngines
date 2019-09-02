#pragma once

class SnakeBody;

class Snake {
public:
    Snake();

    void init(int initialLength, int x, int y, int moveX, int moveY);

    void move();

    void grow();

    // do not allow the movedirection to be the opposite of the current direction
    void setMoveDirection(int moveX, int moveY);

    bool collide(int x, int y);
private:
    SnakeBody* snakeHead = nullptr;
    int moveX = 1;
    int moveY = 0;
    int length;
    friend class SnakeGUI;
};

