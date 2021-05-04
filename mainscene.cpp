#include "mainscene.h"
#include "config.h"
#include <QIcon>
#include <QDebug>
#include <QPainter>
#include <QMouseEvent>
#include <ctime>
MainScene::MainScene(QWidget *parent)
    : QWidget(parent)
{
    //场景的初始化
    initScene();
    //飞机参数初始化
    initplane();

}

MainScene::~MainScene()
{
}

void MainScene::initplane()
{
    //敌机最大数量
    commonenemynum = 20;
    shootenemynum = 10;
    speedenemynum = 15;

    //初始化飞机
    plane = new CommonMyPlane(COMMONMYPLANE_PATH, COMMONMYBOMB_PATH);
    commonenemys = new CommonEnemyPlane[commonenemynum];
    shootenemys = new ShootEnemyPlane[shootenemynum];
    speedenemys = new SpeedEnemyPlane[speedenemynum];

    //设置飞机参数
    for (int i=0; i < commonenemynum; i++)
    {
        //设置普通敌机参数
        commonenemys[i].setPlanePath(COMMONENEMY_PATH);
        commonenemys[i].setBombPath(BOMB_COMMONENEMY_PATH);
    }
    for (int i=0; i < shootenemynum; i++)
    {
        //设置射击敌机参数
        shootenemys[i].setPlanePath(SHOOTENEMY_PATH);
        shootenemys[i].setBombPath(BOMB_SHOOTENEMY_PATH);
    }
    for (int i=0; i<speedenemynum; i++)
    {
        //设置速度飞机参数
        speedenemys[i].setPlanePath(SPEEDENEMY_PATH);
        speedenemys[i].setBombPath(BOMB_SPEEDENEMY_PATH);
    }

    //敌机刷新间隔
    commonrecorder = 0;
    shootrecorder = 0;
    speedrecorder = 0;
    commonenemyinterval = 50;
    shootenemyinterval = 200;
    speedenemyinterval = 100;
}

void MainScene::initScene()
{
    //随机数种子
    srand((unsigned int)time(NULL));

    //窗口大小
    setFixedSize(GAME_WIDTH,GAME_HEIGHT);
    //窗口标题
    setWindowTitle(GAME_TITLE);
    //窗口图标
    setWindowIcon(QIcon(GAME_ICON));
    //定时器设置
    Timer.setInterval(GAME_RATE);
    //启动游戏
    playGame();
}

void MainScene::playGame()
{
    //启动定时器
    Timer.start();

    //监听定时器
    connect(&Timer,&QTimer::timeout,[=](){
        //主机移动
        if (plane->X >= 0 && plane->X <= GAME_WIDTH - plane->rect.width())
        {
            plane->X += (plane->direction_a + plane->direction_d) * plane->speed;
            data.movingdistance += (plane->direction_a + plane->direction_d) * plane->speed;   //增加移动距离
        }
        if (plane->Y >= 0 && plane->Y <= (GAME_HEIGHT - plane->rect.height()))
        {
            plane->Y += (plane->direction_w + plane->direction_s) * plane->speed;
            data.movingdistance += (plane->direction_w + plane->direction_s) * plane->speed;   //增加移动距离
        }
        //边界检测
        if(plane->X <= 0 )
        {
            plane->X = 0;
        }
        else if(plane->X >= GAME_WIDTH - plane->rect.width())
        {
            plane->X = GAME_WIDTH - plane->rect.width();
        }
        if(plane->Y <= 0)
        {
            plane->Y = 0;
        }
        else if(plane->Y >= GAME_HEIGHT - plane->rect.height())
        {
            plane->Y = GAME_HEIGHT - plane->rect.height();
        }
        plane->rect.moveTo(plane->X, plane->Y);
        if (plane->shootflag)
        {
            plane->shoot();
            data.myplaneshoottime++;    //射击子弹数加一
        }
        //敌机出场
        enemyToScene();
        //更新游戏元素坐标
        updatePosition();
        //重新绘制图片
        update();
        //碰撞检测
        collisionDetection();
        //刷新技能
        updateSkill();
    });
}

void MainScene::updateSkill()
{
    if (screenclear.free == false)
    {
        screenclear.skillrecorder++;
        if (screenclear.skillrecorder >= screenclear.cd)
        {
            screenclear.free = true;
        }
    }
    if (laser.free == false)
    {
        laser.skillrecorder++;
        if (laser.skillrecorder >= laser.cd)
        {
            laser.free = true;
        }
    }
    if (missle.free == false && missle.misslefree == true)
    {
        missle.skillrecorder++;
        if (missle.skillrecorder >= missle.cd)
        {
            missle.free = true;
        }
    }
}

void MainScene::updatePosition()
{
    //更新地图坐标
    map.mapPosition();

    //计算子弹坐标
    for(int i = 0 ;i < BULLET_NUM;i++)
    {
        //如果子弹状态为非空闲，计算发射位置
        if(!plane->bullets[i].free)
        {
            plane->bullets[i].updatePosition();
        }
    }

    //敌机坐标计算
    for(int i = 0 ; i< commonenemynum;i++)
    {
        //非空闲敌机 更新坐标
        if(commonenemys[i].free == false)
        {
           commonenemys[i].updatePosition();
        }
    }
    for(int i = 0 ; i< shootenemynum;i++)
    {
        //非空闲敌机 更新坐标
        if(shootenemys[i].free == false)
        {
           shootenemys[i].updatePosition();
           shootenemys[i].shoot();
        }
        //更新敌机子弹
        for(int j=0; j < BULLET_NUM; j++)
        {
            if(!shootenemys[i].bullets[j].free)
            {
                shootenemys[i].bullets[j].updatePosition();
            }
        }
    }
    for (int i=0; i<speedenemynum; i++)
    {
        //非空闲敌机 更新坐标
        if(speedenemys[i].free == false)
        {
           speedenemys[i].updatePosition();
        }
    }

    //计算爆炸播放的图片
    for(int i = 0 ; i < commonenemynum;i++)
    {
        //敌机爆炸
        if(commonenemys[i].bombfree == false)
        {
            commonenemys[i].updateInfo();
        }
    }
    for(int i = 0 ; i < shootenemynum;i++)
    {
        //敌机爆炸
        if(shootenemys[i].bombfree == false)
        {
            shootenemys[i].updateInfo();
        }
    }
    for(int i = 0 ; i < speedenemynum;i++)
    {
        //敌机爆炸
        if(speedenemys[i].bombfree == false)
        {
            speedenemys[i].updateInfo();
        }
    }

    //主机爆炸
    if (plane->bombfree == false)
    {
        plane->updateInfo();
    }

    //导弹更新
    if (missle.misslefree == false)
    {
        missle.updatePosition();
    }
}

void MainScene::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    //绘制地图
    painter.drawPixmap(0,map.map1_posY , map.map1);
    painter.drawPixmap(0,map.map2_posY , map.map2);

    //绘制主机
    if (plane->isdeath == false)
    {
        painter.drawPixmap(plane->X, plane->Y, plane->Plane);
    }
    if (plane->bombfree == false)
    {
        painter.drawPixmap(plane->X, plane->Y, plane->pixArr[plane->index]);
    }

    //绘制主机子弹
    for(int i = 0 ;i < BULLET_NUM;i++)
    {
        //如果子弹状态为非空闲，计算发射位置
        if(!plane->bullets[i].free)
        {
            painter.drawPixmap(plane->bullets[i].X,plane->bullets[i].Y,plane->bullets[i].bullet);
        }
    }

    //绘制敌机
    for(int i = 0 ; i< commonenemynum;i++)
    {
        if(commonenemys[i].free == false)
        {
            painter.drawPixmap(commonenemys[i].X,commonenemys[i].Y,commonenemys[i].enemy);
        }
    }
    for(int i = 0 ; i< shootenemynum;i++)
    {
        if(shootenemys[i].free == false)
        {
            painter.drawPixmap(shootenemys[i].X,shootenemys[i].Y,shootenemys[i].enemy);
        }
        //绘制敌机子弹
        for(int j = 0 ;j < BULLET_NUM;j++)
            {
                //如果子弹状态为非空闲，计算发射位置
                if(!shootenemys[i].bullets[j].free)
                {
                    painter.drawPixmap(shootenemys[i].bullets[j].X,shootenemys[i].bullets[j].Y,shootenemys[i].bullets[j].bullet);
                }
            }
    }
    for (int i=0; i<speedenemynum; i++)
    {
        if(speedenemys[i].free == false)
        {
            painter.drawPixmap(speedenemys[i].X,speedenemys[i].Y,speedenemys[i].enemy);
        }
    }

    //绘制敌机爆炸图片
    for(int i = 0 ; i < commonenemynum;i++)
    {
        if(commonenemys[i].bombfree == false)
        {
            painter.drawPixmap(commonenemys[i].X, commonenemys[i].Y, commonenemys[i].pixArr[commonenemys[i].index]);
        }
    }
    for(int i = 0 ; i < shootenemynum;i++)
    {
        if(shootenemys[i].bombfree == false)
        {
            painter.drawPixmap(shootenemys[i].X, shootenemys[i].Y, shootenemys[i].pixArr[shootenemys[i].index]);
        }
    }
    for(int i = 0 ; i < speedenemynum;i++)
    {
        if(speedenemys[i].bombfree == false)
        {
            painter.drawPixmap(speedenemys[i].X, speedenemys[i].Y, speedenemys[i].pixArr[speedenemys[i].index]);
        }
    }

    //绘制导弹
    if (missle.misslefree == false)
    {
        painter.drawPixmap(missle.X, missle.Y, missle.missle);
    }
}

void MainScene::mouseMoveEvent(QMouseEvent *event)
{
    int x = event->x() - plane->rect.width()/2;      //鼠标位置 - 飞机矩形的一半
    int y = event->y() - plane->rect.height()/2;

    //边界检测
    if(x <= 0 )
    {
        x = 0;
    }
    if(x >= GAME_WIDTH - plane->rect.width())
    {
        x = GAME_WIDTH - plane->rect.width();
    }
    if(y <= 0)
    {
        y = 0;
    }
    if(y >= GAME_HEIGHT - plane->rect.height())
    {
        y = GAME_HEIGHT - plane->rect.height();
    }
    plane->setPosition(x,y);
}

void MainScene::keyPressEvent(QKeyEvent *event)         //键盘按键按下判定 持续按住按键控制
{
    //使用技能
    if (event->key() == Qt::Key_K && !event->isAutoRepeat())
    {
        if (screenclear.free == true)
        {
            screenclear.use(commonenemynum, shootenemynum, speedenemynum, commonenemys, shootenemys, speedenemys);
        }
    }
    if (event->key() == Qt::Key_L && !event->isAutoRepeat())
    {
        if (laser.free == true)
        {
            laser.use(plane->X, commonenemynum, shootenemynum, speedenemynum, commonenemys, shootenemys, speedenemys);
        }
    }
    if (event->key() == Qt::Key_U && !event->isAutoRepeat())
    {
        if (missle.free == true)
        {
            missle.shoot(plane->X, plane->Y);
        }
    }

    //射击
    if (event->key() == Qt::Key_J && !event->isAutoRepeat())
    {
        plane->shootflag = true;
    }

    //移动
    if((event->key() == Qt::Key_W) && !event->isAutoRepeat())   //上
    {
        if(!plane->pressflag_w)
        {
            plane->direction_w = -1;
        }
        plane->pressflag_w = true;
    }
    if((event->key() == Qt::Key_S) && !event->isAutoRepeat())  //下
    {
        if(!plane->pressflag_s)
        {
           plane->direction_s = 1;
        }
        plane->pressflag_s = true;
    }
    if((event->key() == Qt::Key_A) && !event->isAutoRepeat())  //左
    {
        if(!plane->pressflag_a)
        {
            plane->direction_a = -1;
        }
        plane->pressflag_a = true;
    }
    if((event->key() == Qt::Key_D) && !event->isAutoRepeat())  //右
    {
        if(!plane->pressflag_d)
        {
            plane->direction_d = 1;
        }
        plane->pressflag_d = true;
    }

}

void MainScene::keyReleaseEvent(QKeyEvent *event)       //键盘按键抬起判定 持续按住按键控制
{
    if (event->key() == Qt::Key_J && !event->isAutoRepeat())
    {
        plane->shootflag = false;
    }

    if((event->key() == Qt::Key_W)&& plane->direction_w == -1 && !event->isAutoRepeat())     //上
    {
        if(plane->pressflag_w)
        {
            plane->direction_w = 0;
        }
        plane->pressflag_w = false;
    }
    if((event->key() == Qt::Key_S)&& plane->direction_s == 1 && !event->isAutoRepeat())     //下
    {
        if(plane->pressflag_s)
        {
            plane->direction_s = 0;
        }
        plane->pressflag_s = false;
    }
    if((event->key() == Qt::Key_A)&& plane->direction_a == -1 && !event->isAutoRepeat())     //左
    {
        if(plane->pressflag_a)
        {
            plane->direction_a = 0;
        }
        plane->pressflag_a = false;
    }
    if((event->key() == Qt::Key_D)&& plane->direction_d == 1 && !event->isAutoRepeat())     //右
    {
        if(plane->pressflag_d)
        {
            plane->direction_d = 0;
        }
        plane->pressflag_d = false;
    }
}

void MainScene::enemyToScene()
{
    commonrecorder++;
    shootrecorder++;
    speedrecorder++;

    if (commonrecorder > commonenemyinterval)
    {
        for(int i = 0 ; i< commonenemynum;i++)
        {
            if(commonenemys[i].free)
            {
                //敌机空闲状态改为false
                commonenemys[i].free = false;
                //设置坐标
                commonenemys[i].X = rand() % (GAME_WIDTH - commonenemys[i].rect.width());
                commonenemys[i].Y = -commonenemys[i].rect.height();
                break;
            }
        }
        commonrecorder = 0;
    }

    if (shootrecorder > shootenemyinterval)
    {
        for(int i = 0 ; i< shootenemynum;i++)
        {
            if(shootenemys[i].free)
            {
                //敌机空闲状态改为false
                shootenemys[i].free = false;
                //设置坐标
                shootenemys[i].X = rand() % (GAME_WIDTH - shootenemys[i].rect.width());
                shootenemys[i].Y = -shootenemys[i].rect.height();
                break;
            }
        }
        shootrecorder = 0;
    }

    if (speedrecorder > speedenemyinterval)
    {
        for(int i = 0 ; i< speedenemynum;i++)
        {
            if(speedenemys[i].free)
            {
                //敌机空闲状态改为false
                speedenemys[i].free = false;
                //设置坐标
                speedenemys[i].X = rand() % (GAME_WIDTH - speedenemys[i].rect.width());
                speedenemys[i].Y = -speedenemys[i].rect.height();
                break;
            }
        }
        speedrecorder = 0;
    }

}

void MainScene::collisionDetection()
{
    //遍历所有非空闲的普通敌机
    for(int i = 0 ;i < commonenemynum;i++)
    {
        if(commonenemys[i].free)
        {
            //空闲飞机 跳转下一次循环
            continue;
        }

        //导弹碰撞判定
        if (missle.misslefree == false && commonenemys[i].rect.intersects(missle.rect))
        {
            missle.bomb(commonenemynum, shootenemynum, speedenemynum, commonenemys, shootenemys, speedenemys);
        }

        //遍历所有非空闲的子弹
        for(int j = 0 ; j < BULLET_NUM;j++)
        {
            if(plane->bullets[j].free)
            {
                //空闲子弹 跳转下一次循环
                continue;
            }

            //如果子弹矩形框和敌机矩形框相交，发生碰撞
            if(commonenemys[i].rect.intersects(plane->bullets[j].rect))
            {
                //敌机与碰撞的子弹变为空闲
                commonenemys[i].free = true;
                plane->bullets[j].free = true;
                //爆炸变为非空闲
                commonenemys[i].bombfree = false;

                data.destoryshootenemy++;   //击毁普通敌机数加一
            }
        }
    }

    //遍历所有非空闲的射击敌机
    for(int i = 0 ;i < shootenemynum;i++)
    {
        //遍历所非空闲的敌机子弹
        for(int j = 0 ; j < BULLET_NUM;j++)
        {
            if(shootenemys[i].bullets[j].free)
            {
                //空闲子弹 跳转下一次循环
                continue;
            }

            //如果子弹矩形框和敌机子弹矩形框相交，发生碰撞
            if(shootenemys[i].bullets[j].rect.intersects(plane->rect))
            {
                //敌机子弹变为空闲
                shootenemys[i].bullets[j].free = true;
                data.beshottime++;  //被敌机子弹击中次数加一
                if (plane->health>0)
                {
                    plane->health--;
                }
                else
                {
                    data.destroyedbyshootenemy++;   //被射击敌机击毁次数加一
                    plane->isdeath = true;
                    plane->bombfree = false;
                }
            }
        }

        if(shootenemys[i].free)
        {
            //空闲飞机 跳转下一次循环
            continue;
        }

        //导弹碰撞判定
        if (missle.misslefree == false && commonenemys[i].rect.intersects(missle.rect))
        {
            missle.bomb(commonenemynum, shootenemynum, speedenemynum, commonenemys, shootenemys, speedenemys);
        }

        //判定敌机与主机碰撞
        if (shootenemys[i].rect.intersects(plane->rect))
        {
            shootenemys[i].free = true;
            shootenemys[i].bombfree = false;
            data.destoryshootenemy++;   //击毁射击敌机数加一
            data.crashtime++;   //与敌机碰撞次数加一
            if (plane->health>0)
            {
                plane->health--;
            }
            else
            {
                data.destroyedbyshootenemy++;   //被射击敌机击毁次数加一
                plane->isdeath = true;
                plane->bombfree = false;
            }
        }

        //遍历所有非空闲的子弹
        for(int j = 0 ; j < BULLET_NUM;j++)
        {
            if(plane->bullets[j].free)
            {
                //空闲子弹 跳转下一次循环
                continue;
            }

            //如果子弹矩形框和敌机矩形框相交，发生碰撞
            if(shootenemys[i].rect.intersects(plane->bullets[j].rect))
            {
                //敌机与碰撞的子弹变为空闲
                shootenemys[i].free = true;
                plane->bullets[j].free = true;
                //爆炸变为非空闲
                shootenemys[i].bombfree = false;

                data.destoryshootenemy++;   //击毁射击敌机数加一
            }
        }
    }

    //遍历所有速度敌机
    for(int i = 0 ;i < speedenemynum;i++)
    {
        if(speedenemys[i].free)
        {
            //空闲飞机 跳转下一次循环
            continue;
        }

        //导弹碰撞判定
        if (missle.misslefree == false && commonenemys[i].rect.intersects(missle.rect))
        {
            missle.bomb(commonenemynum, shootenemynum, speedenemynum, commonenemys, shootenemys, speedenemys);
        }

        //判定敌机与主机碰撞
        if (speedenemys[i].rect.intersects(plane->rect))
        {
            speedenemys[i].free = true;
            speedenemys[i].bombfree = false;
            data.destorycommonenemy++;  //击毁普通敌机数加一
            data.crashtime++;   //与敌机碰撞次数加一
            if (plane->health>0)
            {
                plane->health--;
            }
            else
            {
                data.destroyedbycommonenemy++;   //被普通敌机击毁次数加一
                plane->isdeath = true;
                plane->bombfree = false;
            }
        }

        //遍历所有非空闲的子弹
        for(int j = 0 ; j < BULLET_NUM;j++)
        {
            if(plane->bullets[j].free)
            {
                //空闲子弹 跳转下一次循环
                continue;
            }

            //如果子弹矩形框和敌机矩形框相交，发生碰撞
            if(speedenemys[i].rect.intersects(plane->bullets[j].rect))
            {
                //敌机与碰撞的子弹变为空闲
                speedenemys[i].free = true;
                plane->bullets[j].free = true;
                //爆炸变为非空闲
                speedenemys[i].bombfree = false;

                data.destoryshootenemy++;   //击毁普通敌机数加一
            }
        }
    }

}












