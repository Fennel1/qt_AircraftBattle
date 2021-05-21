#ifndef MYPLANE_H
#define MYPLANE_H
#include <QPixmap>
#include "bomb.h"
#include "bullet.h"

class MainScene;
class Shield;

class MyPlane : public Bomb
{
    friend class MainScene;
    friend class Shield;
public:
    MyPlane();
    MyPlane(QString planepath, QString bombPath);
    //发射子弹
    void shoot();
    //设置飞机位置
    void setPosition(int x, int y);

    //飞机死亡
    void death();

    //设置飞机参数
    void setspeed(int speed);
    void sethealth(int health);
    void setplanePath(QString planepath);
    void setbulletinterval(int interval);

protected:
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
    int bulletinterval;

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
    //飞机速度
    int speed;
};

class CommonMyPlane : public MyPlane
{
    friend class MainScene;
public:
    CommonMyPlane();
    CommonMyPlane(QString planepath, QString bombpath);
};

#endif // MYPLANE_H
