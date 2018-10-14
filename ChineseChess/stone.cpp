#include "stone.h"

Stone::Stone()
{

}

Stone::~Stone(){

}

QString Stone::getText(){
    switch (this->_type) {
        case JIANG:
            return "将";
        case CHE:
            return "車";
        case PAO:
            return "炮";
        case MA:
            return "马";
        case SHI:
            return "士";
        case XIANG:
            return "象";
        case BING:
            return "兵";
        default:
            return "错误";
    }
}


void Stone::init(int id){
    _id = id;
    _dead = false;
    _red = id<16;

    if(_red){
        this->_row = StonePosMap[id].row;
        this->_col = StonePosMap[id].col;
        this->_type = StonePosMap[id].type;
    }
    else{
        this->_row = 9-StonePosMap[id-16].row;
        this->_col = 8-StonePosMap[id-16].col;
        this->_type = StonePosMap[id-16].type;
    }
}
