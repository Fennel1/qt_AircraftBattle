#ifndef ENEMYPLANE_H
#define ENEMYPLANE_H
#include <QPixmap>
#include "bomb.h"
#include "bullet.h"

class MainScene;

class EnemyPlane : public Bomb
{
    friend class MainScene;
public:
    EnemyPlane();

    //更新坐标
    void updatePosition();

    //飞机死亡
    void death();

    //发射子弹
    void shoot();

protected:
    //敌机资源对象
    QPixmap m_enemy;

    //位置
    int m_X;
    int m_Y;

    //敌机的矩形边框（碰撞检测）
    QRect m_Rect;

    //状态
    bool m_Free;

    //速度
    int m_Speed;

    //弹匣
    EnemyBullet m_bullets[BULLET_NUM];

    //发射间隔记录
    int m_recorder;

};

class CommonEnemyPlane : public EnemyPlane{

};

class SpeedEnemyPlane : public EnemyPlane{

};

class ShootEnemyPlane : public EnemyPlane{

};

#endif // ENEMYPLANE_H
