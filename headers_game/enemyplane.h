#ifndef ENEMYPLANE_H
#define ENEMYPLANE_H
#include <QPixmap>
#include "bomb.h"
#include "bullet.h"

class MainScene;
class ScreenClear;
class Laser;
class Missle;

class EnemyPlane : public Bomb
{
public:
    EnemyPlane();
    EnemyPlane(QString planepath, QString bombpath);

    //更新坐标
    void updatePosition();

    //飞机死亡
    void death();

    //设置飞机参数
    void setPlanePath(QString planepath);
    void setspeed();

protected:
    //敌机资源对象
    QPixmap enemy;

    //位置
    int X;
    int Y;

    //敌机的矩形边框（碰撞检测）
    QRect rect;

    //状态
    bool free;

    //速度
    int speed;

};



class CommonEnemyPlane : public EnemyPlane
{
    friend class MainScene;
    friend class ScreenClear;
    friend class Laser;
    friend class Missle;
public:
    CommonEnemyPlane();
    CommonEnemyPlane(QString planepath, QString bombpath);
};



class ShootEnemyPlane : public EnemyPlane
{
    friend class MainScene;
    friend class ScreenClear;
    friend class Laser;
    friend class Missle;
public:
    ShootEnemyPlane();
    ShootEnemyPlane(QString planepath, QString bombpath);
    //发射子弹
    void shoot();

    //更新坐标
    void updatePosition();

    //飞机参数设置
    void setbulletinterval(int interval);

protected:
    //弹匣
    EnemyBullet bullets[BULLET_NUM];

    //发射间隔记录
    int recorder;
    int bulletinterval;

};


class SpeedEnemyPlane : public EnemyPlane
{
    friend class MainScene;
    friend class ScreenClear;
    friend class Laser;
    friend class Missle;
public:
    SpeedEnemyPlane();
    SpeedEnemyPlane(QString planepath, QString bombpath);

    //更新坐标
    void updatePosition();

    //飞机参数设置
    void setBulletinterval(int interval);

private:
    int recorder;

    //飞机加速点
    int speeduppoint;

    //停顿判断
    bool ispause;
};


#endif // ENEMYPLANE_H
