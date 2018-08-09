#ifndef BOARD_H
#define BOARD_H

#include <QWidget>
#include "Stone.h"
#include <QPainter>
#include <QMouseEvent>
class Board : public QWidget
{
    Q_OBJECT
public:
    explicit Board(QWidget *parent = 0);
    ~Board();
    void paintEvent(QPaintEvent *);
    void drawStone(QPainter &,int);
    void mouseReleaseEvent(QMouseEvent *);
    bool canMove(int,int,int,int);
    bool canMoveche(int,int,int,int);
    bool canMovema(int,int,int,int);
    bool canMovexiang(int,int,int,int);
    bool canMoveshi(int,int,int,int);
    bool canMovejiang(int,int,int,int);
    bool canMovepao(int,int,int,int);
    bool canMovebin(int,int,int,int);
    bool isBottonSide(int);

    int relation (int ,int,int,int);
    int countStone(int,int,int,int);
    int getStoneId(int,int);

    QPoint getRowCol(QPoint);
    QPoint center(int ,int);
    QPoint center(int);



    const int _off;
    const int _rad;
    Stone _s[32];
    int _selId;
    bool redTurn;


signals:

public slots:
};

#endif // BOARD_H
