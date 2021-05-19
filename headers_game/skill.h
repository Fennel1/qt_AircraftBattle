#ifndef SKILL_H
#define SKILL_H
#include "config.h"
#include "enemyplane.h"
#include "myplane.h"
#include "boss.h"
#include "data.h"

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
    void shoot();
    void updatePosition();
private:
    //动画资源
    QPixmap clear;
    //坐标
    int y;
    //速度
    int speed;
    //是否闲置
    bool screenclearfree;
    //矩形
    QRect rect;
};

class Laser : public Skill
{
    friend class MainScene;
public:
    Laser();
    void use();
    void shoot(int laserx, int lasery, int commonenemynum, int shootenemynum, int speedenemynum,
               CommonEnemyPlane *commonenemys, ShootEnemyPlane *shootenemys, SpeedEnemyPlane *speedenemys, Boss &boss, Data &data, bool &isgameover);
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
    //矩形
    QRect rect;
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
              CommonEnemyPlane *commonenemys, ShootEnemyPlane *shootenemys, SpeedEnemyPlane *speedenemys, Data &data);

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
    void use();
    void end(MyPlane *myplane);
    void updateInfo(MyPlane *myplane);
private:
    //护盾持续时间
    int duration;
    //护盾计时
    int shieldrecorder;
    //护盾是否存在
    bool shieldfree;
    //护盾资源
    QVector<QPixmap> pixArr;
    //加载图片下标
    int index;
    //切图时间间隔
    int shieldstartrecorder;
    int shieldstartinterval;
    int shieldstartmax;
    //是否开始出现护盾
    bool shieldstartfree;
};



#endif // SKILL_H
