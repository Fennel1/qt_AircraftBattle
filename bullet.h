#ifndef BULLET_H
#define BULLET_H
#include "config.h"
#include <QPixmap>

class MainScene;
class myPlane;
class EnemyPlane;

class Bullet
{ 
    friend class MainScene;
    friend class myPlane;
    friend class EnemyPlane;
public:
    Bullet();

    //更新子弹坐标
    virtual void updatePosition() = 0;

protected:
    //子弹资源对象
    QPixmap m_Bullet;
    //子弹坐标
    int m_X;
    int m_Y;
    //子弹移动速度
    int m_Speed;
    //子弹是否闲置
    bool m_Free;
    //子弹的矩形边框（用于碰撞检测）
    QRect m_Rect;
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
