#include "headers_game/bomb.h"

Bomb::Bomb()
{
    //爆炸参数
    bombmax = 6;
    bombinterval = 10;

    //初始化爆炸图片数组
    for(int i = 1 ;i <= bombmax ;i++)
    {
        //字符串拼接，类似  ":/res/bomb-1.png"
        QString str = QString(BOMB_COMMONENEMY_PATH).arg(i);
        pixArr.push_back(QPixmap(str));
    }


    //初始化空闲状态
    bombfree = true;

    //当前播放图片下标
    index = 0;

    //爆炸间隔记录
    recoder = 0;
}

Bomb::Bomb(QString path)
{
    //爆炸参数
    bombmax = 4;
    bombinterval = 10;

    //初始化爆炸图片数组
    for(int i = 1 ;i <= bombmax ;i++)
    {
        //字符串拼接，类似  ":/res/bomb-1.png"
        QString str = QString(path).arg(i);
        pixArr.push_back(QPixmap(str));
    }


    //初始化空闲状态
    bombfree = true;

    //当前播放图片下标
    index = 0;

    //爆炸间隔记录
    recoder = 0;
}

void Bomb::updateInfo()
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
        bombfree = true;
    }
}

void Bomb::setBombPath(QString path)
{
    pixArr.clear();
    for(int i = 1 ;i <= bombmax; i++)
    {
        //字符串拼接，类似  ":/res/bomb-1.png"
        QString str = QString(path).arg(i);
        pixArr.push_back(QPixmap(str));
    }
}
