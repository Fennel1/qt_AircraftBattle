#include "headers_game/dropobjects.h"
#include "headers_game/config.h"

DropObject::DropObject()
{
    //掉落物资源加载
    object.load(COMMONENEMY_PATH);

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

void BloodBag::setObjectPath(QString objectpath)
{
    object.load(objectpath);
}


