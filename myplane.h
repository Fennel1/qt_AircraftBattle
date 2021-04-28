#ifndef MYPLANE_H
#define MYPLANE_H
#include <QPixmap>
#include "bomb.h"
#include "bullet.h"

class MainScene;

class MyPlane : public Bomb
{
    friend class MainScene;
public:
    MyPlane();
    MyPlane(QString bombPath);
    //发射子弹
    void shoot();
    //设置飞机位置
    void setPosition(int x, int y);

    //飞机死亡
    void death();

private:
    //飞机资源 对象
    QPixmap Plane;

    //飞机坐标
    int X;
    int Y;

    //飞机的矩形边框
    QRect rect;

    //弹匣
    MyBullet bullets[BULLET_NUM];

    //发射间隔记录
    int recorder;

    //发射子弹
    bool shootflag;

    //飞机移动方向
    int direction_w;
    int direction_s;
    int direction_a;
    int direction_d;
    bool pressflag_w;
    bool pressflag_s;
    bool pressflag_a;
    bool pressflag_d;

    //飞机死亡
    bool isdeath;

    //飞机生命值
    int health;
};


#endif // MYPLANE_H
