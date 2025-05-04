#ifndef SNAKE_H
#define SNAKE_H

#include <QList>
#include <QPoint>

class Snake
{
public:
    enum Direction { UP, DOWN, LEFT, RIGHT };

    Snake();
    void move();
    void grow();
    bool checkCollision(const QPoint &point) const;
    bool checkSelfCollision() const;
    void setDirection(Direction newDirection);
    Direction getDirection() const;
    const QList<QPoint>& getBody() const;
    QPoint getHead() const;

private:
    QList<QPoint> body;
    Direction direction;
};

#endif // SNAKE_H
