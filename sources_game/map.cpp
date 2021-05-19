#include "headers_game/map.h"
#include "headers_game/config.h"

Map::Map()
{
    map1.load(BACKGROUND_PATH);
    map2.load(BACKGROUND_PATH);

    map1_posY = -GAME_HEIGHT;
    map2_posY = 0;

    scroll_speed = 2;
}

void Map::mapPosition()
{
    //第一张图片滚动
    map1_posY += scroll_speed;
    if(map1_posY >= 0)
    {
        map1_posY = -GAME_HEIGHT;
    }
    //第二张图片滚动
    map2_posY += scroll_speed;
    if(map2_posY >= GAME_HEIGHT)
    {
        map2_posY = 0;
    }
}
