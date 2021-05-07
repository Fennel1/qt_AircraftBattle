#include "skill.h"

Skill::Skill()
{
    skillrecorder = 0;
    free = true;
}

ScreenClear::ScreenClear()
{
    cd = 10;
    //加载图片
    clear.load(SCREENCLEAR_PATH);
    //闲置
    screenclearfree = true;
    //速度
    speed = 15;
    //矩形框
    rect.setWidth(clear.width());
    rect.setHeight(clear.height());
    rect.moveTo(0,0);
}

void ScreenClear::shoot()
{
    screenclearfree = false;
    skillrecorder  = 0;
    y = GAME_HEIGHT;
}

void ScreenClear::updatePosition()
{
    if(screenclearfree)
    {
        return;
    }

    //子弹向上移动
    y -= speed;
    rect.moveTo(0,y);

    if(y <= 0)
    {
        screenclearfree = true;
        free = false;
    }
}

Laser::Laser()
{
    cd = 300;

    //切图参数
    lasermax = 5;
    laserinterval = 10;
    laserfree = true;
    index = 0;
    laserrecorder = 0;

    for (int i=1; i<=lasermax; i++)
    {
        QString str = QString(LASER_PATH).arg(i);
        pixArr.push_back(QPixmap(str));
    }
}

void Laser::updateInfo()
{
    //空闲状态
    if(laserfree)
    {
        return;
    }

    laserrecorder++;
    if(laserrecorder < laserinterval)
    {
        //记录爆炸间隔未到，直接return，不需要切图
        return;
    }
    //重置记录ad
    laserrecorder = 0;

    //切换爆炸播放图片
    index++;

    if(index > lasermax-1)
    {
        index = 0;
        laserfree = true;
    }
}

void Laser::use()
{
    free = false;
    laserfree = false;
    skillrecorder  = 0;
}

void Laser::shoot(int laserx, int lasery, int commonenemynum, int shootenemynum, int speedenemynum,
                CommonEnemyPlane *commonenemys, ShootEnemyPlane *shootenemys, SpeedEnemyPlane *speedenemys)
{
    QRect laser(laserx-50, 0, 100, lasery);
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
    //CD时间
    cd = 1000;
    //持续时间
    duration = 1000;
    //护盾计时
    shieldrecorder = 0;

    //护盾出现参数
    shieldstartmax = 5;
    shieldstartinterval = 10;
    shieldstartrecorder = 0;
    index = 0;
    //护盾资源
    for (int i=1; i<=shieldstartmax; i++)
    {
        QString str = QString(COMMONMYPLANESHIELDSTART_PATH).arg(i);
        pixArr.push_back(QPixmap(str));
    }
    //是否开始出现护盾
    shieldstartfree = true;
}

void Shield::use()
{
    shieldfree = false;
    free = false;
    shieldrecorder = 0;
    skillrecorder = 0;

    shieldstartfree = false;

}

void Shield::end(MyPlane *myplane)
{
    myplane->Plane.load(COMMONMYPLANE_PATH);
}
void Shield::updateInfo(MyPlane *myplane)
{
    //空闲状态
    if(shieldstartfree)
    {
        return;
    }

    shieldstartrecorder++;
    if(shieldstartrecorder < shieldstartinterval)
    {
        //记录爆炸间隔未到，直接return，不需要切图
        return;
    }
    //重置记录ad
    shieldstartrecorder = 0;

    //切换爆炸播放图片
    index++;

    if(index > shieldstartmax-1)
    {
        index = 0;
        shieldstartfree = true;
        myplane->Plane.load(COMMONMYPLANESHIELD_PATH);
    }
}

