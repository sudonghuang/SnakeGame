#include "snakegame.h"
#include <QPainter>
#include <QMessageBox>

SnakeGame::SnakeGame(QWidget *parent)
    : QMainWindow(parent)
{
    setFixedSize(GAME_WIDTH * CELL_SIZE, GAME_HEIGHT * CELL_SIZE);
    setWindowTitle("贪吃蛇游戏");

    snake = new Snake();
    food = new Food();
    timer = new QTimer(this);

    connect(timer, &QTimer::timeout, this, &SnakeGame::gameLoop);

    initGame();
}

SnakeGame::~SnakeGame()
{
    delete snake;
    delete food;
}

void SnakeGame::initGame()
{
    score = 0;
    gameOver = false;
    gameStarted = false;
    currentSpeed = INITIAL_SPEED;

    // 重置蛇的位置和大小
    delete snake;
    snake = new Snake();

    food->generateNew(snake->getBody(), GAME_WIDTH, GAME_HEIGHT);
    timer->stop();
}

void SnakeGame::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);

    // 绘制背景
    painter.fillRect(rect(), Qt::black);

    drawGame(painter);
    drawScore(painter);

    if (!gameStarted) {
        drawStartMessage(painter);
    } else if (gameOver) {
        drawGameOverMessage(painter);
    }
}

void SnakeGame::drawGame(QPainter &painter)
{
    // 绘制蛇
    painter.setBrush(Qt::green);
    painter.setPen(Qt::NoPen);

    for (const QPoint &point : snake->getBody()) {
        painter.drawRect(point.x() * CELL_SIZE, point.y() * CELL_SIZE,
                         CELL_SIZE - 1, CELL_SIZE - 1);
    }

    // 绘制食物
    painter.setBrush(Qt::red);
    QPoint foodPos = food->getPosition();
    painter.drawEllipse(foodPos.x() * CELL_SIZE, foodPos.y() * CELL_SIZE,
                        CELL_SIZE - 1, CELL_SIZE - 1);
}

void SnakeGame::drawScore(QPainter &painter)
{
    painter.setPen(Qt::white);
    painter.setFont(QFont("Arial", 16));
    painter.drawText(10, 30, QString("得分: %1").arg(score));
    painter.drawText(10, 60, QString("速度: %1").arg((INITIAL_SPEED - currentSpeed) / SPEED_STEP + 1));
}

void SnakeGame::drawStartMessage(QPainter &painter)
{
    painter.setPen(Qt::white);
    painter.setFont(QFont("Arial", 20));
    QString message = "按空格键开始游戏\n"
                      "方向键控制移动\n"
                      "+/- 调整速度";
    painter.drawText(rect(), Qt::AlignCenter, message);
}

void SnakeGame::drawGameOverMessage(QPainter &painter)
{
    painter.setPen(Qt::white);
    painter.setFont(QFont("Arial", 20));
    QString message = QString("游戏结束！\n得分：%1\n点击重新开始").arg(score);
    painter.drawText(rect(), Qt::AlignCenter, message);
}

void SnakeGame::keyPressEvent(QKeyEvent *event)
{
    if (!gameStarted) {
        if (event->key() == Qt::Key_Space) {
            gameStarted = true;
            timer->start(currentSpeed);
        }
        return;
    }

    if (gameOver) {
        if (event->key() == Qt::Key_Space) {
            initGame();
            gameStarted = true;
            timer->start(currentSpeed);
        }
        return;
    }

    switch (event->key()) {
    case Qt::Key_Up:
        snake->setDirection(Snake::UP);
        break;
    case Qt::Key_Down:
        snake->setDirection(Snake::DOWN);
        break;
    case Qt::Key_Left:
        snake->setDirection(Snake::LEFT);
        break;
    case Qt::Key_Right:
        snake->setDirection(Snake::RIGHT);
        break;
    case Qt::Key_Plus:
    case Qt::Key_Equal:
        adjustSpeed(true);
        break;
    case Qt::Key_Minus:
        adjustSpeed(false);
        break;
    }
}

void SnakeGame::mousePressEvent(QMouseEvent *event)
{
    if (gameOver && event->button() == Qt::LeftButton) {
        initGame();
        gameStarted = true;
        timer->start(currentSpeed);
    }
}

void SnakeGame::adjustSpeed(bool increase)
{
    if (increase && currentSpeed > MIN_SPEED) {
        currentSpeed -= SPEED_STEP;
    } else if (!increase && currentSpeed < INITIAL_SPEED) {
        currentSpeed += SPEED_STEP;
    }
    timer->setInterval(currentSpeed);
}

void SnakeGame::gameLoop()
{
    if (gameOver || !gameStarted) {
        return;
    }

    snake->move();
    checkCollision();
    update();
}

void SnakeGame::checkCollision()
{
    QPoint head = snake->getHead();

    // 检查是否撞墙
    if (head.x() < 0 || head.x() >= GAME_WIDTH ||
        head.y() < 0 || head.y() >= GAME_HEIGHT) {
        gameOver = true;
        timer->stop();
        return;
    }

    // 检查是否撞到自己
    if (snake->checkSelfCollision()) {
        gameOver = true;
        timer->stop();
        return;
    }

    // 检查是否吃到食物
    if (head == food->getPosition()) {
        snake->grow();
        score += 10;
        food->generateNew(snake->getBody(), GAME_WIDTH, GAME_HEIGHT);
    }
}
