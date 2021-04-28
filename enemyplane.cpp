#include "enemyplane.h"
#include "config.h"

EnemyPlane::EnemyPlane() : Bomb()
{
    //敌机资源加载
    enemy.load(ENEMY_PATH);

    //敌机位置
    X = 0;
    Y = 0;

    //敌机状态
    Free = true;

    //敌机速度
    Speed = ENEMY_SPEED;

    //敌机矩形
    Rect.setWidth(enemy.width());
    Rect.setHeight(enemy.height());
    Rect.moveTo(X,Y);

    //初始化发射间隔记录
    recorder = 0;

}

void EnemyPlane::updatePosition()
{
    //空闲状态，不计算坐标
    if(Free)
    {
        return;
    }

    X += Speed;
    Y += 2;

    if(X < 0)
    {
        Speed = ENEMY_SPEED;
    }
    else if(X > GAME_WIDTH-Rect.width())
    {
        Speed = -ENEMY_SPEED;
    }
    Rect.moveTo(X, Y);

    if(Y >= GAME_HEIGHT + Rect.height())
    {
        Free = true;
    }
}

void EnemyPlane::death()
{
    Free = true;
}

void EnemyPlane::shoot()
{
    //累加时间间隔记录变量
    recorder++;
    //判断如果记录数字 未达到发射间隔，直接return
    if(recorder < ENEMY_BULLETINTERVAL)
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
        if(bullets[i].Free)
        {
            //将改子弹空闲状态改为假
            bullets[i].Free = false;
            //设置发射的子弹坐标
            bullets[i].X = X + Rect.width()*0.5;
            bullets[i].Y = Y ;
            break;
        }
     }
}
