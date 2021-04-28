#include "map.h"
#include "config.h"

Map::Map()
{
    map1.load(MAP_PATH);
    map2.load(MAP_PATH);

    map1_posY = -GAME_HEIGHT;
    map2_posY = 0;

    scroll_speed = MAP_SCROLL_SPEED;
}

void Map::mapPosition()
{
    //第一张图片滚动
    map1_posY += MAP_SCROLL_SPEED;
    if(map1_posY >= 0)
    {
        map1_posY = -GAME_HEIGHT;
    }
    //第二张图片滚动
    map2_posY += MAP_SCROLL_SPEED;
    if(map2_posY >= GAME_HEIGHT)
    {
        map2_posY = 0;
    }
}
