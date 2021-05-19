#include "headers_game/dropobjects.h"
#include "headers_game/config.h"

DropObject::DropObject()
{
    //掉落物资源加载
    object.load(BLOODBAG_PATH);

    //掉落物位置
    X = 0;
    Y = 0;

    //掉落物状态
    free = true;

    //掉落物速度
    speed = 2;

    //掉落物矩形
    rect.setWidth(object.width());
    rect.setHeight(object.height());
    rect.moveTo(X,Y);
}

DropObject::DropObject(QString objectpath)
{
    //掉落物资源加载
    object.load(objectpath);

    //掉落物位置
    X = 0;
    Y = 0;

    //掉落物状态
    free = true;

    //掉落物速度
    speed = 2;

    //掉落物矩形
    rect.setWidth(object.width());
    rect.setHeight(object.height());
    rect.moveTo(X,Y);

}

void DropObject::updatePosition()
{
    //空闲状态，不计算坐标
    if(free)
    {
        return;
    }

    X += speed;
    Y += 1;

    if(X < widthl)
    {
        speed = 1;
    }
    else if(X > widthr)
    {
        speed = -1;
    }
    rect.moveTo(X, Y);

    if(Y >= GAME_HEIGHT + rect.height())
    {
        free = true;
    }
}

void DropObject::setObjectPath(QString objectpath)
{
    object.load(objectpath);
}

BloodBag::BloodBag():DropObject (DROPOBJECT_PATH)
{

}

BloodBag::BloodBag(QString objectpath):DropObject (objectpath)
{


}

void BloodBag::updatePosition()
{
    //空闲状态，不计算坐标
    if(free)
    {
        return;
    }

    X += speed;
    Y += 1;

    if(X<0||X < widthl)
    {
        speed = 1;
    }
    else if(X> GAME_WIDTH-rect.width()||X > widthr)
    {
        speed = -1;
    }
    rect.moveTo(X, Y);

    if(Y >= GAME_HEIGHT + rect.height())
    {
        free = true;
    }
}

void BloodBag::setObjectPath(QString objectpath)
{
    object.load(objectpath);
}

BcdFree::BcdFree():DropObject (DROPOBJECT_PATH)
{

}

BcdFree::BcdFree(QString objectpath):DropObject (DROPOBJECT_PATH)
{

}

void BcdFree::updatePosition()
{
    //空闲状态，不计算坐标
    if(free)
    {
        return;
    }

    X += speed;
    Y += 1;

    if(X<0||X < widthl)
    {
        speed = 1;
    }
    else if(X> GAME_WIDTH-rect.width()||X > widthr)
    {
        speed = -1;
    }
    rect.moveTo(X, Y);

    if(Y >= GAME_HEIGHT + rect.height())
    {
        free = true;
    }
}

void BcdFree::setObjectPath(QString objectpath)
{
    object.load(objectpath);
}

ScdFree::ScdFree():DropObject (DROPOBJECT_PATH)
{

}

ScdFree::ScdFree(QString objectpath):DropObject (DROPOBJECT_PATH)
{

}

void ScdFree::updatePosition()
{
    //空闲状态，不计算坐标
    if(free)
    {
        return;
    }

    X += speed;
    Y += 1;

    if(X<0||X < widthl)
    {
        speed = 1;
    }
    else if(X> GAME_WIDTH-rect.width()||X > widthr)
    {
        speed = -1;
    }
    rect.moveTo(X, Y);

    if(Y >= GAME_HEIGHT + rect.height())
    {
        free = true;
    }
}

void ScdFree::setObjectPath(QString objectpath)
{
    object.load(objectpath);
}

Coin::Coin():DropObject (DROPOBJECT_PATH)
{
    //爆炸参数
    bombmax = 8;
    bombinterval = 10;

    //初始化爆炸图片数组
    for(int i = 1 ;i <= bombmax; i++)
    {
        //字符串拼接，类似  ":/res/bomb-1.png"
        QString str = QString(COIN_ANIMAPATH).arg(i);
        pixArr.push_back(QPixmap(str));
    }


    //初始化空闲状态
    bombfree = false;

    //当前播放图片下标
    index = 0;

    //爆炸间隔记录
    recoder = 0;
}
Coin::Coin(QString objectpath):DropObject (DROPOBJECT_PATH)
{
    //爆炸参数
    bombmax = 8;
    bombinterval = 10;

    //初始化爆炸图片数组
    for(int i = 1 ;i <= bombmax ;i++)
    {
        //字符串拼接，类似  ":/res/bomb-1.png"
        QString str = QString(COIN_ANIMAPATH).arg(i);
        pixArr.push_back(QPixmap(str));
    }


    //初始化空闲状态
    bombfree = false;

    //当前播放图片下标
    index = 0;

    //爆炸间隔记录
    recoder = 0;
}

void Coin::updateInfo()
{
    //空闲状态
    if(bombfree)
    {
        return;
    }

    recoder++;
    if(recoder < bombinterval)
    {
        //记录爆炸间隔未到，直接return，不需要切图
        return;
    }
    //重置记录ad
    recoder = 0;

    //切换爆炸播放图片
    index++;
    //注：数组中的下标从0开始，最大是6
    //如果计算的下标大于6，重置为0
    if(index > bombmax-1)
    {
        index = 0;
    }
}

void Coin::setBombPath(QString path)
{
    pixArr.clear();
    for(int i = 1 ;i <= bombmax; i++)
    {
        //字符串拼接，类似  ":/res/bomb-1.png"
        QString str = QString(path).arg(i);
        pixArr.push_back(QPixmap(str));
    }
}

void Coin::updatePosition()
{
    //空闲状态，不计算坐标
    if(free)
    {
        return;
    }

    X += speed;
    Y += 1;

    if(X<0||X < widthl)
    {
        speed = 1;
    }
    else if(X> GAME_WIDTH-rect.width()||X > widthr)
    {
        speed = -1;
    }
    rect.moveTo(X, Y);

    if(Y >= GAME_HEIGHT + rect.height())
    {
        free = true;
    }
}

void Coin::setObjectPath(QString objectpath)
{
    object.load(objectpath);
}
