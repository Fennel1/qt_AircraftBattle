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

Data::Data(const Data &d)
{
    score = d.score;    //得分

    coin = d.coin;    //金币

    //游戏时长

    //击毁敌机数
    destorycommonenemy = d.destorycommonenemy;
    destoryshootenemy = d.destoryshootenemy;
    destoryspeedenemy = d.destoryspeedenemy;

    //发射子弹数
    myplaneshoottime = d.myplaneshoottime;

    crashtime = d.crashtime;    //与敌机碰撞次数
    beshottime = d.beshottime;    //被敌机子弹击中次数

    //主机死亡
    destroyedbycommonenemy = d.destroyedbycommonenemy;    //被普通敌机击毁次数
    destroyedbyshootenemy = d.destroyedbyshootenemy;    //被射击敌机击毁次数
    destroyedbyspeedenemy = d.destroyedbyspeedenemy;      //被速度敌机击毁次数

    injury = d.injury;    //受到总伤害
    cure = d.cure;   //恢复总血量

    //技能
    //使用次数
    screencleartime = d.screencleartime;
    lasertime = d.lasertime;
    missletime = d.missletime;
    shieldtime = d.shieldtime;

    //技能效果
    screencleardestory = d.screencleardestory;
    laserdestory = d.laserdestory;
    missledestory = d.missledestory;
    shielddefense = d.shielddefense;

    //BOSS
    damageboss = d.damageboss;     //对BOSS造成伤害
    destroyedbyboss = d.destroyedbyboss;    //被BOSS击毁次数
    destoryboss = d.destoryboss;     //击毁BOSS次数
}

Data::Data(int score, int coin, int destorycommonenemy, int destoryshootenemy, int destoryspeedenemy, int myplaneshoottime,
           int crashtime, int beshottime, int destroyedbycommonenemy, int destroyedbyshootenemy, int destroyedbyspeedenemy,
           int injury, int cure, int screencleartime, int lasertime, int missletime, int shieldtime, int screencleardestory,
           int laserdestory, int missledestory, int shielddefense, int damageboss, int destroyedbyboss, int destoryboss)
{
    this->score = score;    //得分

    this->coin = coin;    //金币

    //游戏时长

    //击毁敌机数
    this->destorycommonenemy = destorycommonenemy;
    this->destoryshootenemy = destoryshootenemy;
    this->destoryspeedenemy = destoryspeedenemy;

    //发射子弹数
    this->myplaneshoottime = myplaneshoottime;

    this->crashtime = crashtime;    //与敌机碰撞次数
    this->beshottime = beshottime;    //被敌机子弹击中次数

    //主机死亡
    this->destroyedbycommonenemy = destroyedbycommonenemy;    //被普通敌机击毁次数
    this->destroyedbyshootenemy = destroyedbyshootenemy;    //被射击敌机击毁次数
    this->destroyedbyspeedenemy = destroyedbyspeedenemy;      //被速度敌机击毁次数

    this->injury = injury;    //受到总伤害
    this->cure = cure;   //恢复总血量

    //技能
    //使用次数
    this->screencleartime = screencleartime;
    this->lasertime = lasertime;
    this->missletime = missletime;
    this->shieldtime = shieldtime;

    //技能效果
    this->screencleardestory = screencleardestory;
    this->laserdestory = laserdestory;
    this->missledestory = missledestory;
    this->shielddefense = shielddefense;

    //BOSS
    this->damageboss = damageboss;     //对BOSS造成伤害
    this->destroyedbyboss = destroyedbyboss;    //被BOSS击毁次数
    this->destoryboss = destoryboss;     //击毁BOSS次数

    //道具
}


Data& Data::operator=(const Data &d)
{
    if (this != &d)
    {
        score = d.score;    //得分

        coin = d.coin;    //金币

        //游戏时长

        //击毁敌机数
        destorycommonenemy = d.destorycommonenemy;
        destoryshootenemy = d.destoryshootenemy;
        destoryspeedenemy = d.destoryspeedenemy;

        //发射子弹数
        myplaneshoottime = d.myplaneshoottime;

        crashtime = d.crashtime;    //与敌机碰撞次数
        beshottime = d.beshottime;    //被敌机子弹击中次数

        //主机死亡
        destroyedbycommonenemy = d.destroyedbycommonenemy;    //被普通敌机击毁次数
        destroyedbyshootenemy = d.destroyedbyshootenemy;    //被射击敌机击毁次数
        destroyedbyspeedenemy = d.destroyedbyspeedenemy;      //被速度敌机击毁次数

        injury = d.injury;    //受到总伤害
        cure = d.cure;   //恢复总血量

        //技能
        //使用次数
        screencleartime = d.screencleartime;
        lasertime = d.lasertime;
        missletime = d.missletime;
        shieldtime = d.shieldtime;

        //技能效果
        screencleardestory = d.screencleardestory;
        laserdestory = d.laserdestory;
        missledestory = d.missledestory;
        shielddefense = d.shielddefense;

        //BOSS
        damageboss = d.damageboss;     //对BOSS造成伤害
        destroyedbyboss = d.destroyedbyboss;    //被BOSS击毁次数
        destoryboss = d.destoryboss;     //击毁BOSS次数
    }
    return *this;
}

void Data::update(const Data &d)
{
    score += d.score;    //得分

    coin += d.coin;    //金币

    //游戏时长

    //击毁敌机数
    destorycommonenemy += d.destorycommonenemy;
    destoryshootenemy += d.destoryshootenemy;
    destoryspeedenemy += d.destoryspeedenemy;

    //发射子弹数
    myplaneshoottime += d.myplaneshoottime;

    crashtime += d.crashtime;    //与敌机碰撞次数
    beshottime += d.beshottime;    //被敌机子弹击中次数

    //主机死亡
    destroyedbycommonenemy += d.destroyedbycommonenemy;    //被普通敌机击毁次数
    destroyedbyshootenemy += d.destroyedbyshootenemy;    //被射击敌机击毁次数
    destroyedbyspeedenemy += d.destroyedbyspeedenemy;      //被速度敌机击毁次数

    injury += d.injury;    //受到总伤害
    cure += d.cure;   //恢复总血量

    //技能
    //使用次数
    screencleartime += d.screencleartime;
    lasertime += d.lasertime;
    missletime += d.missletime;
    shieldtime += d.shieldtime;

    //技能效果
    screencleardestory += d.screencleardestory;
    laserdestory += d.laserdestory;
    missledestory += d.missledestory;
    shielddefense += d.shielddefense;

    //BOSS
    damageboss += d.damageboss;     //对BOSS造成伤害
    destroyedbyboss += d.destroyedbyboss;    //被BOSS击毁次数
    destoryboss += d.destoryboss;     //击毁BOSS次数
}
