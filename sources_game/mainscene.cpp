#include "headers_game/mainscene.h"
#include "headers_game/config.h"
#include <QIcon>
#include <QDebug>
#include <QPainter>
#include <QMouseEvent>
#include <ctime>
MainScene::MainScene(int difficulty, int model, Player *p, CommonRecord *commonrecord,
                     EndlessRecord *endlessrecord, QWidget *parent)
    : QWidget(parent), difficulty(difficulty), model(model)
{
    //用户
    player = p;

    //记录
    this->commonrecord = commonrecord;
    this->endlessrecord = endlessrecord;

    //飞机参数初始化
    initplane();

    //文本信息的初始化
    inittext();

    //掉落物参数初始化
    initobject();

    //界面组件初始化
    initmenu();

    //场景的初始化
    initScene();
}

MainScene::~MainScene()
{
}

void MainScene::initplane()
{
    //敌机最大数量
    commonenemynum = 20 + difficulty;
    shootenemynum = 10 + difficulty;
    speedenemynum = 15 + difficulty;

    //初始化飞机
    plane = new CommonMyPlane(COMMONMYPLANE_PATH, COMMONMYBOMB_PATH);
    plane->health = player->myplane_health;
    plane->speed = player->myplane_speed;
    plane->bulletinterval = player->myplane_bulletinterval;
    plane->setplanePath(player->myplane_path);

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
        for (int j=0; j<BULLET_NUM; j++)
        {
            shootenemys[i].bullets[j].setBulletPath(ENEMYBULLET_PATH);
        }
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
    commonenemyinterval = 50 - difficulty * 2;
    shootenemyinterval = 200 - difficulty * 10;
    speedenemyinterval = 100 - difficulty * 4;

    //设置技能参数
    missle.setBombPath(MISSLEBOMB_PATH);

    //技能参数
    screenclear.skillrecorder = screenclear.cd;
    laser.skillrecorder = laser.cd;
    missle.skillrecorder = missle.cd;
    shield.skillrecorder = shield.cd;

    //BOSS信息
    bossrecorder = 0;
    bossinterval = 5000 + difficulty * 1000;
    boss.setBombPath(BOMB_BOSS_PATH);

    //暂停参数
    ispause = false;

    //游戏参数
    difficultyinterval = 5000;
    difficultyrecorder = 0;
    isgameover = false;
}

void MainScene::initobject()
{
    //掉落物最大数量
    scdfreenum = 1;
    bcdfreenum = 1;
    bloodbagnum = 1;
    coinnum = 1;
    //掉落物刷新间隔
    objectrecorder = 0;
    objectinterval = 500;
    //初始化掉落物
    scdfrees = new ScdFree[scdfreenum];
    bcdfrees = new BcdFree[bcdfreenum];
    bloodbags = new BloodBag[bloodbagnum];
    coins = new Coin[coinnum];
    //设置掉落物参数

    for (int i=0; i<bloodbagnum; i++)
    {
        bloodbags[i].setObjectPath(BLOODBAG_PATH);
    }
    for (int i=0; i<scdfreenum; i++)
    {
        scdfrees[i].setObjectPath(SCDFREE_PATH);
    }
    for (int i=0; i<bcdfreenum; i++)
    {
        bcdfrees[i].setObjectPath(BCDFREE_PATH);
    }

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
            if(model == 0)
            {
                if(boss.health>0)
                {
                    label_value_of_boss.setText(QStringLiteral("boss血量: ")+QString::number(boss.health));
                }
                else
                {
                    label_value_of_boss.setText(QStringLiteral("boss血量: ")+QString::number(0));
                }
            }
            else if(model == 1)
            {
                label_value_of_boss.setText(QStringLiteral("难度提升进度: ")+QString::number(difficultyrecorder*100/difficultyinterval)+QString("%"));
            }

    });

    QTimer* timer_score = new QTimer;
    timer_score->start(500);
    connect(timer_score,&QTimer::timeout,[=](){
        label_score.setText(QStringLiteral("得分:")+QString::number(data.score));
    });

    QTimer* timer_progress_of_boss = new QTimer;
    timer_progress_of_boss->start(500);
    connect(timer_progress_of_boss,&QTimer::timeout,[=](){
        if(model == 0)
        {
            if(bossrecorder*100/bossinterval<99)
            {
                label_progress_of_boss.setText(QStringLiteral("boss出现进度:")+QString::number(bossrecorder*100/bossinterval)+QString("%"));
            }
            else
            {
                timer_progress_of_boss->stop();
                label_progress_of_boss.setAutoFillBackground(true);
                QPalette palette;
                palette.setColor(QPalette::Background, QColor(255,0,0));
                label_progress_of_boss.setPalette(palette);
                label_progress_of_boss.setText(QStringLiteral("boss已出现！"));
            }
        }
        else if(model == 1)
        {
            label_progress_of_boss.setText(QStringLiteral("难度: ")+QString::number(difficulty));
        }
    });

    QTimer* timer_cd_of_laser = new QTimer;
    timer_cd_of_laser->start(500);
    connect(timer_cd_of_laser, &QTimer::timeout,[=](){
        if (player->has_laser == true)
        {
            if(laser.skillrecorder<laser.cd)
            {
                label_cd_of_laser.setText(QStringLiteral("L  激光:    ")+QString::number(int(laser.skillrecorder*100/laser.cd))+QString("%"));
                label_cd_of_laser.setAutoFillBackground(true);
                QPalette palette;
                palette.setColor(QPalette::Background, QColor(255,255,255));
                label_cd_of_laser.setPalette(palette);
            }
            if(laser.skillrecorder>=laser.cd)
            {
                label_cd_of_laser.setText(QStringLiteral("L  激光:    ")+QString::number(100)+QString("%"));
                label_cd_of_laser.setAutoFillBackground(true);
                QPalette palette;
                palette.setColor(QPalette::Background, QColor(0,255,0));
                label_cd_of_laser.setPalette(palette);
            }
        }
        else
        {
            label_cd_of_laser.setText(QStringLiteral("L  激光:    未解锁"));
            label_cd_of_laser.setAutoFillBackground(true);
            QPalette palette;
            palette.setColor(QPalette::Background, QColor(255,255,255));
            label_cd_of_laser.setPalette(palette);
        }

    });

    QTimer* timer_cd_of_missle = new QTimer;
    timer_cd_of_missle->start(500);
    connect(timer_cd_of_missle, &QTimer::timeout,[=](){
        if (player->has_missle == true)
        {
            if(missle.skillrecorder<missle.cd)
            {
                label_cd_of_missle.setText(QStringLiteral("U  导弹:    ")+QString::number(int(missle.skillrecorder*100/missle.cd))+QString("%"));
                label_cd_of_missle.setAutoFillBackground(true);
                QPalette palette;
                palette.setColor(QPalette::Background, QColor(255,255,255));
                label_cd_of_missle.setPalette(palette);
            }
            if(missle.skillrecorder>=missle.cd)
            {
                label_cd_of_missle.setText(QStringLiteral("U  导弹:    ")+QString::number(100)+QString("%"));
                label_cd_of_missle.setAutoFillBackground(true);
                QPalette palette;
                palette.setColor(QPalette::Background, QColor(0,255,0));
                label_cd_of_missle.setPalette(palette);
            }
        }
        else
        {
            label_cd_of_missle.setText(QStringLiteral("U  导弹:    未解锁"));
            label_cd_of_missle.setAutoFillBackground(true);
            QPalette palette;
            palette.setColor(QPalette::Background, QColor(255,255,255));
            label_cd_of_missle.setPalette(palette);
        }
    });

    QTimer* timer_cd_of_screenclear = new QTimer;
    timer_cd_of_screenclear->start(500);
    connect(timer_cd_of_screenclear, &QTimer::timeout,[=](){
        if (player->has_screenclear == true)
        {
            if(screenclear.skillrecorder<screenclear.cd)
            {
                label_cd_of_screenclear.setText(QStringLiteral("K  清屏:    ")+QString::number(int(screenclear.skillrecorder*100/screenclear.cd))+QString("%"));
                label_cd_of_screenclear.setAutoFillBackground(true);
                QPalette palette;
                palette.setColor(QPalette::Background, QColor(255,255,255));
                label_cd_of_screenclear.setPalette(palette);
            }
            if(screenclear.skillrecorder>=screenclear.cd)
            {
                label_cd_of_screenclear.setText(QStringLiteral("K  清屏:    ")+QString::number(100)+QString("%"));
                label_cd_of_screenclear.setAutoFillBackground(true);
                QPalette palette;
                palette.setColor(QPalette::Background, QColor(0,255,0));
                label_cd_of_screenclear.setPalette(palette);
            }
        }
        else
        {
            label_cd_of_screenclear.setText(QStringLiteral("K  清屏:    未解锁"));
            label_cd_of_screenclear.setAutoFillBackground(true);
            QPalette palette;
            palette.setColor(QPalette::Background, QColor(255,255,255));
            label_cd_of_screenclear.setPalette(palette);
        }
    });

    QTimer* timer_cd_of_shield = new QTimer;
    timer_cd_of_shield->start(500);
    connect(timer_cd_of_shield, &QTimer::timeout,[=](){
        if (player->has_shield == true)
        {
            if(shield.skillrecorder<shield.cd)
            {
                label_cd_of_shield.setText(QStringLiteral("I  护盾:    ")+QString::number(int(shield.skillrecorder*100/shield.cd))+QString("%"));
                label_cd_of_shield.setAutoFillBackground(true);
                QPalette palette;
                palette.setColor(QPalette::Background, QColor(255,255,255));
                label_cd_of_shield.setPalette(palette);
            }
            if(shield.skillrecorder>=shield.cd)
            {
                label_cd_of_shield.setText(QStringLiteral("I  护盾:    ")+QString::number(100)+QString("%"));
                label_cd_of_shield.setAutoFillBackground(true);
                QPalette palette;
                palette.setColor(QPalette::Background, QColor(0,255,0));
                label_cd_of_shield.setPalette(palette);
            }
        }
        else
        {
            label_cd_of_shield.setText(QStringLiteral("I  护盾:    未解锁"));
            label_cd_of_shield.setAutoFillBackground(true);
            QPalette palette;
            palette.setColor(QPalette::Background, QColor(255,255,255));
            label_cd_of_shield.setPalette(palette);
        }
    });


    //文本设置
    QFont font1("Consolas", 14);
    QFont font_cd("Consolas", 12);

    label_value_of_life.setParent(this);
    label_value_of_life.setFont(font1);
    label_value_of_life.setFrameShape(QFrame::Panel);
    label_value_of_life.setFrameShadow(QFrame::Plain);
    label_value_of_life.move(620,20);
    label_value_of_life.resize(160,80);

    label_score.setParent(this);
    label_score.setFont(font_cd);
    label_score.setFrameShape(QFrame::Panel);
    label_score.setFrameShadow(QFrame::Plain);
    label_score.move(800,20);
    label_score.resize(180,80);

    label_value_of_boss.setParent(this);
    label_value_of_boss.setFont(font_cd);
    label_value_of_boss.setFrameShape(QFrame::Panel);
    label_value_of_boss.setFrameShadow(QFrame::Plain);
    label_value_of_boss.move(620,110);
    label_value_of_boss.resize(300,80);

    label_progress_of_boss.setParent(this);
    label_progress_of_boss.setFont(font_cd);
    label_progress_of_boss.setFrameShape(QFrame::Panel);
    label_progress_of_boss.setFrameShadow(QFrame::Plain);
    label_progress_of_boss.move(620,200);
    label_progress_of_boss.resize(350,50);

    label_cd_of_laser.setParent(this);
    label_cd_of_laser.setFont(font_cd);
    label_cd_of_laser.setFrameShape(QFrame::Panel);
    label_cd_of_laser.setFrameShadow(QFrame::Plain);
    label_cd_of_laser.move(620,360);
    label_cd_of_laser.resize(350,60);

    label_cd_of_missle.setParent(this);
    label_cd_of_missle.setFont(font_cd);
    label_cd_of_missle.setFrameShape(QFrame::Panel);
    label_cd_of_missle.setFrameShadow(QFrame::Plain);
    label_cd_of_missle.move(620,430);
    label_cd_of_missle.resize(350,60);

    label_cd_of_screenclear.setParent(this);
    label_cd_of_screenclear.setFont(font_cd);
    label_cd_of_screenclear.setFrameShape(QFrame::Panel);
    label_cd_of_screenclear.setFrameShadow(QFrame::Plain);
    label_cd_of_screenclear.move(620,500);
    label_cd_of_screenclear.resize(350,60);

    label_cd_of_shield.setParent(this);
    label_cd_of_shield.setFont(font_cd);
    label_cd_of_shield.setFrameShape(QFrame::Panel);
    label_cd_of_shield.setFrameShadow(QFrame::Plain);
    label_cd_of_shield.move(620,570);
    label_cd_of_shield.resize(350,60);
}

void MainScene::initmenu()
{
    settlement.setRect(100, 150, 400, 500);

    revive.setText("复活");
    revive.move(200, 500);
    revive.resize(100, 50);

    returnhome.setText("返回主菜单");
    returnhome.move(350, 500);
    returnhome.resize(100, 50);

    pause.setParent(this);
    pause.setText("暂停");
    pause.move(650, 700);
    pause.resize(100, 50);

    connect(&revive, &QPushButton::clicked, this, &MainScene::revive_plane);
    connect(&returnhome, &QPushButton::clicked, this, &MainScene::return_home);
    connect(&pause, &QPushButton::clicked, this, &MainScene::game_pause);

}

void MainScene::playGame()
{
    //启动定时器
    Timer.start();

    //监听定时器
    connect(&Timer,&QTimer::timeout,[=](){

        if (ispause == false)
        {
            if (isgameover == false)
            {
                //飞机移动射击
                planeMove();
                //掉落物出场
                objectToScene();
                if (boss.free && boss.isdeath == false)
                {
                    //敌机出场
                    enemyToScene();
                }
            }
            //更新游戏元素坐标
            updatePosition();
            //重新绘制图片
            update ();
            if (isgameover == false)
            {
                //刷新技能
                updateSkill();
                //BOSS出现
                if (boss.free && boss.isdeath == false)
                {
                    //碰撞检测
                    collisionDetection();
                }
                else
                {
                    //BOSS碰撞
                    bosscollisionDetection();
                }
            }
        }
    });
}

void MainScene::planeMove()
{
    //主机移动
    if (plane->X >= 0 && plane->X <= GAME_WIDTH - plane->rect.width())
    {
        plane->X += (plane->direction_a + plane->direction_d) * plane->speed;
    }
    if (plane->Y >= 0 && plane->Y <= (GAME_HEIGHT - plane->rect.height()))
    {
        plane->Y += (plane->direction_w + plane->direction_s) * plane->speed;
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
    if (isgameover == false)
    {
        if (model == 0)     //为正常模式才刷新BOSS
        {
            //更新BOSS信息
            if (boss.isanger == false && boss.health < 500)
            {
                boss.isanger = true;
            }
            if (boss.free == true)
            {
                bossrecorder++;
            }
            if (bossrecorder > bossinterval)
            {
                bossrecorder = 0;
                boss.free = false;
            }
        }
        else    //无尽模式
        {
            difficultyrecorder++;
            if (difficultyrecorder > difficultyinterval)
            {
                difficulty++;
                difficultyrecorder = 0;
            }
        }
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
    if (boss.free && boss.isdeath == false)
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
        if (boss.isdeath == false)
        {
            boss.updatePosition();
            boss.shoot();
        }
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

    //BOSS爆炸
    if (boss.bombfree == false)
    {
        boss.updateInfo();
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
    for(int i = 0 ; i< bloodbagnum;i++)
    {
        //更新坐标
        if(bloodbags[i].free == false)
        {
            bloodbags[i].updatePosition();
        }
    }

    for(int i = 0 ; i< scdfreenum;i++)
    {
        //更新坐标
        if(scdfrees[i].free == false)
        {
            scdfrees[i].updatePosition();
        }
    }

    for(int i = 0 ; i< bcdfreenum;i++)
    {
        //更新坐标
        if(bcdfrees[i].free == false)
        {
            bcdfrees[i].updatePosition();
        }
    }
    for(int i = 0 ; i< coinnum;i++)
    {
        //更新坐标
        if(coins[i].free == false)
        {
            coins[i].updatePosition();
        }
    }
    for(int i = 0 ; i < coinnum;i++)
    {
        //敌机爆炸
        if(coins[i].free == false)
        {
            coins[i].updateInfo();
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

    if (isgameover == true)
    {
        painter.setPen(Qt::NoPen);
        painter.setBrush(QColor(0,170,255, 100)); // 最后一项为透明度
        painter.drawRoundRect(settlement);// 画圆角矩形
        painter.setPen(QColor(0, 0, 0));

        QFont font1("Consolas", 35);
        QFont font2("Consolas", 20);

        if (model == 0)     //正常模式
        {
            painter.setFont(font1);
            if (plane->isdeath == false)
            {
                painter.drawText(200, 300, "YOU WIN!");
            }
            else
            {
                painter.drawText(160, 300, "TRY AGAIN!");
                revive.setParent(this);
                revive.show();

            }
            painter.setFont(font2);
            painter.drawText(170, 400, QStringLiteral("得分:")+QString::number(data.score));
            painter.drawText(340, 400, QStringLiteral("金币:")+QString::number(data.coin + data.score/20));
            returnhome.setParent(this);
            returnhome.show();
        }
        else        //无尽模式
        {
            painter.setFont(font1);
            painter.drawText(160, 300, "TRY AGAIN!");
            painter.setFont(font2);
            painter.drawText(170, 400, QStringLiteral("得分:")+QString::number(data.score));
            painter.drawText(340, 400, QStringLiteral("金币:")+QString::number(data.coin + data.score/20));
            revive.setParent(this);
            returnhome.setParent(this);
            revive.show();
            returnhome.show();
        }
    }

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

    if (boss.free && boss.isdeath == false)
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
        if (boss.isdeath == false)
        {
            //绘制BOSS
            painter.drawPixmap(boss.X, boss.Y, boss.boss);
        }
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

    //BOSS爆炸
    if (boss.bombfree == false)
    {
        painter.drawPixmap(boss.X, boss.Y, boss.pixArr[boss.index]);
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
        laser.shoot(plane->X, plane->Y, commonenemynum, shootenemynum, speedenemynum, commonenemys, shootenemys, speedenemys, boss, data, isgameover);
    }

    //护盾出现
    if (shield.shieldstartfree == false)
    {
        painter.drawPixmap(plane->X, plane->Y, shield.pixArr[shield.index]);
    }

    //绘制掉落物
    for(int i = 0 ; i< bloodbagnum;i++)
    {
        if(bloodbags[i].free == false)
        {
            painter.drawPixmap(bloodbags[i].X,bloodbags[i].Y,bloodbags[i].object);
        }
    }
    for(int i = 0 ; i< scdfreenum;i++)
    {
        if(scdfrees[i].free == false)
        {
            painter.drawPixmap(scdfrees[i].X,scdfrees[i].Y,scdfrees[i].object);
        }
    }
    for(int i = 0 ; i< bcdfreenum;i++)
    {
        if(bcdfrees[i].free == false)
        {
            painter.drawPixmap(bcdfrees[i].X,bcdfrees[i].Y,bcdfrees[i].object);
        }
    }
    for(int i = 0 ; i< coinnum;i++)
    {
        if(coins[i].free == false)
        {
            painter.drawPixmap(coins[i].X,coins[i].Y,coins[i].pixArr[coins[i].index]);
        }
    }
}

void MainScene::objectToScene()
{
    objectrecorder++;
    int odds=rand() % 8;
    if (objectrecorder > objectinterval &&odds==0)
    {
        for(int i = 0 ; i< bloodbagnum;i++)
        {
            if(bloodbags[i].free)
            {
                //状态改为false
                bloodbags[i].free = false;
                //设置坐标
                bloodbags[i].X = rand() % (GAME_WIDTH - bloodbags[i].rect.width());
                if(bloodbags[i].X-75<=0){
                    bloodbags[i].widthl = 0;
                    bloodbags[i].widthr = bloodbags[i].X +75;
                }
                else if(bloodbags[i].X+75>=GAME_WIDTH){
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
        objectrecorder = 0;
    }

    if (objectrecorder > objectinterval&&(odds==1||odds==2))
    {
        for(int i = 0 ; i< scdfreenum;i++)
        {
            if(scdfrees[i].free)
            {
                //状态改为false
                scdfrees[i].free = false;
                //设置坐标
                scdfrees[i].X = rand() % (GAME_WIDTH - scdfrees[i].rect.width());
                if(scdfrees[i].X-75<0){
                    scdfrees[i].widthl = 0;
                    scdfrees[i].widthr = scdfrees[i].X +75;
                }
                else {
                    scdfrees[i].widthl = scdfrees[i].X -75;
                    scdfrees[i].widthr = scdfrees[i].X +75;
                }
                if(scdfrees[i].X+75>GAME_WIDTH){
                    scdfrees[i].widthl = scdfrees[i].X -75;
                    scdfrees[i].widthr = GAME_WIDTH;
                }
                else {
                    scdfrees[i].widthl = scdfrees[i].X -75;
                    scdfrees[i].widthr = scdfrees[i].X +75;
                }
                scdfrees[i].Y = -scdfrees[i].rect.height();
                break;
            }
        }
        objectrecorder = 0;
    }

    if (objectrecorder > objectinterval &&odds==3)
    {
        for(int i = 0 ; i< bcdfreenum;i++)
        {
            if(bcdfrees[i].free)
            {
                //状态改为false
                bcdfrees[i].free = false;
                //设置坐标
                bcdfrees[i].X = rand() % (GAME_WIDTH - bcdfrees[i].rect.width());
                if(bcdfrees[i].X-75<0){
                    bcdfrees[i].widthl = 0;
                    bcdfrees[i].widthr = bcdfrees[i].X +75;
                }
                else {
                    bcdfrees[i].widthl = bcdfrees[i].X -75;
                    bcdfrees[i].widthr = bcdfrees[i].X +75;
                }
                if(bcdfrees[i].X+75>GAME_WIDTH){
                    bcdfrees[i].widthl = bcdfrees[i].X -75;
                    bcdfrees[i].widthr = GAME_WIDTH;
                }
                else {
                    bcdfrees[i].widthl = bcdfrees[i].X -75;
                    bcdfrees[i].widthr = bcdfrees[i].X +75;
                }
                bcdfrees[i].Y = -bcdfrees[i].rect.height();
                break;
            }
        }
        objectrecorder = 0;
    }

    if (objectrecorder > objectinterval&&odds>3)
    {
        for(int i = 0 ; i< coinnum;i++)
        {
            if(coins[i].free)
            {
                //状态改为false
                coins[i].free = false;
                //设置坐标
                coins[i].X = rand() % (GAME_WIDTH - coins[i].rect.width());
                if(coins[i].X-75<0){
                    coins[i].widthl = 0;
                    coins[i].widthr = coins[i].X +75;
                }
                else {
                    coins[i].widthl = coins[i].X -75;
                    coins[i].widthr = coins[i].X +75;
                }
                if(coins[i].X+75>GAME_WIDTH){
                    coins[i].widthl = coins[i].X -75;
                    coins[i].widthr = GAME_WIDTH;
                }
                else {
                    coins[i].widthl = coins[i].X -75;
                    coins[i].widthr = coins[i].X +75;
                }
                coins[i].Y = -coins[i].rect.height();
                break;
            }
        }
        objectrecorder = 0;
    }
}

void MainScene::mouseMoveEvent(QMouseEvent *event)
{
    if (isgameover) return;
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
    if (isgameover) return;
    //暂停
    if (event->key() == Qt::Key_Escape && !event->isAutoRepeat())
    {
        game_pause();
    }

    //使用技能
    if (event->key() == Qt::Key_K && !event->isAutoRepeat() && player->has_screenclear)
    {
        if (screenclear.free == true)
        {
            screenclear.shoot();
            screenclear.skillrecorder = 0;
            data.screencleartime++;
        }
    }
    if (event->key() == Qt::Key_L && !event->isAutoRepeat() && player->has_laser)
    {
        if (laser.free == true)
        {
            laser.use();
            laser.skillrecorder = 0;
            data.lasertime++;
        }
    }
    if (event->key() == Qt::Key_U && !event->isAutoRepeat() && player->has_missle)
    {
        if (missle.free == true)
        {
            missle.shoot(plane->X + plane->rect.width()/2, plane->Y);
            missle.skillrecorder = 0;
            data.missletime++;
        }
    }
    if (event->key() == Qt::Key_I && !event->isAutoRepeat() && player->has_shield)
    {
        if (shield.free == true)
        {
            shield.use();
            shield.skillrecorder = 0;
            data.shieldtime++;
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
    if (isgameover) return;
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
            data.screencleardestory++;
            data.score += 1 + difficulty;
        }
        //导弹碰撞判定
        if (missle.misslefree == false && commonenemys[i].rect.intersects(missle.rect))
        {
            missle.bomb(commonenemynum, shootenemynum, speedenemynum, commonenemys, shootenemys, speedenemys, data);
        }

        //判定敌机与主机碰撞
        if (commonenemys[i].rect.intersects(plane->rect))
        {
            commonenemys[i].free = true;
            commonenemys[i].bombfree = false;
            data.destorycommonenemy++;  //击毁普通敌机数加一
            data.crashtime++;   //与敌机碰撞次数加一
            data.score += 5 + difficulty;
            if (shield.shieldfree == true)
            {
                if (plane->health>1)
                {
                    plane->health--;
                    data.injury++;
                }
                else
                {
                    data.destroyedbycommonenemy++;   //被普通敌机击毁次数加一
                    plane->isdeath = true;
                    plane->bombfree = false;
                    isgameover = true;
                }
            }
            else
            {
                data.shielddefense++;
                data.score++;
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

                data.destorycommonenemy++;   //击毁普通敌机数加一
                data.score += 5 + difficulty;
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
                data.screencleardestory++;
            }

            //如果子弹矩形框和敌机子弹矩形框相交，发生碰撞
            if(shootenemys[i].bullets[j].rect.intersects(plane->rect))
            {
                //敌机子弹变为空闲
                shootenemys[i].bullets[j].free = true;
                data.beshottime++;  //被敌机子弹击中次数加一
                if (shield.shieldfree == true)
                {
                    if (plane->health>1)
                    {
                        plane->health--;
                        data.injury++;
                    }
                    else
                    {
                        data.destroyedbyshootenemy++;   //被射击敌机击毁次数加一
                        plane->isdeath = true;
                        plane->bombfree = false;
                        isgameover = true;
                    }
                }
                else
                {
                    data.shielddefense++;
                    data.score++;
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
            data.screencleardestory++;
            data.score += 1 + difficulty;
        }

        //导弹碰撞判定
        if (missle.misslefree == false && shootenemys[i].rect.intersects(missle.rect))
        {
            missle.bomb(commonenemynum, shootenemynum, speedenemynum, commonenemys, shootenemys, speedenemys, data);
        }

        //判定敌机与主机碰撞
        if (shootenemys[i].rect.intersects(plane->rect))
        {
            shootenemys[i].free = true;
            shootenemys[i].bombfree = false;
            data.destoryshootenemy++;   //击毁射击敌机数加一
            data.crashtime++;   //与敌机碰撞次数加一
            data.score += 15 + difficulty;
            if (shield.shieldfree == true)
            {
                if (plane->health>1)
                {
                    plane->health--;
                    data.injury++;
                }
                else
                {
                    data.destroyedbyshootenemy++;   //被射击敌机击毁次数加一
                    plane->isdeath = true;
                    plane->bombfree = false;
                    isgameover = true;
                }
            }
            else
            {
                data.shielddefense++;
                data.score++;
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
                data.score += 15 + difficulty;
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
            data.screencleardestory++;
            data.score += 1 + difficulty;
        }

        //导弹碰撞判定
        if (missle.misslefree == false && speedenemys[i].rect.intersects(missle.rect))
        {
            missle.bomb(commonenemynum, shootenemynum, speedenemynum, commonenemys, shootenemys, speedenemys, data);
        }

        //判定敌机与主机碰撞
        if (speedenemys[i].rect.intersects(plane->rect))
        {
            speedenemys[i].free = true;
            speedenemys[i].bombfree = false;
            data.destoryspeedenemy++;  //击毁普通敌机数加一
            data.crashtime++;   //与敌机碰撞次数加一
            data.score += 10 + difficulty;
            if (shield.shieldfree == true)
            {
                if (plane->health>1)
                {
                    plane->health--;
                    data.injury++;
                }
                else
                {
                    data.destroyedbyspeedenemy++;
                    plane->isdeath = true;
                    plane->bombfree = false;
                    isgameover = true;
                }
            }
            else
            {
                data.shielddefense++;
                data.score++;
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

                data.destoryspeedenemy++;   //击毁普通敌机数加一
                data.score += 10 + difficulty;
            }
        }
    }

    //遍历所有非空闲的掉落物
    objectCollisionDetection();
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
                data.injury++;
            }
            else
            {
                plane->isdeath = true;
                plane->bombfree = false;
                data.destroyedbyboss++;
                isgameover = true;
            }
        }
        else
        {
            data.shielddefense++;
            data.score++;
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
                data.screencleardestory++;
            }

            if (boss.bullets[i].rect.intersects(plane->rect))
            {
                boss.bullets[i].free = true;
                data.beshottime++;
                if (shield.shieldfree == true)
                {
                    if (plane->health>1)
                    {
                        plane->health--;
                        data.injury++;
                    }
                    else
                    {
                        plane->isdeath = true;
                        plane->bombfree = false;
                        data.destroyedbyboss++;
                        isgameover = true;
                    }
                }
                else
                {
                    data.shielddefense++;
                    data.score++;
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
                data.screencleardestory++;
            }

            if (boss.bossbullets[i].rect.intersects(plane->rect))
            {
                boss.bossbullets[i].free = true;
                data.beshottime++;
                if (shield.shieldfree == true)
                {
                    if (plane->health>1)
                    {
                        plane->health--;
                        data.injury++;
                    }
                    else
                    {
                        plane->isdeath = true;
                        plane->bombfree = false;
                        data.destroyedbyboss++;
                        isgameover = true;
                    }
                }
                else
                {
                    data.shielddefense++;
                    data.score++;
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
            if (boss.health > 1)
            {
                boss.health--;
                data.damageboss++;
            }
            else
            {
                boss.isdeath = true;
                boss.free = true;
                boss.bombfree = false;
                isgameover = true;
                data.destoryboss++;
                data.score += 1000;
            }
        }
    }

    //导弹碰撞判定
    if (missle.misslefree == false && missle.rect.intersects(boss.rect))
    {
        missle.bomb(commonenemynum, shootenemynum, speedenemynum, commonenemys, shootenemys, speedenemys, data);
        if (boss.health > 1)
        {
            boss.health -= 30;
            data.damageboss += 30;
        }
        else
        {
            boss.isdeath = true;
            boss.free = true;
            boss.bombfree = false;
            isgameover = true;
            data.destoryboss++;
            data.score += 1000;
        }
    }

    //遍历所有非空闲的掉落物
    objectCollisionDetection();
}

void MainScene::objectCollisionDetection()  //掉落物碰撞检测
{
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
            data.cure++;
            plane->health++;
        }
    }

    for(int i = 0 ;i < scdfreenum;i++)
    {
        if(scdfrees[i].free)
        {
            //空闲 跳转下一次循环
            continue;
        }

        //判定小CD与主机碰撞
        if (scdfrees[i].rect.intersects(plane->rect))
        {
            scdfrees[i].free = true;
            laser.skillrecorder = laser.cd;
            missle.skillrecorder = missle.cd;
        }
    }

    for(int i = 0 ;i < bcdfreenum;i++)
    {
        if(bcdfrees[i].free)
        {
            //空闲 跳转下一次循环
            continue;
        }

        //判定大CD与主机碰撞
        if (bcdfrees[i].rect.intersects(plane->rect))
        {
            bcdfrees[i].free = true;
            screenclear.skillrecorder = screenclear.cd;
            shield.skillrecorder = shield.cd;
        }
    }

    for(int i = 0 ;i < coinnum;i++)
    {
        if(coins[i].free)
        {
            //空闲 跳转下一次循环
            continue;
        }

        //判定大CD与主机碰撞
        if (coins[i].rect.intersects(plane->rect))
        {
            coins[i].free = true;
            data.coin += 10;
        }
    }
}

void MainScene::return_home()
{
    //更新数据
    data.coin +=  data.score/20;
    player->mydata.update(data);
    player->coins += data.coin;

    //储存记录
    if (model == 0)     //正常模式
    {
        CommonRecord *record = new CommonRecord(player->id, data.score, data.coin);
        record->update();

        QFile File(COMMONRECORDFILE_PATH);
        QDataStream txt(&File);
        int record_num;
        File.open(QIODevice::ReadOnly);
        txt >> record_num;
        File.close();
        if (record_num == 0)
        {
            return;
        }
        else
        {
            CommonRecord temp[record_num];
            File.open(QIODevice::ReadOnly);
            for (int i=0; i<record_num; i++)
            {
                txt >> record_num >> temp[i].player_name >> temp[i].score >> temp[i].coins;
            }
            sort(temp, temp+record_num, cmp);
            for (int i=0; i<record_num && i<10; i++)
            {
                commonrecord[i] = temp[i];
            }
            File.close();
        }
    }
    else        //无尽模式
    {
        EndlessRecord * record = new EndlessRecord(player->id, data.score, data.coin, difficulty);
        record->update();

        QFile File(ENDLESSRECORDFILE_PATH);
        QDataStream txt(&File);
        int record_num;
        File.open(QIODevice::ReadOnly);
        txt >> record_num;
        File.close();
        if (record_num == 0)
        {
            return;
        }
        else
        {
            EndlessRecord temp[record_num];
            File.open(QIODevice::ReadOnly);
            for (int i=0; i<record_num; i++)
            {
                txt >> record_num >> temp[i].player_name >> temp[i].score >> temp[i].coins >> difficulty;
            }
            sort(temp, temp+record_num, cmp);
            for (int i=0; i<record_num && i<10; i++)
            {
                endlessrecord[i] = temp[i];
            }
            File.close();
        }
    }

    //更新玩家数据文件
    QFile playerFile(PLAYERFILE_PATH);
    QDataStream txt(&playerFile);
    playerFile.open(QIODevice::ReadOnly);
    int player_num;
    txt >> player_num;
    playerFile.close();
    Player player_list[player_num];
    //导出数据
    QString id;         //账户
    QString password;   //密码
    QString phone;
    int coins;  //金币
    //游戏参数
    int myplane_health;           //生命值
    int myplane_speed;            //速度
    int myplane_bulletinterval;   //射速
    QString myplane_path;           //皮肤
    //技能
    bool has_screenclear;
    bool has_laser;
    bool has_missle;
    bool has_shield;
    //道具
    int revivetokens_num;        //复活币

    int score;    //得分
    int coin;    //金币
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

    playerFile.open(QFile::ReadOnly);
    for(int i=0;i<player_num;i++){
        //数据从文件导出
        txt >> player_num >>id >> password  >> phone >> score >> coin >> destorycommonenemy >> destoryshootenemy >> destoryspeedenemy >> myplaneshoottime >>
                crashtime >> beshottime >> destroyedbycommonenemy >> destroyedbyshootenemy >> destroyedbyspeedenemy >> injury >> cure >>
                screencleartime >> lasertime >> missletime >> shieldtime >> screencleardestory >> laserdestory >> missledestory >>
                shielddefense >> damageboss >> destroyedbyboss >> destoryboss >> coins >> myplane_health >> myplane_speed >> myplane_bulletinterval >>
                myplane_path >> has_screenclear >> has_laser >> has_missle >> has_shield >> revivetokens_num;
        qDebug() << player_num << id << password  << has_laser << endl;
        Data mydata(score, coin,destorycommonenemy, destoryshootenemy,  destoryspeedenemy,  myplaneshoottime,
                    crashtime,  beshottime,  destroyedbycommonenemy,  destroyedbyshootenemy,  destroyedbyspeedenemy,
                    injury,  cure,  screencleartime,  lasertime,  missletime,  shieldtime,  screencleardestory,
                    laserdestory,  missledestory,  shielddefense,  damageboss,  destroyedbyboss,  destoryboss);
        player_list[i] = Player(id,  password, phone , mydata,  coins,  myplane_health,  myplane_speed,  myplane_bulletinterval,
                                myplane_path,  has_screenclear,  has_laser,  has_missle,  has_shield,  revivetokens_num);
    }
    playerFile.close();
    playerFile.open(QIODevice::WriteOnly);
    for(int i=0;i<player_num;i++)
    {
        if (player->id == player_list[i].id)
        {
            txt << player_num << player->id << player->password << player->phone << player->mydata.score << player->mydata.coin << player->mydata.destorycommonenemy << player->mydata.destoryshootenemy << player->mydata.destoryspeedenemy << player->mydata.myplaneshoottime <<
                   player->mydata.crashtime << player->mydata.beshottime << player->mydata.destroyedbycommonenemy << player->mydata.destroyedbyshootenemy << player->mydata.destroyedbyspeedenemy << player->mydata.injury << player->mydata.cure <<
                   player->mydata.screencleartime << player->mydata.lasertime << player->mydata.missletime << player->mydata.shieldtime << player->mydata.screencleardestory << player->mydata.laserdestory << player->mydata.missledestory <<
                   player->mydata.shielddefense << player->mydata.damageboss << player->mydata.destroyedbyboss << player->mydata.destoryboss << player->coins << player->myplane_health << player->myplane_speed << player->myplane_bulletinterval <<
                   player->myplane_path << player->has_screenclear << player->has_laser << player->has_missle << player->has_shield << player->revivetokens_num;
        }
        else
        {
            txt << player_num << player_list[i].id << player_list[i].password << player_list[i].phone << player_list[i].mydata.score << player_list[i].mydata.coin << player_list[i].mydata.destorycommonenemy << player_list[i].mydata.destoryshootenemy << player_list[i].mydata.destoryspeedenemy << player_list[i].mydata.myplaneshoottime <<
                   player_list[i].mydata.crashtime << player_list[i].mydata.beshottime << player_list[i].mydata.destroyedbycommonenemy << player_list[i].mydata.destroyedbyshootenemy << player_list[i].mydata.destroyedbyspeedenemy << player_list[i].mydata.injury << player_list[i].mydata.cure <<
                   player_list[i].mydata.screencleartime << player_list[i].mydata.lasertime << player_list[i].mydata.missletime << player_list[i].mydata.shieldtime << player_list[i].mydata.screencleardestory << player_list[i].mydata.laserdestory << player_list[i].mydata.missledestory <<
                   player_list[i].mydata.shielddefense << player_list[i].mydata.damageboss << player_list[i].mydata.destroyedbyboss << player_list[i].mydata.destoryboss << player_list[i].coins << player_list[i].myplane_health << player_list[i].myplane_speed << player_list[i].myplane_bulletinterval <<
                   player_list[i].myplane_path << player_list[i].has_screenclear << player_list[i].has_laser << player_list[i].has_missle << player_list[i].has_shield << player_list[i].revivetokens_num;
        }
    }
    playerFile.close();

    this->close();
}

void MainScene::revive_plane()
{
    if (player->revivetokens_num > 0)
    {
        plane->isdeath = false;
        isgameover = false;
        player->revivetokens_num--;
        plane->health = player->myplane_health;
        plane->X = GAME_WIDTH / 2  - plane->Plane.width() / 2;
        plane->Y = GAME_HEIGHT - plane->Plane.height();
        plane->pressflag_w = false;
        plane->pressflag_a = false;
        plane->pressflag_s = false;
        plane->pressflag_d = false;
        plane->direction_w = 0;
        plane->direction_a = 0;
        plane->direction_s = 0;
        plane->direction_d = 0;
        plane->shootflag = false;

        screenclear.shoot();

        revive.close();
        returnhome.close();
    }
}

void MainScene::game_pause()
{
    if (ispause == false)
    {
        ispause = true;
    }
    else
    {
        ispause = false;
    }
}

