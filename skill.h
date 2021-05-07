#ifndef SKILL_H
#define SKILL_H
#include "config.h"
#include "enemyplane.h"
#include "myplane.h"

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
    void use(int laserx, int lasery, int commonenemynum, int shootenemynum, int speedenemynum,
             CommonEnemyPlane *commonenemys, ShootEnemyPlane *shootenemys, SpeedEnemyPlane *speedenemys);
    void updateInfo();
private:
    //激光资源
    QVector<QPixmap> pixArr;

    //发射状态
    bool laserfree;

    //切图时间间隔
    int laserrecorder;
    int laserinterval;
    int lasermax;

    //加载图片下标
    int index;
};

class Missle : public Skill, public Bomb
{
    friend class MainScene;
public:
    Missle();
    Missle(QString bombPath);
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

class Shield : public Skill
{
    friend class MainScene;
public:
    Shield();
    void use(MyPlane *myplane);
    void end(MyPlane *myplane);
private:
    int duration;
    int shieldrecorder;
    bool shieldfree;
};



#endif // SKILL_H
