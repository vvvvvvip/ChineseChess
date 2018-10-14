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
    void drawStone(QPainter&, int);
    QPoint center(int, int);
    QPoint center(int);
    QRect getRect(int);

public:
    Stone _stone[32];
    int d=60;
signals:

public slots:
};

#endif // BOARD_H
