#ifndef SNAKEGAME_H
#define SNAKEGAME_H

#include <QMainWindow>
#include <QTimer>
#include <QKeyEvent>
#include <QMouseEvent>
#include "snake.h"
#include "food.h"

class SnakeGame : public QMainWindow
{
    Q_OBJECT

public:
    SnakeGame(QWidget *parent = nullptr);
    ~SnakeGame();

protected:
    void paintEvent(QPaintEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;

private slots:
    void gameLoop();

private:
    static const int CELL_SIZE = 20;
    static const int GAME_WIDTH = 30;
    static const int GAME_HEIGHT = 20;
    static const int INITIAL_SPEED = 150;  // 初始速度（毫秒）
    static const int MIN_SPEED = 50;       // 最快速度
    static const int SPEED_STEP = 10;      // 速度调整步长

    Snake *snake;
    Food *food;
    QTimer *timer;
    int score;
    bool gameOver;
    bool gameStarted;
    int currentSpeed;

    void initGame();
    void checkCollision();
    void drawGame(QPainter &painter);
    void drawScore(QPainter &painter);
    void drawStartMessage(QPainter &painter);
    void drawGameOverMessage(QPainter &painter);
    void adjustSpeed(bool increase);
};

#endif // SNAKEGAME_H
