#include "headers_game/myplane.h"
#include "headers_game/config.h"

MyPlane::MyPlane() : Bomb()
{
    //初始化加载飞机图片资源
    Plane.load(COMMONMYPLANE_PATH);

    //初始化坐标
    X = GAME_WIDTH / 2 - Plane.width() / 2;
    Y = GAME_HEIGHT - Plane.height();

    //初始化矩形框
    rect.setWidth(Plane.width());
    rect.setHeight(Plane.height());
    rect.moveTo(X,Y);

    //初始化发射间隔记录
    recorder = 0;
    bulletinterval = 20;
    shootflag = false;

    //飞机移动方向
    direction_w = 0;
    direction_s = 0;
    direction_a = 0;
    direction_d = 0;
    pressflag_w = false;
    pressflag_s = false;
    pressflag_a = false;
    pressflag_d = false;

    //飞机死亡
    isdeath = false;

    //飞机生命值
    health = 5;

    //飞机速度
    speed = 5;
}

MyPlane::MyPlane(QString planepath,QString bombPath) : Bomb(bombPath)
{
    //初始化加载飞机图片资源
    Plane.load(planepath);

    //初始化坐标
    X = GAME_WIDTH / 2 - Plane.width() / 2;
    Y = GAME_HEIGHT - Plane.height();

    //初始化矩形框
    rect.setWidth(Plane.width());
    rect.setHeight(Plane.height());
    rect.moveTo(X,Y);

    //初始化发射间隔记录
    recorder = 0;
    bulletinterval = 20;
    shootflag = false;

    //飞机移动方向
    direction_w = 0;
    direction_s = 0;
    direction_a = 0;
    direction_d = 0;
    pressflag_w = false;
    pressflag_s = false;
    pressflag_a = false;
    pressflag_d = false;

    //飞机死亡
    isdeath = false;

    //飞机生命值
    health = 5;

    //飞机速度
    speed = 5;
}

void MyPlane::setPosition(int x, int y)
{
    X = x;
    Y = y;
    rect.moveTo(X, Y);
}

void MyPlane::setplanePath(QString planepath)
{
    Plane.load(planepath);
}

void MyPlane::shoot()
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
            bullets[i].X = X + rect.width()/2;
            bullets[i].Y = Y - 25 ;
            break;
        }
    }
}

CommonMyPlane::CommonMyPlane() : MyPlane(COMMONMYPLANE_PATH, COMMONMYBOMB_PATH)
{

}
CommonMyPlane::CommonMyPlane(QString planepath, QString bombpath)
    : MyPlane(planepath, bombpath)
{

}
