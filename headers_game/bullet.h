#ifndef BULLET_H
#define BULLET_H
#include "config.h"
#include <QPixmap>

class MainScene;
class MyPlane;
class CommonEnemyPlane;
class ShootEnemyPlane;
class ScreenClear;
class Laser;
class Missle;
class Boss;

class Bullet
{ 
    friend class MainScene;
    friend class MyPlane;
    friend class ShootEnemyPlane;
    friend class ScreenClear;
    friend class Laser;
    friend class Missle;
    friend class Boss;
public:
    Bullet();

    //更新子弹坐标
    virtual void updatePosition() = 0;

    void setBulletPath(QString path);

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

class BossBUlet : public Bullet
{
public:
    void updatePosition();
};

#endif // BULLET_H
