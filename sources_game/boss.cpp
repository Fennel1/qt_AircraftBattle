#include "headers_game/boss.h"
#include "headers_game/config.h"
#include <ctime>

Boss::Boss()
{
    //敌机资源加载
    boss.load(BOSS_PATH);

    //敌机矩形
    rect.setWidth(boss.width());
    rect.setHeight(boss.height());

    //敌机位置
    X = GAME_WIDTH/2-rect.width()/2;
    Y = 0-rect.height();

    rect.moveTo(X,Y);

    //敌机状态
    free = true;
    isanger = false;
    isshoot = true;
    isdeath = false;

    //移动速度
    speed = 1;

    //生命值
    health = 1000;

    //射击间隔
    bossshootinterval = 70;
    shootinterval = 30;
    pauseinterval = 500;
    bossshootrecorder = 0;
    shootrecorder = 0;
    pauserecorder = 0;
    shootpoint = (rand() % 6)*100+50;

    //子弹路径
    for (int i=0; i<BOSSBULLET_NUM; i++)
    {
        bullets[i].setBulletPath(BOSSBULLET1_PATH);
        bossbullets[i].setBulletPath(BOSSBULLET2_PATH);
    }
}

void Boss::updatePosition()
{
    //空闲状态，不计算坐标
    if(free)
    {
        return;
    }

    if (Y <= -rect.height()/3)
    {
        Y += 0.5;
    }

    rect.moveTo(X, Y);
}

void Boss::shoot()
{
    if (isanger)
    {
        if (isshoot)
        {
            shootrecorder++;
            pauserecorder++;
            if (shootrecorder > shootinterval)
            {
                shootrecorder = 0;
                for (int i=0; i<6; i++)
                {
                    if (i*100+50 == shootpoint) continue;
                    for (int j=0; j<BOSSBULLET_NUM; j++)
                    {
                        if (bullets[j].free)
                        {
                            bullets[j].free = false;
                            bullets[j].X = i*100+50;
                            bullets[j].Y = rect.height()/2;
                            break;
                        }
                    }
                }
            }
            if (pauserecorder > pauseinterval)
            {
                isshoot = false;
                pauserecorder = 0;
                shootpoint = (rand() % 6)*100+50;
            }
        }
        else
        {
            pauserecorder++;
            if (pauserecorder > pauseinterval)
            {
                pauserecorder = 0;
                isshoot = true;
            }
        }
    }
    else
    {
        bossshootrecorder++;
        if (bossshootrecorder > bossshootinterval)
        {
            bossshootrecorder = 0;
            for (int i=0; i<BOSSBULLET_NUM; i++)
            {
                if (bossbullets[i].free)
                {
                    bossbullets[i].free = false;
                    bossbullets[i].X = rand() % GAME_WIDTH;
                    bossbullets[i].Y = Y + rect.height()-20;
                    bossbullets[i].speed = rand() % 2 ? 2 : -2;
                    break;
                }
            }
        }
    }
}
