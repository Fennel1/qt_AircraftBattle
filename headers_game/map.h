#ifndef MAP_H
#define MAP_H
#include <QPixmap>

class MainScene;

class Map
{
    friend class MainScene;
public:
    Map();
    //地图滚动坐标计算
    void mapPosition();

private:
    //地图图片对象
    QPixmap map1;
    QPixmap map2;

    //地图y轴坐标
    int map1_posY;
    int map2_posY;

    //地图滚动幅度
    int scroll_speed;
};

#endif // MAP_H
