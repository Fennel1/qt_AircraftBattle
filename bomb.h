#ifndef BOMB_H
#define BOMB_H
#include "config.h"
#include <QPixmap>
#include <QVector>

class Bomb
{
public:
    Bomb();
    Bomb(QString path);

    //更新信息（播放图片下标、播放间隔）
    void updateInfo();

protected:
    //放爆炸资源数组
    QVector<QPixmap> pixArr;

    //爆炸状态
    bool bombfree;

    //爆炸切图的时间间隔
    int recoder;

    //爆炸时加载的图片下标
    int index;
};

#endif // BOMB_H
