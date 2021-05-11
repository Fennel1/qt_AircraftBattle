#include "headers_game/data.h"

Data::Data()
{
    score = 0;
    coin = 0;
    destorycommonenemy = 0;
    destoryshootenemy = 0;
    myplaneshoottime = 0;
    crashtime = 0;
    beshottime = 0;
    destroyedbycommonenemy = 0;
    destroyedbyshootenemy = 0;
    movingdistance = 0;
    playtime = new QTime(0, 0, 0); //初始化时间
    isstart = false;
}

Data& Data::operator=(const Data &d)
{
    if (this != &d)
    {
        score = d.score;
        coin = d.coin;
        destorycommonenemy = d.destorycommonenemy;
        destoryshootenemy = d.destoryshootenemy;
        myplaneshoottime = d.myplaneshoottime;
        crashtime = d.crashtime;
        beshottime = d.beshottime;
        destroyedbycommonenemy = d.destroyedbycommonenemy;
        destroyedbyshootenemy = d.destroyedbyshootenemy;
        movingdistance = d.movingdistance;
        //playtime = new QTime(0, 0, 0);
        isstart = d.isstart;
    }
    return *this;
}

//Data Data::operator+=(const Data &d)
//{

//}
