#ifndef BOSS_H
#define BOSS_H
#include <QPixmap>
#include "headers_game/bullet.h"

class MainScene;

class Boss
{
    friend class MainScene;
public:
    Boss();

    //更新坐标
    void updatePosition();

    void shoot();
private:
    //敌机资源对象
    QPixmap boss;

    //位置
    int X;
    int Y;

    //敌机的矩形边框（碰撞检测）
    QRect rect;

    //状态
    bool free;
    bool isanger;
    bool isshoot;

    //速度
    int speed;

    //生命值
    int health;

    //射击间隔
    int shootinterval;
    int pauseinterval;
    int shootrecorder;
    int pauserecorder;
    int shootpoint;

    //子弹
    EnemyBullet bullets[BOSSBULLET_NUM];
};

#endif // BOSS_H
