#ifndef BOARD_H
#define BOARD_H

#include <QWidget>
#include "stone.h"

class Board : public QWidget
{
    Q_OBJECT
public:
    explicit Board(QWidget *parent = nullptr);
    virtual void paintEvent(QPaintEvent*);
    void mouseReleaseEvent(QMouseEvent*);

    void drawStone(QPainter&, int);
    QPoint center(int, int);
    QPoint center(int);
    QRect getRect(int);
    bool getRowCol(QPoint, int&, int&);
    bool canMove(int, int, int, int);
    bool canMoveJiang(int, int, int, int);
    bool canMoveShi(int, int, int, int);
    bool canMoveXiang(int, int, int, int);
    bool canMoveChe(int, int, int, int);
    bool canMoveMa(int, int, int, int);
    bool canMovePao(int, int, int, int);
    bool canMoveBing(int, int, int, int);
    bool judge(int, int, int, int);
    bool existStone(int, int);   // judge (row, col) exist stone?
public:
    Stone _stone[32];
    int d=60;
    int _selectid;
    bool isRedWalk;
signals:

public slots:
};

#endif // BOARD_H
