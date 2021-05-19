#include "headers_game/bullet.h"

Bullet::Bullet()
{
    //加载子弹资源
    bullet.load(BULLET_PATH);

    //子弹坐标 初始坐标可随意设置，后期会重置
    X = GAME_WIDTH/2 - bullet.width()/2;
    Y = GAME_HEIGHT;

    //子弹状态
    free = true;

    //子弹速度
    speed = 5;

    //子弹矩形框
    rect.setWidth(bullet.width());
    rect.setHeight(bullet.height());
    rect.moveTo(X,Y);
}

void Bullet::setBulletPath(QString path)
{
    bullet.load(path);
}

void MyBullet::updatePosition()
{
    //如果子弹是空闲状态，不需要坐标计算
    //玩家飞机可以控制子弹的空闲状态为false
    if(free)
    {
        return;
    }

    //子弹向上移动
    Y  -= speed;
    rect.moveTo(X,Y);

    if(Y <= -rect.height())
    {
        free = true;
    }
}

void EnemyBullet::updatePosition()
{
    //如果子弹是空闲状态，不需要坐标计算
    if(free)
    {
        return;
    }

    //子弹向下移动
    Y  += speed;
    rect.moveTo(X,Y);

    if(Y >= GAME_HEIGHT)
    {
        free = true;
    }
}

void BossBUlet::updatePosition()
{
    //如果子弹是空闲状态，不需要坐标计算
    if(free)
    {
        return;
    }

    //子弹向下移动
    Y  += 2;
    X  += speed;
    if(X < 0)
    {
        speed = 2;
    }
    else if(X > GAME_WIDTH-rect.width())
    {
        speed = -2;
    }
    rect.moveTo(X,Y);

    if(Y >= GAME_HEIGHT)
    {
        free = true;
    }
}
