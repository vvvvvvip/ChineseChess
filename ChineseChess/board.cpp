#include <QPainter>
#include "board.h"

Board::Board(QWidget *parent) : QWidget(parent)
{
    for( int i=0; i<32; i++){
        this->_stone[i].init(i);
    }
}


void Board::paintEvent(QPaintEvent* event){
    QPainter painter(this);
    /* 11 h lines */
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

    for( int i=0; i<32; i++){
        /* change bgc depend on i */
        if(i<16){
            painter.setBrush(QBrush(QColor(255, 0, 0)));
        }
        else{
            painter.setBrush(QBrush(QColor(0, 255, 0)));
        }
        this->drawStone(painter, i);
    }
}

QPoint Board::center(int x, int y){
    return QPoint((y+1)*d, (x+1)*d);
}

QPoint Board::center(int id){
    return this->center(this->_stone[id]._row, this->_stone[id]._col);
}

QRect Board::getRect(int id){
    QPoint tmp_p = this->center(id);
    return QRect(tmp_p.x()-d/2, tmp_p.y()-d/2, d, d);
}

void Board::drawStone(QPainter& painter, int id){
    // gen ju id lai hua
    painter.drawEllipse(this->center(id), d/2, d/2);
    /*在绘制汉字的时候，注意控制文字的位置,  以及颜色*/
    painter.setFont(QFont("system", d/2, 700));
    painter.drawText(this->getRect(id), this->_stone[id].getText(), QTextOption(Qt::AlignCenter));

}
