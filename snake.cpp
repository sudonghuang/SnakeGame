#include "snake.h"
#include <QRandomGenerator>

Snake::Snake()
{
    // 初始化蛇的位置在屏幕中央
    body.append(QPoint(15, 10));
    body.append(QPoint(14, 10));
    body.append(QPoint(13, 10));
    direction = RIGHT;
}

void Snake::move()
{
    QPoint newHead = body.first();

    switch (direction) {
    case UP:
        newHead.setY(newHead.y() - 1);
        break;
    case DOWN:
        newHead.setY(newHead.y() + 1);
        break;
    case LEFT:
        newHead.setX(newHead.x() - 1);
        break;
    case RIGHT:
        newHead.setX(newHead.x() + 1);
        break;
    }

    body.prepend(newHead);
    body.removeLast();
}

void Snake::grow()
{
    QPoint tail = body.last();
    body.append(tail);
}

bool Snake::checkCollision(const QPoint &point) const
{
    return body.contains(point);
}

bool Snake::checkSelfCollision() const
{
    QPoint head = body.first();
    for (int i = 1; i < body.size(); ++i) {
        if (body[i] == head) {
            return true;
        }
    }
    return false;
}

void Snake::setDirection(Direction newDirection)
{
    // 防止180度转向
    if ((direction == UP && newDirection == DOWN) ||
        (direction == DOWN && newDirection == UP) ||
        (direction == LEFT && newDirection == RIGHT) ||
        (direction == RIGHT && newDirection == LEFT)) {
        return;
    }
    direction = newDirection;
}

Snake::Direction Snake::getDirection() const
{
    return direction;
}

const QList<QPoint>& Snake::getBody() const
{
    return body;
}

QPoint Snake::getHead() const
{
    return body.first();
}
