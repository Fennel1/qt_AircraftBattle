#include "headers_game/enemyplane.h"
#include "headers_game/config.h"

EnemyPlane::EnemyPlane() : Bomb()
{
    //敌机资源加载
    enemy.load(COMMONENEMY_PATH);

    //敌机位置
    X = 0;
    Y = 0;

    //敌机状态
    free = true;

    //敌机速度
    speed = 2;

    //敌机矩形
    rect.setWidth(enemy.width());
    rect.setHeight(enemy.height());
    rect.moveTo(X,Y);
}

EnemyPlane::EnemyPlane(QString planepath, QString bombpath) : Bomb(bombpath)
{
    //敌机资源加载
    enemy.load(planepath);

    //敌机位置
    X = 0;
    Y = 0;

    //敌机状态
    free = true;

    //敌机速度
    speed = 2;

    //敌机矩形
    rect.setWidth(enemy.width());
    rect.setHeight(enemy.height());
    rect.moveTo(X,Y);

}

void EnemyPlane::updatePosition()
{
    //空闲状态，不计算坐标
    if(free)
    {
        return;
    }

    X += speed;
    Y += 2;

    if(X < 0)
    {
        speed = 2;
    }
    else if(X > GAME_WIDTH-rect.width())
    {
        speed = -2;
    }
    rect.moveTo(X, Y);

    if(Y >= GAME_HEIGHT + rect.height())
    {
        free = true;
    }
}

void EnemyPlane::death()
{
    free = true;
}

void EnemyPlane::setPlanePath(QString planepath)
{
    enemy.load(planepath);
}

CommonEnemyPlane::CommonEnemyPlane() : EnemyPlane(COMMONENEMY_PATH, BOMB_COMMONENEMY_PATH)
{

}

CommonEnemyPlane::CommonEnemyPlane(QString planepath, QString bombpath)
    : EnemyPlane(planepath, bombpath)
{

}

ShootEnemyPlane::ShootEnemyPlane() : EnemyPlane(SHOOTENEMY_PATH, BOMB_SHOOTENEMY_PATH)
{
    //初始化发射间隔记录
    recorder = 0;
    bulletinterval = 100;
}

ShootEnemyPlane::ShootEnemyPlane(QString planepath, QString bombpath) : EnemyPlane(planepath, bombpath)
{
    //初始化发射间隔记录
    recorder = 0;
    bulletinterval = 100;
}

void ShootEnemyPlane::shoot()
{
    //累加时间间隔记录变量
    recorder++;
    //判断如果记录数字 未达到发射间隔，直接return
    if(recorder < bulletinterval)
    {
        return;
    }
    //到达发射时间处理
    //重置发射时间间隔记录
    recorder = 0;

    //发射子弹
    for(int i = 0 ; i < BULLET_NUM;i++)
    {
        //如果是空闲的子弹进行发射
        if(bullets[i].free)
        {
            //将改子弹空闲状态改为假
            bullets[i].free = false;
            //设置发射的子弹坐标
            bullets[i].X = X + rect.width()*0.5;
            bullets[i].Y = Y ;
            break;
        }
    }
}

void ShootEnemyPlane::updatePosition()
{
    //空闲状态，不计算坐标
    if(free)
    {
        return;
    }

    X += speed;
    if (Y <= rect.height()/2)
    {
        Y +=2;
    }


    if(X < 0)
    {
        speed = 2;
    }
    else if(X > GAME_WIDTH-rect.width())
    {
        speed = -2;
    }
    rect.moveTo(X, Y);

    if(Y >= GAME_HEIGHT + rect.height())
    {
        free = true;
    }
}

SpeedEnemyPlane::SpeedEnemyPlane() : EnemyPlane(SPEEDENEMY_PATH, BOMB_SPEEDENEMY_PATH)
{
    //初始化停顿间隔记录
    recorder = 0;
    //初始化加速点
    speeduppoint = 150;
    //初始化速度
    speed=2;
}

SpeedEnemyPlane::SpeedEnemyPlane(QString planepath, QString bombpath) : EnemyPlane(planepath, bombpath)
{
    //初始化停顿间隔记录
    recorder = 0;
    //初始化加速点
    speeduppoint = 150;
    //初始化速度
    speed=2;
}

void SpeedEnemyPlane::updatePosition()
{
    //空闲状态，不计算坐标
    if(free)
    {
        return;
    }
    if (Y <= speeduppoint && ispause)
    {
        recorder = 0;
        ispause = false;
    }
    speed = 2;
    if (Y <= speeduppoint)
    {
        Y += speed;
    }
    else
    {
        speed = 10;
        if(recorder==speeduppoint)
        {
            ispause = true;
            Y += speed;
        }
        else {
            recorder++;
        }
    }
    rect.moveTo(X, Y);

    if(Y >= GAME_HEIGHT + rect.height())
    {
        free = true;
    }
}
