#ifndef MAINSCENE_H
#define MAINSCENE_H

#include <algorithm>
#include <QWidget>
#include <QTimer>
#include <QTextBrowser>
#include <QLabel>
#include <QPainter>
#include <QPushButton>
#include <QSound>
#include "map.h"
#include "myplane.h"
#include "enemyplane.h"
#include "data.h"
#include "skill.h"
#include "headers_game/dropobjects.h"
#include "boss.h"
#include "player.h"
#include "gamerecord.h"
using namespace std;

class MainScene : public QWidget
{
    Q_OBJECT

public:
    QTimer Timer;

    MainScene(int difficulty, int model, Player *p, CommonRecord *commonrecord, EndlessRecord *endlessrecord, QWidget *parent = nullptr);
    ~MainScene();
    //初始化
    void initScene();
    void initplane();
    void inittext();
    void initobject();
    void initmenu();
    //启动游戏
    void playGame();
    //更新坐标
    void planeMove();
    void updatePosition();
    //绘图事件
    void paintEvent(QPaintEvent *event);

    //鼠标移动事件
    void mouseMoveEvent(QMouseEvent *event);
    //键盘操作事件
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);

    //敌机出场
    void enemyToScene();

    //掉落物出场
    void objectToScene();

    //碰撞检测
    void collisionDetection();
    void bosscollisionDetection();
    void objectCollisionDetection();

    //刷新技能
    void updateSkill();

    //按钮
    void return_home();
    void revive_plane();
    void game_pause();

private:
    //敌机数组
    CommonEnemyPlane *commonenemys;
    ShootEnemyPlane *shootenemys;
    SpeedEnemyPlane *speedenemys;

    //敌机出场间隔记录
    int commonrecorder;
    int shootrecorder;
    int speedrecorder;
    int commonenemyinterval;
    int shootenemyinterval;
    int speedenemyinterval;

    //敌机最大数量
    int commonenemynum;
    int shootenemynum;
    int speedenemynum;

    //BOSS信息
    Boss boss;
    int bossrecorder;
    int bossinterval;

    //地图对象
    Map map1;
    QPixmap map2;

    //主机对象
    MyPlane *plane;

    //游戏数据对象
    Data data;

    //技能
    ScreenClear screenclear;    //清屏
    Laser laser;      //激光
    Missle missle;      //导弹
    Shield shield;      //护盾

    //掉落物数组
    BloodBag *bloodbags;
    BcdFree *bcdfrees;
    ScdFree *scdfrees;
    Coin *coins;

    //掉落物出场间隔
    int objectrecorder;
    int objectinterval;

    //掉落物最大数量
    int bloodbagnum;
    int scdfreenum;
    int bcdfreenum;
    int coinnum;

    //游戏文本信息
    QLabel label_value_of_life;//飞机生命值
    QLabel label_value_of_boss;//boss生命值
    QLabel label_cd_of_laser;
    QLabel label_cd_of_missle;
    QLabel label_cd_of_screenclear;
    QLabel label_cd_of_shield;
    QLabel label_score;//得分
    QLabel label_progress_of_boss;//boss出现的进度

    //暂停参数
    bool ispause;

    //游戏参数
    int difficulty;  //游戏难度
    int model;      //游戏模式 0为正常模式 1为无尽模式
    int difficultyrecorder;     //无尽模式难度增长
    int difficultyinterval;
    bool isgameover;

    //结算界面
    QRect settlement;
    QPushButton revive;
    QPushButton returnhome;
    QPushButton pause;

    //音效
    QSound *bgm1;
    QSound *bgm2;
    QSound *shoot;
    QSound *bomb;

    //用户
    Player *player;

    //记录
    CommonRecord *commonrecord;
    EndlessRecord *endlessrecord;
};

bool cmp(const Gamerecord &a, const Gamerecord &b);



#endif // MAINSCENE_H
