#ifndef MAINSCENE_H
#define MAINSCENE_H

#include <QWidget>
#include <QTimer>
#include <QTextBrowser>
#include <QLabel>
#include <QPainter>
#include <QPushButton>
#include "map.h"
#include "myplane.h"
#include "enemyplane.h"
#include "data.h"
#include "skill.h"
#include "headers_window/dropobjects.h"
#include "boss.h"

class MainScene : public QWidget
{
    Q_OBJECT

public:
    QTimer Timer;

    MainScene(QWidget *parent = nullptr);
    ~MainScene();
    void initScene();
    void initplane();
    void inittext();
    //启动游戏
    void playGame();
    //更新坐标
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

    //刷新技能
    void updateSkill();

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

    //BOSS对象
    Boss boss;

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
    DropObject *dropobjects;
    BloodBag *bloodbags;

    //掉落物出场间隔
    int droprecorder;
    int dropobjectinterval;
    int bloodbagrecorder;
    int bloodbaginterval;


    //掉落物最大数量
    int dropobjectnum;
    int bloodbagnum;

    //游戏文本信息
    QLabel label_value_of_life;//飞机生命值
    QLabel label_cd_of_laser;
    QLabel label_cd_of_missle;
    QLabel label_cd_of_screenclear;
    QLabel label_cd_of_shield;

};



#endif // MAINSCENE_H
