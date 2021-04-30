#include "skill.h"

Skill::Skill()
{
    cd = 0;
    free = true;
}

ScreenClear::ScreenClear()
{
}

void ScreenClear::use(int commonenemynum, int shootenemynum, int speedenemynum,
                      CommonEnemyPlane *commonenemys, ShootEnemyPlane *shootenemys, SpeedEnemyPlane *speedenemys)
{
    free = false;
    cd  = 0;
    //遍历所有非空闲的普通敌机
    for(int i = 0 ;i < commonenemynum;i++)
    {
        if(commonenemys[i].free)
        {
            //空闲飞机 跳转下一次循环
            continue;
        }

        commonenemys[i].free = true;
        commonenemys[i].bombfree = false;
    }

    //遍历所有非空闲的射击敌机
    for(int i = 0 ;i < shootenemynum;i++)
    {
        //遍历所非空闲的敌机子弹
        for(int j = 0 ; j < BULLET_NUM;j++)
        {
            if(shootenemys[i].bullets[j].free)
            {
                //空闲子弹 跳转下一次循环
                continue;
            }

            shootenemys[i].bullets[j].free = true;
        }

        if(shootenemys[i].free)
        {
            //空闲飞机 跳转下一次循环
            continue;
        }

        shootenemys[i].free = true;
        shootenemys[i].bombfree = false;
    }

    //遍历所有速度敌机
    for(int i = 0 ;i < speedenemynum;i++)
    {
        if(speedenemys[i].free)
        {
            //空闲飞机 跳转下一次循环
            continue;
        }

        speedenemys[i].free = true;
        speedenemys[i].bombfree = false;
    }
}
