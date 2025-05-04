#ifndef FOOD_H
#define FOOD_H

#include <QPoint>

class Food
{
public:
    Food();
    void generateNew(const QList<QPoint>& snakeBody, int maxX, int maxY);
    QPoint getPosition() const;

private:
    QPoint position;
};

#endif // FOOD_H
