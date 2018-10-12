#include <QPainter>
#include "board.h"

Board::Board(QWidget *parent) : QWidget(parent)
{

}

void Board::paintEvent(QPaintEvent* event){
    QPainter painter(this);
    /* 11 h lines */
    int d=60;
    for( int i=0; i<10; i++){
        painter.drawLine(QPoint(d, d*(i+1)), QPoint(9*d, d*(i+1)));
    }
    /* 9 v lines */
    for( int i=0; i<9; i++ ){
        if(i!=0 && i!=8){
            painter.drawLine(QPoint((i+1)*d, d), QPoint((i+1)*d, 5*d));
            painter.drawLine(QPoint((i+1)*d, 6*d), QPoint((i+1)*d, 10*d));
        }
        else{
            painter.drawLine(QPoint((i+1)*d, d), QPoint((i+1)*d, 10*d));
        }
    }
    /* x */
    painter.drawLine(QPoint(4*d, d), QPoint(6*d, 3*d));
    painter.drawLine(QPoint(4*d, 3*d), QPoint(6*d, d));
    painter.drawLine(QPoint(4*d, 8*d), QPoint(6*d, 10*d));
    painter.drawLine(QPoint(4*d, 10*d), QPoint(6*d, 8*d));
}
