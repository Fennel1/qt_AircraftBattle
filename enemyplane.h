#ifndef ENEMYPLANE_H
#define ENEMYPLANE_H
#include <QPixmap>
#include "bomb.h"
#include "bullet.h"

class MainScene;

class EnemyPlane : public Bomb
{
public:
    EnemyPlane();
    EnemyPlane(QString planepath, QString bombpath);

    //更新坐标
    void updatePosition();

    //飞机死亡
    void death();

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
public:
    CommonEnemyPlane();
    CommonEnemyPlane(QString planepath, QString bombpath);
};

class SpeedEnemyPlane : public EnemyPlane
{

};

class ShootEnemyPlane : public EnemyPlane
{
    friend class MainScene;
public:
    ShootEnemyPlane();
    ShootEnemyPlane(QString planepath, QString bombpath);
    //发射子弹
    void shoot();

    //更新坐标
    void updatePosition();

protected:
    //弹匣
    EnemyBullet bullets[BULLET_NUM];

    //发射间隔记录
    int recorder;

};

#endif // ENEMYPLANE_H
