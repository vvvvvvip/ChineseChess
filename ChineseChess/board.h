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

public:
    Stone _stone[32];
    int d=60;
    int _selectid;
signals:

public slots:
};

#endif // BOARD_H
