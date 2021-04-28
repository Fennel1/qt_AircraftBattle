#include "bullet.h"

Bullet::Bullet()
{
    //加载子弹资源
    mBullet.load(BULLET_PATH);

    //子弹坐标 初始坐标可随意设置，后期会重置
    X = GAME_WIDTH*0.5 - mBullet.width()*0.5;
    Y = GAME_HEIGHT;

    //子弹状态
    Free = true;

    //子弹速度
    Speed = BULLET_SPEED;

    //子弹矩形框
    Rect.setWidth(mBullet.width());
    Rect.setHeight(mBullet.height());
    Rect.moveTo(X,Y);
}
void MyBullet::updatePosition()
{
    //如果子弹是空闲状态，不需要坐标计算
    //玩家飞机可以控制子弹的空闲状态为false
    if(Free)
    {
        return;
    }

    //子弹向上移动
    Y  -= Speed;
    Rect.moveTo(X,Y);

    if(Y <= -Rect.height())
    {
        Free = true;
    }
}

void EnemyBullet::updatePosition()
{
    //如果子弹是空闲状态，不需要坐标计算
    if(Free)
    {
        return;
    }

    //子弹向下移动
    Y  += Speed;
    Rect.moveTo(X,Y);

    if(Y >= GAME_HEIGHT)
    {
        Free = true;
    }
}
