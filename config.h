#ifndef CONFIG_H
#define CONFIG_H

#define GAME_WIDTH 480
#define GAME_HEIGHT 700                     //界面宽高
#define GAME_TITLE "飞机大战 v1.0"           //标题
#define GAME_ICON ":/images/enemy2.png"     //图标
#define MAP_PATH ":/image/images/background.png"      //地图
#define MYPLANE_PATH ":/images/me1.png"
#define MAP_SCROLL_SPEED 2                   //地图滚动速度
#define GAME_RATE 10
#define BULLET_PATH ":/images/bullet1.png"   //子弹图片路径
#define BULLET_SPEED 5  //子弹移动速度
#define BULLET_NUM 30   //弹匣中子弹总数
#define BULLET_INTERVAL 20 //发射子弹时间间隔
#define MYPLANE_SPEED 10      //主机飞行速度
#define ENEMY_PATH  ":/images/enemy1.png"  //敌机资源图片
#define ENEMY_SPEED 5  //敌机移动速度
#define ENEMY_NUM   20  //敌机总数量
#define ENEMY_INTERVAL  30  //敌机出场时间间隔

#endif // CONFIG_H
