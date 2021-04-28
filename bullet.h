#ifndef BULLET_H
#define BULLET_H
#include "config.h"
#include <QPixmap>

class MainScene;
class MyPlane;
class CommonEnemyPlane;
class ShootEnemyPlane;

class Bullet
{ 
    friend class MainScene;
    friend class MyPlane;
    friend class ShootEnemyPlane;
public:
    Bullet();

    //更新子弹坐标
    virtual void updatePosition() = 0;

protected:
    //子弹资源对象
    QPixmap bullet;
    //子弹坐标
    int X;
    int Y;
    //子弹移动速度
    int speed;
    //子弹是否闲置
    bool free;
    //子弹的矩形边框（用于碰撞检测）
    QRect rect;
};

class MyBullet : public Bullet
{
public:
    void updatePosition();
};

class EnemyBullet : public Bullet
{
public:
    void updatePosition();
};

#endif // BULLET_H
