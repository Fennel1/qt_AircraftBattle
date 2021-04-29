#ifndef MAINSCENE_H
#define MAINSCENE_H

#include <QWidget>
#include <QTimer>
#include "map.h"
#include "myplane.h"
#include "enemyplane.h"
#include "bomb.h"
#include "data.h"

class MainScene : public QWidget
{
    Q_OBJECT

public:
    QTimer Timer;

    MainScene(QWidget *parent = nullptr);
    ~MainScene();
    void initScene();
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

    //碰撞检测
    void collisionDetection();

private:
    //敌机数组
    CommonEnemyPlane *commonenemys;
    ShootEnemyPlane *shootenemys;

    //敌机出场间隔记录
    int commonrecorder;
    int shootrecorder;

    //地图对象
    Map map;

    //主机对象
    MyPlane *plane;

    //游戏数据对象
    Data data;
};



#endif // MAINSCENE_H
