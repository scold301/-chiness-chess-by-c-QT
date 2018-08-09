#include "Stone.h"

Stone::Stone()
{





}

Stone::~Stone()
{

}

QString Stone::getText(){

    switch(_type){
    case che:
        return "车";
    case ma:
        return "马";
    case xiang:
        return "相";
    case shi:
        return "士";
    case jiang:
        return "将";
    case pao:
        return "炮";
    case bin:
        return "兵";
    }
    return "错误";
}
void Stone::init(int i){
    struct {
        int row;int col;TYPE type;
    }istone[16]={
    {0,0,che},{0,1,ma},{0,2,xiang},{0,3,shi},{0,4,jiang},{0,5,shi},{0,6,xiang},{0,7,ma},{0,8,che},{2,1,pao},{2,7,pao},
    {3,0,bin},{3,2,bin},{3,4,bin},{3,6,bin},{3,8,bin},
    }
        ;
    _id=i;
    _dead=false;
    _red=i<16;

    if(i<16){
        _row=9-istone[i].row;
        _col=8-istone[i].col;
        _type=istone[i].type;
    }
    if(i>=16){
        _row=istone[i-16].row;
        _col=istone[i-16].col;
        _type=istone[i-16].type;
    }
}
