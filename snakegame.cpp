#include "snakegame.h"
#include "./ui_snakegame.h"

Snakegame::Snakegame(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Snakegame)
{
    ui->setupUi(this);
}

Snakegame::~Snakegame()
{
    delete ui;
}
