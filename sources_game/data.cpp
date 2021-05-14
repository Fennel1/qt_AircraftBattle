#include "headers_game/data.h"

Data::Data()
{
    score = 0;    //得分

    coin = 0;    //金币

    //游戏时长

    //击毁敌机数
    destorycommonenemy = 0;
    destoryshootenemy = 0;
    destoryspeedenemy = 0;

    //发射子弹数
    myplaneshoottime = 0;

    crashtime = 0;    //与敌机碰撞次数
    beshottime = 0;    //被敌机子弹击中次数

    //主机死亡
    destroyedbycommonenemy = 0;    //被普通敌机击毁次数
    destroyedbyshootenemy = 0;    //被射击敌机击毁次数
    destroyedbyspeedenemy = 0;      //被速度敌机击毁次数

    injury = 0;    //受到总伤害
    cure = 0;   //恢复总血量

    //技能
    //使用次数
    screencleartime = 0;
    lasertime = 0;
    missletime = 0;
    shieldtime = 0;

    //技能效果
    screencleardestory = 0;
    laserdestory = 0;
    missledestory = 0;
    shielddefense = 0;

    //BOSS
    damageboss = 0;     //对BOSS造成伤害
    destroyedbyboss = 0;    //被BOSS击毁次数
    destoryboss = 0;     //击毁BOSS次数

    //道具
}

//Data& Data::operator=(const Data &d)
//{
//}

//Data Data::operator+=(const Data &d)
//{

//}
