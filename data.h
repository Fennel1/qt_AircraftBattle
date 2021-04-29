#ifndef DATA_H
#define DATA_H
#include <QTime>
#include "myplane.h"

class MainScene;

class Data : public MyPlane
{
    friend class MainScene;
public:
    Data();

    Data& operator=(const Data &d);
    Data operator+=(const Data &d);

private:
    //得分
    int score;

    //金币
    int coin;

    //游戏时长
    QTime *playtime;
    bool isstart;

    //击毁敌机数
    int destorycommonenemy;
    int destoryshootenemy;

    //发射子弹数
    int myplaneshoottime;

    //与敌机碰撞次数
    int crashtime;
    //被敌机子弹击中次数
    int beshottime;

    //主机死亡
    //被普通敌机击毁次数
    int destroyedbycommonenemy;
    //被射击敌机击毁次数
    int destroyedbyshootenemy;

    //主机移动距离
    int movingdistance;
};

#endif // DATA_H
