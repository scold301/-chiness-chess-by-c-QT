#include "Board.h"
//#include <QPainter>


Board::Board(QWidget *parent) : QWidget(parent),_off(40),_rad(20),_selId(-1),redTurn(true)
{
    for(int i=0;i<32;++i){
        _s[i].init(i);
    }



}

Board::~Board()
{

}
bool Board::isBottonSide(int id){
    return _s[id]._red;
}
QPoint Board::center(int id){
    return center(_s[id]._row,_s[id]._col);

}

QPoint Board::center(int row,int col){
    QPoint ret;
    ret.rx()=col*2*_rad+_off;
    ret.ry()=row*2*_rad+_off;
    return ret;
}


void Board::paintEvent(QPaintEvent *){
    QPainter painter(this);
    //画10条横线
    for(int i=0;i<10;++i){

        painter.drawLine(QPoint(_off,_off+i*2*_rad),QPoint(_off+8*2*_rad,_off+i*2*_rad));

    }
    //画9条竖线
    for(int i=0;i<9;++i){
        if(i==0||i==8){

            painter.drawLine(QPoint(_off+i*2*_rad,_off),QPoint(_off+i*2*_rad,_off+9*2*_rad));
        }
        else{
            painter.drawLine(QPoint(_off+i*2*_rad,_off),QPoint(_off+i*2*_rad,_off+4*2*_rad));
            painter.drawLine(QPoint(_off+i*2*_rad,_off+5*2*_rad),QPoint(_off+i*2*_rad,_off+9*2*_rad));

        }

    }
    //画九宫格
    painter.drawLine(QPoint(_off+3*2*_rad,_off),QPoint(_off+5*2*_rad,_off+2*2*_rad));

    painter.drawLine(QPoint(_off+3*2*_rad,_off+2*2*_rad),QPoint(_off+5*2*_rad,_off));

    painter.drawLine(QPoint(_off+3*2*_rad,_off+7*2*_rad),QPoint(_off+5*2*_rad,_off+9*2*_rad));
    painter.drawLine(QPoint(_off+3*2*_rad,_off+9*2*_rad),QPoint(_off+5*2*_rad,_off+7*2*_rad));

    //绘制32个棋子
    for(int i=0;i<32;++i){
        drawStone(painter,i);
    }
}


void Board::drawStone(QPainter & painter, int id){
    if(_s[id]._dead)
        return;
    QPoint c=center(id);
    painter.setBrush(Qt::yellow);
    painter.setPen(Qt::black);
    if(_selId==id)
        painter.setBrush(Qt::gray);


    painter.drawEllipse(c,_rad,_rad);
    if(_s[id]._red)
        painter.setPen(Qt::red);
    painter.setFont(QFont("system",_rad,700));

    QRect rect=QRect(c.x()-_rad,c.y()-_rad,_rad*2,_rad*2);
    painter.drawText(rect,_s[id].getText(),QTextOption(Qt::AlignCenter));
}

bool Board::canMove(int moveid,int row,int col,int killid){
    if(killid!=-1&&_s[moveid]._red==_s[killid]._red){
        _selId=killid;
        update();

        return false;}
    switch(_s[moveid]._type){
    case Stone::che:
        return canMoveche(moveid,row,col,killid);
        break;
    case Stone::ma:
        return canMovema(moveid,row,col,killid);
        break;
    case Stone::xiang:
        return canMovexiang(moveid,row,col,killid);
        break;
    case Stone::shi:
        return canMoveshi(moveid,row,col,killid);
        break;
    case Stone::jiang:
        return canMovejiang(moveid,row,col,killid);
        break;
    case Stone::pao:
        return canMovepao(moveid,row,col,killid);
        break;
    case Stone::bin:
        return canMovebin(moveid,row,col,killid);
        break;
    }

}
int Board::relation (int row1 ,int col1,int row,int col){
    int disr=row1-row;
    int disc=col1-col;
    return 10*abs(disr)+abs(disc);
}
int Board::getStoneId(int row, int col){

    for( int i=0;i<32;++i){

        if(_s[i]._row==row&&_s[i]._col==col&&_s[i]._dead==false){
             return i;
        }

    }
    return -1;
}

int Board::countStone(int row1,int col1,int row,int col){
    if(row1!=row&&col1!=col){
        return -1;
    }
    int cnt=0;
    if(row1==row){
        int min=col1<col?col1:col;
        int max=col1<col?col:col1;
        for(int i=min+1;i<max;i++){
            if(getStoneId(row,i)!=-1)
                ++cnt;
        }
    }
    if(col1==col){
        int min=row1<row?row1:row;
        int max=row1<row?row:row1;
        for(int i=min+1;i<max;i++){
            if(getStoneId(i,col)!=-1)
                ++cnt;
        }
    }
    return cnt;
}

bool Board::canMoveche(int moveid,int row,int col,int killid){
    if(countStone(_s[moveid]._row,_s[moveid]._col,row,col)==0){
        return true;
    }

}

bool Board::canMovema(int moveid,int row,int col,int killid){
    int re=relation(_s[moveid]._row,_s[moveid]._col,row,col);
    if (re==12||re==21){
        if(abs(_s[moveid]._row-row)==1){
            return getStoneId(_s[moveid]._row,(_s[moveid]._col+col)/2)==-1;
        }
        if(abs(_s[moveid]._col-col)==1){
            return getStoneId((_s[moveid]._row+row)/2,  _s[moveid]._col)==-1;
        }
    }
    return false;
}

bool Board::canMovexiang(int moveid,int row,int col,int killid){
    int re=relation(_s[moveid]._row,_s[moveid]._col,row,col);
    if(re!=22){
        return false;
    }
    if(getStoneId((_s[moveid]._row+row)/2,(_s[moveid]._col+col)/2)!=-1)
        return false;
    if(isBottonSide(moveid)){
        if(row<5)return false;
    }else{
        if(row>4)return false;
    }
    return true;

}

bool Board::canMoveshi(int moveid,int row,int col,int killid){
    int re=relation(_s[moveid]._row,_s[moveid]._col,row,col);
    if(re!=11){
        return false;
    }
    if(col<3||col>5){
        return false;
    }
    if(isBottonSide(moveid)){
        if(row<7)return false;
    }else{
        if(row>2)return false;
    }
    return true;

}

bool Board::canMovejiang(int moveid,int row,int col,int killid){
   /*if(killid!=-1&&_s[killid]._type==Stone::jiang){
        return canMoveche(moveid,row,col,killid);
    }*/
    int re=relation(_s[moveid]._row,_s[moveid]._col,row,col);
    if(re!=1&&re!=10){
        return false;
    }
    if(col<3||col>5){
        return false;
    }
    if(isBottonSide(moveid)){
        if(row<7)return false;
    }else{
        if(row>2)return false;
    }
    int jid=(moveid==4)?20:4;
    if(canMoveche(jid,row,col,killid)){
        return false;
    }


    return true;
}

bool Board::canMovepao(int moveid,int row,int col,int killid){
    if(killid==-1){
        if(countStone(_s[moveid]._row,_s[moveid]._col,row,col)==0){
            return true;
        }
    }else{
        if(countStone(_s[moveid]._row,_s[moveid]._col,row,col)==1){
            return true;
        }
    }
    return false;
}

bool Board::canMovebin(int moveid,int row,int col,int killid){
    int re=relation(_s[moveid]._row,_s[moveid]._col,row,col);
    if(isBottonSide(moveid)){
        if(_s[moveid]._row<row)
            return false;
        if(_s[moveid]._row<5){
            if(re!=1&&re!=10)
                return false;
        }
        else{
            if(row-_s[moveid]._row!=-1||_s[moveid]._col!=col){
                return false;
            }
        }
    }else{
        if(_s[moveid]._row>row)
            return false;
        if(_s[moveid]._row>4){
            if(re!=1&&re!=10)
                return false;
        }
        else{
            if(row-_s[moveid]._row!=1||_s[moveid]._col!=col){
                return false;
            }
        }
    }
    return true;

}

void Board::mouseReleaseEvent(QMouseEvent *ev){
    QPoint pt=ev->pos();
    pt=getRowCol(pt);
    int row,col,clickId=-1;

    row=pt.y();
    col=pt.x();

    clickId=getStoneId(row,col);


    /*for( int i=0;i<32;++i){

        if(_s[i]._row==row&&_s[i]._col==col&&_s[i]._dead==false){
             clickId=i;
            break;
        }

    }*/
    if(_selId==-1){
        if(redTurn==_s[clickId]._red){
            _selId=clickId;

            update();}
    }else{
        if(canMove(_selId,row,col,clickId)){

            _s[_selId]._row=row;
            _s[_selId]._col=col;
            if(clickId!=-1){
                _s[clickId]._dead=true;
            }
            redTurn=!redTurn;
            update();
            _selId=-1;
        }
    }

}

QPoint Board::getRowCol(QPoint pt){
    QPoint po;
    po.rx()=(pt.x()-_off+_rad)/(2*_rad);
    po.ry()=(pt.y()-_off+_rad)/(2*_rad);
    return po;
}
