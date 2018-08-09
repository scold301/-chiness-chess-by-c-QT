#ifndef STONE_H
#define STONE_H
#include <QString>

class Stone
{
public:
    Stone();
    ~Stone();



    enum TYPE{che,ma,xiang,shi,jiang,pao,bin};
    void init(int);
    QString getText();



    int _row;
    int _col;
    int _id;
    bool _dead;
    bool _red;

    TYPE _type;



};

#endif // STONE_H
