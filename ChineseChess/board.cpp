#include <QPainter>
#include "board.h"
#include <QMouseEvent>
#include <QDebug>
#include <QtMath>
#include <iostream>


Board::Board(QWidget *parent) : QWidget(parent)
{
    for( int i=0; i<32; i++){
        this->_stone[i].init(i);
    }
    this->_selectid = -1;
    isRedWalk = true;
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
        if(i == _selectid)
               painter.setBrush(QBrush(Qt::gray));
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
    if(this->_stone[id]._dead)
        return;
    painter.drawEllipse(this->center(id), d/2, d/2);
    /*在绘制汉字的时候，注意控制文字的位置,  以及颜色*/
    painter.setFont(QFont("system", d/2, 700));
    painter.drawText(this->getRect(id), this->_stone[id].getText(), QTextOption(Qt::AlignCenter));

}


bool Board::getRowCol(QPoint pt, int& row, int& col){
    int x = pt.x();
    int y = pt.y();
    std::cout << x << ": " << y << std::endl;
    if(d/2<=x && x<=9*d+d/2 && d/2<=y && y<=10*d+d/2){
        col = (x%d<=d/2)?x/d-1:x/d;
        row = (y%d<=d/2)?y/d-1:y/d;
        return true;
    }
    return false;
}

bool Board::canMoveJiang(int selectid, int row, int col, int killid){
    /* xian ding sigongge*/
    if(_stone[selectid]._red){
        if(row>=3)return false;
    }
    else{
        if(row<7)return false;
    }
    if(col<3||col>5)
        return false;
    int x_len = qAbs(_stone[selectid]._row - row);
    int y_len = qAbs(_stone[selectid]._col - col);
    if(x_len + y_len == 1)
        return true;
    return false;
}
bool Board::canMoveShi(int selectid, int row, int col, int killid){
    if(_stone[selectid]._red){
        if(row>=3)return false;
    }
    else{
        if(row<7)return false;
    }
    if(col<3||col>5)
        return false;
    int x_len = qAbs(_stone[selectid]._row - row);
    int y_len = qAbs(_stone[selectid]._col - col);
    if(x_len==1 && y_len == 1)
        return true;
    return false;
}
bool Board::canMoveXiang(int selectid, int row, int col, int killid){
    int x_len = qAbs(_stone[selectid]._row - row);
    int y_len = qAbs(_stone[selectid]._col - col);
    /* bie xiang yan */
    if(x_len == 2 && y_len == 2)
        return true;
    return false;
}
bool Board::canMoveChe(int selectid, int row, int col, int killid){
    return true;
}
bool Board::canMoveMa(int selectid, int row, int col, int killid){
    return true;
}
bool Board::canMovePao(int selectid, int row, int col, int killid){
    return true;
}
bool Board::canMoveBing(int selectid, int row, int col, int killid){
    /* guo he keyi hengzhe zou row pos */
    return true;
}

bool Board::judge(int selectid, int row, int col, int killid){
    bool res = false;
    switch (_stone[selectid]._type) {
        case Stone::JIANG:
            res = canMoveJiang(selectid, row, col, killid);
            break;
        case Stone::SHI:
            res = canMoveShi(selectid, row, col, killid);
            break;
        case Stone::XIANG:
            res = canMoveXiang(selectid, row, col, killid);
            break;
        case Stone::CHE:
            res = canMoveChe(selectid, row, col, killid);
            break;
        case Stone::MA:
            res = canMoveMa(selectid, row, col, killid);
            break;
        case Stone::PAO:
            res = canMovePao(selectid, row, col, killid);
            break;
        case Stone::BING:
            res = canMoveBing(selectid, row, col, killid);
            break;
    }
    return res;
}
bool Board::canMove(int selectid, int row, int col, int clickid){
    qDebug() << clickid << "\n";
    if((clickid == -1)){
        return judge(selectid, row, col, clickid);
    }
    if(_stone[selectid]._red == _stone[clickid]._red){
        this->_selectid = clickid;
        update();
        return false;
    }
    else{
        return judge(selectid, row, col, clickid);
    }
}
void Board::mouseReleaseEvent(QMouseEvent* event){
    QPoint pt = event->pos();
    int row, col, i;
    bool bRet = this->getRowCol(pt, row, col);
    if(!bRet)
        return;
    int clickid = -1;
    for( i=0; i<32; i++){
        if(_stone[i]._row == row && _stone[i]._col == col && !_stone[i]._dead ){
            break;
        }
    }
    if(i<32){
        // yes
        clickid = i;
    }
    if(this->_selectid == -1){
        if(clickid != -1){
            if(isRedWalk == _stone[clickid]._red){
                _selectid = clickid;
                update();
            }
        }
    }
    else{
        if(canMove(_selectid, row, col, clickid)){
            this->_stone[_selectid]._row = row;
            this->_stone[_selectid]._col = col;
            if(clickid != -1){
                this->_stone[clickid]._dead = true;
            }
            this->_selectid = -1;
            update();
            isRedWalk = !isRedWalk;
        }
    }
}
