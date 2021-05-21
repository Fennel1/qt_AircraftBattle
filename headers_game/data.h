#ifndef DATA_H
#define DATA_H
#include <QTime>
#include "myplane.h"

class MainScene;
class Laser;
class Missle;
class loginWindow;
class RegWindow;
class ForgetPW;
class MainWindow;

class Data : public MyPlane
{
    friend class MainScene;
    friend class Laser;
    friend class Missle;
    friend class loginWindow;
    friend class RegWindow;
    friend class ForgetPW;
    friend class MainWindow;
public:
    Data();
    Data(const Data & d);
    Data(int score, int coin, int destorycommonenemy, int destoryshootenemy, int destoryspeedenemy, int myplaneshoottime,
         int crashtime, int beshottime, int destroyedbycommonenemy, int destroyedbyshootenemy, int destroyedbyspeedenemy,
         int injury, int cure, int screencleartime, int lasertime, int missletime, int shieldtime, int screencleardestory,
         int laserdestory, int missledestory, int shielddefense, int damageboss, int destroyedbyboss, int destoryboss);
    Data& operator=(const Data &d);
    void update(const Data &d);

private:
    int score;    //得分

    int coin;    //金币

    //游戏时长

    //击毁敌机数
    int destorycommonenemy;
    int destoryshootenemy;
    int destoryspeedenemy;

    //发射子弹数
    int myplaneshoottime;

    int crashtime;    //与敌机碰撞次数
    int beshottime;    //被敌机子弹击中次数

    //主机死亡
    int destroyedbycommonenemy;    //被普通敌机击毁次数
    int destroyedbyshootenemy;    //被射击敌机击毁次数
    int destroyedbyspeedenemy;      //被速度敌机击毁次数

    int injury;    //受到总伤害
    int cure;   //恢复总血量

    //技能
    //使用次数
    int screencleartime;
    int lasertime;
    int missletime;
    int shieldtime;

    //技能效果
    int screencleardestory;
    int laserdestory;
    int missledestory;
    int shielddefense;

    //BOSS
    int damageboss;     //对BOSS造成伤害
    int destroyedbyboss;    //被BOSS击毁次数
    int destoryboss;     //击毁BOSS次数

    //道具
};

#endif // DATA_H
