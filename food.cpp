#include "food.h"
#include <QRandomGenerator>
#include<QList>
Food::Food()
{
    position = QPoint(0, 0);
}

void Food::generateNew(const QList<QPoint>& snakeBody, int maxX, int maxY)
{
    QPoint newPos;
    do {
        newPos.setX(QRandomGenerator::global()->bounded(maxX));
        newPos.setY(QRandomGenerator::global()->bounded(maxY));
    } while (snakeBody.contains(newPos));

    position = newPos;
}

QPoint Food::getPosition() const
{
    return position;
}
