#include "headers_game/mainscene.h"
#include "headers_game/config.h"
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

    //文本信息的初始化
    inittext();

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
    speedrecorder= 0;
    commonenemyinterval = 50;
    shootenemyinterval = 200;
    speedenemyinterval = 100;

    //设置技能参数
    missle.setBombPath(MISSLEBOMB_PATH);

    //掉落物最大数量
    dropobjectnum = 5;
    bloodbagnum = 1;
    //掉落物刷新间隔
    droprecorder = 0;
    dropobjectinterval = 500;
    bloodbagrecorder = 0;
    bloodbaginterval = 100;
    //初始化掉落物
    dropobjects = new DropObject[dropobjectnum];
    bloodbags = new BloodBag[bloodbagnum];
    //设置掉落物参数
    for (int i=0; i<dropobjectnum; i++)
    {
        dropobjects[i].setObjectPath(DROPOBJECT_PATH);
    }
    for (int i=0; i<bloodbagnum; i++)
    {
        bloodbags[i].setObjectPath(BLOODBAG_PATH);
    }
    //BOSS信息
    isboss = false;
    bossrecorder = 0;
    bossinterval = 5000;
}

void MainScene::initScene()
{
    //随机数种子
    srand((unsigned int)time(NULL));

    map2.load(MAP_PATH);

    //窗口大小
    setFixedSize(GAME_WIDTH+400 ,GAME_HEIGHT);
    //窗口标题
    setWindowTitle(GAME_TITLE);
    //窗口图标
    setWindowIcon(QIcon(GAME_ICON));
    //定时器设置
    Timer.setInterval(GAME_RATE);
    //启动游戏
    playGame();
}

void MainScene::inittext()
{
    //定时器设置
    QTimer* timer_value_of_life = new QTimer;
    timer_value_of_life->start(500);
    connect(timer_value_of_life,&QTimer::timeout,[=](){
        label_value_of_life.setText(QStringLiteral("生命值: ")+QString::number(plane->health));
    });

    QTimer* timer_value_of_boss = new QTimer;
        timer_value_of_boss->start(500);
        connect(timer_value_of_boss,&QTimer::timeout,[=](){
            label_value_of_boss.setText(QStringLiteral("boss血量: ")+QString::number(boss.health));
    });

    QTimer* timer_cd_of_laser = new QTimer;
    timer_cd_of_laser->start(500);
    connect(timer_cd_of_laser, &QTimer::timeout,[=](){
        if(laser.skillrecorder<laser.cd)
        {
            label_cd_of_laser.setText(QStringLiteral("玛卡巴卡射线:         ")+QString::number(int(laser.skillrecorder*100/laser.cd))+QString("%"));
        }
        if(laser.skillrecorder>=laser.cd)
        {
            label_cd_of_laser.setText(QStringLiteral("玛卡巴卡射线:        ")+QString::number(100)+QString("%"));
        }
    });

    QTimer* timer_cd_of_missle = new QTimer;
    timer_cd_of_missle->start(500);
    connect(timer_cd_of_missle, &QTimer::timeout,[=](){
        if(missle.skillrecorder<missle.cd)
        {
            label_cd_of_missle.setText(QStringLiteral("FOF导弹全弹发射:      ")+QString::number(int(missle.skillrecorder*100/missle.cd))+QString("%"));
        }
        if(missle.skillrecorder>=missle.cd)
        {
            label_cd_of_missle.setText(QStringLiteral("FOF导弹全弹发射:      ")+QString::number(100)+QString("%"));
        }
    });

    QTimer* timer_cd_of_screenclear = new QTimer;
    timer_cd_of_screenclear->start(500);
    connect(timer_cd_of_screenclear, &QTimer::timeout,[=](){
        if(screenclear.skillrecorder<screenclear.cd)
        {
            label_cd_of_screenclear.setText(QStringLiteral("大慈大悲渡世人:       ")+QString::number(int(screenclear.skillrecorder*100/screenclear.cd))+QString("%"));
        }
        if(screenclear.skillrecorder>=screenclear.cd)
        {
            label_cd_of_screenclear.setText(QStringLiteral("大慈大悲渡世人:       ")+QString::number(100)+QString("%"));
        }
    });

    QTimer* timer_cd_of_shield = new QTimer;
    timer_cd_of_shield->start(500);
    connect(timer_cd_of_shield, &QTimer::timeout,[=](){
        if(shield.skillrecorder<shield.cd)
        {
            label_cd_of_shield.setText(QStringLiteral("用一次就失去无敌的屑:  ")+QString::number(int(shield.skillrecorder*100/shield.cd))+QString("%"));
        }
        if(shield.skillrecorder>=shield.cd)
        {
            label_cd_of_shield.setText(QStringLiteral("用一次就失去无敌的屑:  ")+QString::number(100)+QString("%"));
        }
    });


    //文本设置
    QFont font1("Consolas", 16);
    QFont font_cd("Consolas", 12);

    label_value_of_life.setParent(this);
    label_value_of_life.setFont(font1);
    label_value_of_life.setFrameShape(QFrame::Panel);
    label_value_of_life.setFrameShadow(QFrame::Plain);
    label_value_of_life.move(620,20);
    label_value_of_life.resize(200,80);

    label_value_of_boss.setParent(this);
    label_value_of_boss.setFont(font_cd);
    label_value_of_boss.setFrameShape(QFrame::Panel);
    label_value_of_boss.setFrameShadow(QFrame::Plain);
    label_value_of_boss.move(620,110);
    label_value_of_boss.resize(300,80);

    label_cd_of_laser.setParent(this);
    label_cd_of_laser.setFont(font_cd);
    label_cd_of_laser.setFrameShape(QFrame::Panel);
    label_cd_of_laser.setFrameShadow(QFrame::Plain);
    label_cd_of_laser.move(620,300);
    label_cd_of_laser.resize(350,60);

    label_cd_of_missle.setParent(this);
    label_cd_of_missle.setFont(font_cd);
    label_cd_of_missle.setFrameShape(QFrame::Panel);
    label_cd_of_missle.setFrameShadow(QFrame::Plain);
    label_cd_of_missle.move(620,370);
    label_cd_of_missle.resize(350,60);

    label_cd_of_screenclear.setParent(this);
    label_cd_of_screenclear.setFont(font_cd);
    label_cd_of_screenclear.setFrameShape(QFrame::Panel);
    label_cd_of_screenclear.setFrameShadow(QFrame::Plain);
    label_cd_of_screenclear.move(620,440);
    label_cd_of_screenclear.resize(350,60);

    label_cd_of_shield.setParent(this);
    label_cd_of_shield.setFont(font_cd);
    label_cd_of_shield.setFrameShape(QFrame::Panel);
    label_cd_of_shield.setFrameShadow(QFrame::Plain);
    label_cd_of_shield.move(620,510);
    label_cd_of_shield.resize(350,60);
}

void MainScene::playGame()
{
    //启动定时器
    Timer.start();

    //监听定时器
    connect(&Timer,&QTimer::timeout,[=](){
        //飞机移动射击
        planeMove();
        //掉落物出场
        objectToScene();
        if (boss.free)
        {
            //敌机出场
            enemyToScene();
        }
        //更新游戏元素坐标
        updatePosition();
        //重新绘制图片
        update();
        //刷新技能
        updateSkill();
        //BOSS出现
        if (boss.free)
        {
            //碰撞检测
            collisionDetection();
        }
        else
        {
            //BOSS碰撞
            bosscollisionDetection();
        }
    });
}

void MainScene::planeMove()
{
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
}

void MainScene::updateSkill()
{
    //清屏
    if (screenclear.free == false)
    {
        screenclear.skillrecorder++;
        if (screenclear.skillrecorder >= screenclear.cd)
        {
            screenclear.free = true;
        }
    }
    //激光
    if (laser.free == false)
    {
        laser.skillrecorder++;
        if (laser.skillrecorder >= laser.cd)
        {
            laser.free = true;
        }
    }
    //导弹
    if (missle.free == false && missle.misslefree == true)
    {
        missle.skillrecorder++;
        if (missle.skillrecorder >= missle.cd)
        {
            missle.free = true;
        }
    }
    //护盾
    if (shield.free == false){
        if (shield.shieldfree == false)
        {
            shield.shieldrecorder++;
            if (shield.shieldrecorder >= shield.duration)
            {
                shield.shieldfree = true;
                shield.end(plane);
            }
        }
        else
        {
            shield.skillrecorder++;
            if (shield.skillrecorder >= shield.cd)
            {
                shield.free = true;
            }
        }
    }
}

void MainScene::updatePosition()
{
    //更新BOSS信息
    if (boss.isanger == false && boss.health < 500)
    {
        boss.isanger = true;
    }
    bossrecorder++;
    if (bossrecorder > bossinterval)
    {
        boss.free = false;
    }


    //更新地图坐标
    map1.mapPosition();

    //计算子弹坐标
    for(int i = 0 ;i < BULLET_NUM;i++)
    {
        //如果子弹状态为非空闲，计算发射位置
        if(!plane->bullets[i].free)
        {
            plane->bullets[i].updatePosition();
        }
    }

    //BOSS是否在场
    if (boss.free)
    {
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
    }
    else
    {
        //BOSS移动
        boss.updatePosition();
        boss.shoot();
        //更新BOSS子弹位置
        for (int i=0; i<BOSSBULLET_NUM; i++)
        {
            if (boss.bullets[i].free == false)
            {
                boss.bullets[i].updatePosition();
            }
        }
        for (int i=0; i<BOSSBULLET_NUM; i++)
        {
            if (boss.bossbullets[i].free == false)
            {
                boss.bossbullets[i].updatePosition();
            }
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

    //导弹爆炸
    if (missle.bombfree == false)
    {
        missle.updateInfo();
    }

    //清屏
    if (screenclear.screenclearfree == false)
    {
        screenclear.updatePosition();
    }

    //激光发射
    if (laser.laserfree == false)
    {
        laser.updateInfo();
    }
    //护盾出现
    if (shield.shieldstartfree == false)
    {
        shield.updateInfo(plane);
    }

    //掉落物坐标计算
    for(int i = 0 ; i< dropobjectnum;i++)
    {
        //更新坐标
        if(dropobjects[i].free == false)
        {
           dropobjects[i].updatePosition();
        }
    }
    for(int i = 0 ; i< bloodbagnum;i++)
    {
        //更新坐标
        if(bloodbags[i].free == false)
        {
           bloodbags[i].updatePosition();
        }
    }
}

void MainScene::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    //绘制地图
    painter.drawPixmap(0,map1.map1_posY , map1.map1);
    painter.drawPixmap(0,map1.map2_posY , map1.map2);
    painter.drawPixmap(GAME_WIDTH, 0, map2);

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

    if (boss.free)
    {
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
    }
    else
    {
        //绘制BOSS
        painter.drawPixmap(boss.X, boss.Y, boss.boss);
        //绘制BOSS子弹
        for (int i=0; i<BOSSBULLET_NUM; i++)
        {
            if (boss.bullets[i].free == false)
            {
                painter.drawPixmap(boss.bullets[i].X, boss.bullets[i].Y, boss.bullets[i].bullet);
            }
        }
        for (int i=0; i<BOSSBULLET_NUM; i++)
        {
            if (boss.bossbullets[i].free == false)
            {
                painter.drawPixmap(boss.bossbullets[i].X, boss.bossbullets[i].Y, boss.bossbullets[i].bullet);
            }
        }
    }

    //绘制导弹
    if (missle.misslefree == false)
    {
        painter.drawPixmap(missle.X, missle.Y, missle.missle);
    }

    //绘制导弹爆炸
    if (missle.bombfree == false)
    {
        painter.drawPixmap(missle.X-100, missle.Y-100, missle.pixArr[missle.index]);
    }

    //清屏
    if (screenclear.screenclearfree == false)
    {
        painter.drawPixmap(0, screenclear.y, screenclear.clear);
    }

    //绘制激光
    if (laser.laserfree == false)
    {
        painter.drawPixmap(plane->X, plane->Y-700, laser.pixArr[laser.index]);
        laser.shoot(plane->X, plane->Y, commonenemynum, shootenemynum, speedenemynum, commonenemys, shootenemys, speedenemys, boss);
    }

    //护盾出现
    if (shield.shieldstartfree == false)
    {
        painter.drawPixmap(plane->X, plane->Y, shield.pixArr[shield.index]);
    }

    //绘制掉落物
        for(int i = 0 ; i< dropobjectnum;i++)
        {
            if(dropobjects[i].free == false)
            {
                painter.drawPixmap(dropobjects[i].X,dropobjects[i].Y,dropobjects[i].object);
            }
        }
        for(int i = 0 ; i< bloodbagnum;i++)
        {
            if(bloodbags[i].free == false)
            {
                painter.drawPixmap(bloodbags[i].X,bloodbags[i].Y,bloodbags[i].object);
            }
        }
}

void MainScene::objectToScene()
{
    droprecorder++;
    bloodbagrecorder++;

    if (droprecorder > dropobjectinterval )
    {
        for(int i = 0 ; i< dropobjectnum;i++)
        {
            if(dropobjects[i].free)
            {
                //状态改为false
                dropobjects[i].free = false;
                //设置坐标
                dropobjects[i].X = rand() % (GAME_WIDTH - dropobjects[i].rect.width());
                if(dropobjects[i].X-75<0){
                    dropobjects[i].widthl = 0;
                    dropobjects[i].widthr = dropobjects[i].X +75;
                }
                else {
                    dropobjects[i].widthl = dropobjects[i].X -75;
                    dropobjects[i].widthr = dropobjects[i].X +75;
                }
                if(dropobjects[i].X+75>GAME_WIDTH){
                    dropobjects[i].widthl = dropobjects[i].X -75;
                    dropobjects[i].widthr = GAME_WIDTH;
                }
                else {
                    dropobjects[i].widthl = dropobjects[i].X -75;
                    dropobjects[i].widthr = dropobjects[i].X +75;
                }
                dropobjects[i].Y = -dropobjects[i].rect.height();
                break;
            }
        }
        droprecorder = 0;
    }
    if (bloodbagrecorder > bloodbaginterval )
    {
        for(int i = 0 ; i< bloodbagnum;i++)
        {
            if(bloodbags[i].free)
            {
                //状态改为false
                bloodbags[i].free = false;
                //设置坐标
                bloodbags[i].X = rand() % (GAME_WIDTH - bloodbags[i].rect.width());
                if(bloodbags[i].X-75<0){
                    bloodbags[i].widthl = 0;
                    bloodbags[i].widthr = bloodbags[i].X +75;
                }
                else {
                    bloodbags[i].widthl = bloodbags[i].X -75;
                    bloodbags[i].widthr = bloodbags[i].X +75;
                }
                if(bloodbags[i].X+75>GAME_WIDTH){
                    bloodbags[i].widthl = bloodbags[i].X -75;
                    bloodbags[i].widthr = GAME_WIDTH;
                }
                else {
                    bloodbags[i].widthl = bloodbags[i].X -75;
                    bloodbags[i].widthr = bloodbags[i].X +75;
                }
                bloodbags[i].Y = -bloodbags[i].rect.height();
                break;
            }
        }
        bloodbagrecorder = 0;
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
            screenclear.shoot();
        }
    }
    if (event->key() == Qt::Key_L && !event->isAutoRepeat())
    {
        if (laser.free == true)
        {
            laser.use();
        }
    }
    if (event->key() == Qt::Key_U && !event->isAutoRepeat())
    {
        if (missle.free == true)
        {
            missle.shoot(plane->X + plane->rect.width()/2, plane->Y);
        }
    }
    if (event->key() == Qt::Key_I && !event->isAutoRepeat())
    {
        if (shield.free == true)
        {
            shield.use();
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
            if(commonenemys[i].free && commonenemys[i].bombfree)
            {
                //敌机空闲状态改为false
                commonenemys[i].free = false;
                commonenemys[i].bombfree = true;
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
            if(shootenemys[i].free && shootenemys[i].bombfree)
            {
                //敌机空闲状态改为false
                shootenemys[i].free = false;
                shootenemys[i].bombfree = true;
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
            if(speedenemys[i].free && speedenemys[i].bombfree)
            {
                //敌机空闲状态改为false
                speedenemys[i].free = false;
                speedenemys[i].bombfree = true;
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
        //清屏判定
        if (screenclear.screenclearfree == false && commonenemys[i].rect.intersects(screenclear.rect))
        {
            commonenemys[i].free = true;
            commonenemys[i].bombfree = false;
        }
        //导弹碰撞判定
        if (missle.misslefree == false && commonenemys[i].rect.intersects(missle.rect))
        {
            missle.bomb(commonenemynum, shootenemynum, speedenemynum, commonenemys, shootenemys, speedenemys);
        }

        //判定敌机与主机碰撞
        if (commonenemys[i].rect.intersects(plane->rect))
        {
            commonenemys[i].free = true;
            commonenemys[i].bombfree = false;
            data.destorycommonenemy++;  //击毁普通敌机数加一
            data.crashtime++;   //与敌机碰撞次数加一
            if (shield.shieldfree == true)
            {
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
                commonenemys[i].free = true;
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

            //清屏判定
            if (screenclear.screenclearfree == false && shootenemys[i].bullets[j].rect.intersects(screenclear.rect))
            {
                shootenemys[i].bullets[j].free = true;
            }

            //如果子弹矩形框和敌机子弹矩形框相交，发生碰撞
            if(shootenemys[i].bullets[j].rect.intersects(plane->rect))
            {
                //敌机子弹变为空闲
                shootenemys[i].bullets[j].free = true;
                data.beshottime++;  //被敌机子弹击中次数加一
                if (shield.shieldfree == true)
                {
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
        }

        if(shootenemys[i].free)
        {
            //空闲飞机 跳转下一次循环
            continue;
        }

        //清屏判定
        if (screenclear.screenclearfree == false && shootenemys[i].rect.intersects(screenclear.rect))
        {
            shootenemys[i].free = true;
            shootenemys[i].bombfree = false;
        }

        //导弹碰撞判定
        if (missle.misslefree == false && shootenemys[i].rect.intersects(missle.rect))
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
            if (shield.shieldfree == true)
            {
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
                shootenemys[i].free = true;
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

        //清屏判定
        if (screenclear.screenclearfree == false && speedenemys[i].rect.intersects(screenclear.rect))
        {
            speedenemys[i].free = true;
            speedenemys[i].bombfree = false;
        }

        //导弹碰撞判定
        if (missle.misslefree == false && speedenemys[i].rect.intersects(missle.rect))
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
            if (shield.shieldfree == true)
            {
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
                speedenemys[i].free = true;
                speedenemys[i].bombfree = false;

                data.destoryshootenemy++;   //击毁普通敌机数加一
            }
        }
    }
    //遍历所有非空闲的掉落物
      for(int i = 0 ;i < dropobjectnum;i++)
      {
          if(dropobjects[i].free)
          {
              //空闲 跳转下一次循环
              continue;
          }

          //判定与主机碰撞
          if (dropobjects[i].rect.intersects(plane->rect))
          {
              dropobjects[i].free = true;
          }
      }

      //遍历所有非空闲的掉落物
      for(int i = 0 ;i < bloodbagnum;i++)
      {
          if(bloodbags[i].free)
          {
              //空闲 跳转下一次循环
              continue;
          }

          //判定血包与主机碰撞
          if (bloodbags[i].rect.intersects(plane->rect))
          {
              bloodbags[i].free = true;
              plane->health++;
          }
      }
}

void MainScene::bosscollisionDetection()
{
    //与BOSS碰撞
    if (boss.rect.intersects(plane->rect))
    {
        if (shield.shieldfree == true)
        {
            if (plane->health>0)
            {
                plane->health--;
            }
            else
            {
                plane->isdeath = true;
                plane->bombfree = false;
            }
        }
    }

    //与BOSS子弹碰撞
    for (int i=0; i<BOSSBULLET_NUM; i++)
    {
        if (boss.isanger)
        {
            if (boss.bullets[i].free)
            {
                //空闲子弹 跳转下一次循环
                continue;
            }

            //清屏判定
            if (screenclear.screenclearfree == false && boss.bullets[i].rect.intersects(screenclear.rect))
            {
                boss.bullets[i].free = true;
            }

            if (boss.bullets[i].rect.intersects(plane->rect))
            {
                boss.bullets[i].free = true;
                if (shield.shieldfree == true)
                {
                    if (plane->health>0)
                    {
                        plane->health--;
                    }
                    else
                    {
                        plane->isdeath = true;
                        plane->bombfree = false;
                    }
                }
            }
        }
        else
        {
            if (boss.bossbullets[i].free)
            {
                //空闲子弹 跳转下一次循环
                continue;
            }

            //清屏判定
            if (screenclear.screenclearfree == false && boss.bossbullets[i].rect.intersects(screenclear.rect))
            {
                boss.bossbullets[i].free = true;
            }

            if (boss.bossbullets[i].rect.intersects(plane->rect))
            {
                boss.bossbullets[i].free = true;
                if (shield.shieldfree == true)
                {
                    if (plane->health>0)
                    {
                        plane->health--;
                    }
                    else
                    {
                        plane->isdeath = true;
                        plane->bombfree = false;
                    }
                }
            }
        }
    }

    //攻击BOSS判定
    //射击BOSS
    for (int i=0; i<BULLET_NUM; i++)
    {
        if(plane->bullets[i].free)
        {
            //空闲子弹 跳转下一次循环
            continue;
        }

        if (plane->bullets[i].rect.intersects(boss.rect))
        {
            plane->bullets[i].free = true;
            if (boss.health > 0)
            {
                boss.health--;
            }
            else
            {
                boss.isdeath = true;
            }
        }
    }

    //导弹碰撞判定
    if (missle.misslefree == false && missle.rect.intersects(boss.rect))
    {
        missle.bomb(commonenemynum, shootenemynum, speedenemynum, commonenemys, shootenemys, speedenemys);
        if (boss.health > 0)
        {
            boss.health -= 30;
        }
        else
        {
            boss.isdeath = true;
        }
    }

    //遍历所有非空闲的掉落物
      for(int i = 0 ;i < dropobjectnum;i++)
      {
          if(dropobjects[i].free)
          {
              //空闲 跳转下一次循环
              continue;
          }

          //判定与主机碰撞
          if (dropobjects[i].rect.intersects(plane->rect))
          {
              dropobjects[i].free = true;
          }
      }

      //遍历所有非空闲的掉落物
      for(int i = 0 ;i < bloodbagnum;i++)
      {
          if(bloodbags[i].free)
          {
              //空闲 跳转下一次循环
              continue;
          }

          //判定血包与主机碰撞
          if (bloodbags[i].rect.intersects(plane->rect))
          {
              bloodbags[i].free = true;
              plane->health++;
          }
      }
}












