#ifndef BOSS_H
#define BOSS_H
#include <QPixmap>
#include "headers_game/bullet.h"
#include "bomb.h"

class MainScene;
class Laser;

class Boss : public Bomb
{
    friend class MainScene;
    friend class Laser;
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
    bool isdeath;

    //速度
    int speed;

    //生命值
    int health;

    //射击间隔
    int bossshootinterval;
    int shootinterval;
    int pauseinterval;
    int bossshootrecorder;
    int shootrecorder;
    int pauserecorder;
    int shootpoint;

    //子弹
    EnemyBullet bullets[BOSSBULLET_NUM];
    BossBUlet bossbullets[BOSSBULLET_NUM];
};

#endif // BOSS_H
