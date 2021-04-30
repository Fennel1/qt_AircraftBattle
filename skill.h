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
//    int skillinterval;
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



#endif // SKILL_H
