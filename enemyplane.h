#ifndef ENEMYPLANE_H
#define ENEMYPLANE_H


#include <QPixmap>
#include <bomb.h>

class EnemyPlane : public Bomb
{
public:
    EnemyPlane();

    //更新坐标
    void updatePosition();
public:
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

    //飞机死亡
    void death();
};

class CommonEnemyPlane : public EnemyPlane{

};

class SpeedEnemyPlane : public EnemyPlane{

};

class ShootEnemyPlane : public EnemyPlane{

};

#endif // ENEMYPLANE_H
