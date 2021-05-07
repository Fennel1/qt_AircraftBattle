#include "skill.h"

Skill::Skill()
{
    skillrecorder = 0;
    free = true;
}

ScreenClear::ScreenClear()
{
    cd = 1000;
}

void ScreenClear::use(int commonenemynum, int shootenemynum, int speedenemynum,
                      CommonEnemyPlane *commonenemys, ShootEnemyPlane *shootenemys, SpeedEnemyPlane *speedenemys)
{
    free = false;
    skillrecorder  = 0;
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

Laser::Laser()
{
    cd = 300;
}

void Laser::use(int laserx, int commonenemynum, int shootenemynum, int speedenemynum,
                CommonEnemyPlane *commonenemys, ShootEnemyPlane *shootenemys, SpeedEnemyPlane *speedenemys)
{
    QRect laser(laserx-35, 0, 70, GAME_HEIGHT);
    free = false;
    skillrecorder  = 0;
    //遍历所有非空闲的普通敌机
    for(int i = 0 ;i < commonenemynum;i++)
    {
        if(commonenemys[i].free)
        {
            //空闲飞机 跳转下一次循环
            continue;
        }
        if (commonenemys[i].rect.intersects(laser))
        {
            commonenemys[i].free = true;
            commonenemys[i].bombfree = false;
        }
    }

    //遍历所有非空闲的射击敌机
    for(int i = 0 ;i < shootenemynum;i++)
    {
        //遍历所非空闲的敌机子弹dw
        for(int j = 0 ; j < BULLET_NUM;j++)
        {
            if(shootenemys[i].bullets[j].free)
            {
                //空闲子弹 跳转下一次循环
                continue;
            }
            if(shootenemys[i].bullets[j].rect.intersects(laser))
            {
                shootenemys[i].bullets[j].free = true;
            }
        }

        if(shootenemys[i].free)
        {
            //空闲飞机 跳转下一次循环
            continue;
        }
        if (shootenemys[i].rect.intersects(laser))
        {
            shootenemys[i].free = true;
            shootenemys[i].bombfree = false;
        }
    }

    //遍历所有速度敌机
    for(int i = 0 ;i < speedenemynum;i++)
    {
        if(speedenemys[i].free)
        {
            //空闲飞机 跳转下一次循环
            continue;
        }
        if (speedenemys[i].rect.intersects(laser))
        {
            speedenemys[i].free = true;
            speedenemys[i].bombfree = false;
        }

    }
}

Missle::Missle()
{
    //加载导弹图片
    missle.load(MISSLE_PATH);

    X = 0;
    Y = 0;

    //导弹状态
    misslefree = true;

    //导弹速度
    speed = 8;

    //导弹矩形框
    rect.setWidth(missle.width());
    rect.setHeight(missle.height());
    rect.moveTo(X,Y);

    cd = 100;
}

Missle::Missle(QString bombPath) : Bomb (bombPath)
{
    //加载导弹图片
    missle.load(MISSLE_PATH);

    X = 0;
    Y = 0;

    //导弹状态
    misslefree = true;

    //导弹速度
    speed = 8;

    //导弹矩形框
    rect.setWidth(missle.width());
    rect.setHeight(missle.height());
    rect.moveTo(X,Y);

    cd = 100;
}

void Missle::shoot(int misslex, int missley)
{
    X = misslex;
    Y = missley;

    misslefree = false;
    free = false;
    skillrecorder  = 0;
}

void Missle::updatePosition()
{
    if(misslefree)
    {
        return;
    }

    Y  -= speed;
    rect.moveTo(X,Y);

    if(Y <= -rect.height())
    {
        misslefree = true;
    }
}

void Missle::bomb(int commonenemynum, int shootenemynum, int speedenemynum,
                  CommonEnemyPlane *commonenemys, ShootEnemyPlane *shootenemys, SpeedEnemyPlane *speedenemys)
{
    QRect missle(X-100, Y-100, 200, 200);
    misslefree = true;
    bombfree = false;
    //遍历所有非空闲的普通敌机
    for(int i = 0 ;i < commonenemynum;i++)
    {
        if(commonenemys[i].free)
        {
            //空闲飞机 跳转下一次循环
            continue;
        }
        if (commonenemys[i].rect.intersects(missle))
        {
            commonenemys[i].free = true;
            commonenemys[i].bombfree = false;
        }
    }

    //遍历所有非空闲的射击敌机
    for(int i = 0 ;i < shootenemynum;i++)
    {
        //遍历所非空闲的敌机子弹dw
        for(int j = 0 ; j < BULLET_NUM;j++)
        {
            if(shootenemys[i].bullets[j].free)
            {
                //空闲子弹 跳转下一次循环
                continue;
            }
            if(shootenemys[i].bullets[j].rect.intersects(missle))
            {
                shootenemys[i].bullets[j].free = true;
            }
        }

        if(shootenemys[i].free)
        {
            //空闲飞机 跳转下一次循环
            continue;
        }
        if (shootenemys[i].rect.intersects(missle))
        {
            shootenemys[i].free = true;
            shootenemys[i].bombfree = false;
        }
    }

    //遍历所有速度敌机
    for(int i = 0 ;i < speedenemynum;i++)
    {
        if(speedenemys[i].free)
        {
            //空闲飞机 跳转下一次循环
            continue;
        }
        if (speedenemys[i].rect.intersects(missle))
        {
            speedenemys[i].free = true;
            speedenemys[i].bombfree = false;
        }

    }
}

Shield::Shield()
{
    cd = 1000;
    duration = 1000;
    shieldrecorder = 0;
}

void Shield::use(MyPlane *myplane)
{
    shieldfree = false;
    free = false;
    shieldrecorder = 0;
    skillrecorder = 0;
    myplane->Plane.load(COMMONMYPLANESHIELD_PATH);
}

void Shield::end(MyPlane *myplane)
{
    myplane->Plane.load(COMMONMYPLANE_PATH);
}

