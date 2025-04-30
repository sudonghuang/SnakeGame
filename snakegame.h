#ifndef SNAKEGAME_H
#define SNAKEGAME_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class Snakegame;
}
QT_END_NAMESPACE

class Snakegame : public QMainWindow
{
    Q_OBJECT

public:
    Snakegame(QWidget *parent = nullptr);
    ~Snakegame();

private:
    Ui::Snakegame *ui;
};
#endif // SNAKEGAME_H
