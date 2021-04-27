#ifndef MYPLANE_H
#define MYPLANE_H
#include <QPixmap>
#include "bomb.h"
#include "bullet.h"

class myPlane : Bomb
{
public:
    myPlane();

    //发射子弹
    void shoot();
    //设置飞机位置
    void setPosition(int x, int y);

    //飞机死亡
    void death();
    bool isdeath;

    //飞机资源 对象
    QPixmap m_Plane;

    //飞机坐标
    int m_X;
    int m_Y;

    //飞机的矩形边框
    QRect m_Rect;

    //弹匣
    Bullet m_bullets[BULLET_NUM];

    //发射间隔记录
    int m_recorder;

    //发射子弹
    bool m_shootflag;

    //飞机移动方向
    int m_direction_w;
    int m_direction_s;
    int m_direction_a;
    int m_direction_d;
    bool m_pressflag_w;
    bool m_pressflag_s;
    bool m_pressflag_a;
    bool m_pressflag_d;
};


#endif // MYPLANE_H
