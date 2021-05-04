#ifndef SKILL_H
#define SKILL_H
#include "config.h"
#include "enemyplane.h"

class Skill
{
public:
    Skill();

protected:
    int cd;
    int skillrecorder;
    bool free;
};


class ScreenClear : public Skill
{
    friend class MainScene;
public:
    ScreenClear();
    void use(int commonenemynum, int shootenemynum, int speedenemynum,
             CommonEnemyPlane *commonenemys, ShootEnemyPlane *shootenemys, SpeedEnemyPlane *speedenemys);
};

class Laser : public Skill
{
    friend class MainScene;
public:
    Laser();
    void use(int laserx, int commonenemynum, int shootenemynum, int speedenemynum,
             CommonEnemyPlane *commonenemys, ShootEnemyPlane *shootenemys, SpeedEnemyPlane *speedenemys);
};

class Missle : public Skill
{
    friend class MainScene;
public:
    Missle();
    void shoot(int misslex, int missley);
    void updatePosition();
    void bomb(int commonenemynum, int shootenemynum, int speedenemynum,
              CommonEnemyPlane *commonenemys, ShootEnemyPlane *shootenemys, SpeedEnemyPlane *speedenemys);

private:
    //子弹坐标
    int X, Y;
    //子弹的矩形边框（用于碰撞检测）
    QRect rect;
    //子弹移动速度
    int speed;
    //子弹是否闲置
    bool misslefree;
    //子弹资源对象
    QPixmap missle;
};



#endif // SKILL_H
