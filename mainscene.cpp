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
}

MainScene::~MainScene()
{
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
    m_Timer.setInterval(GAME_RATE);
    //启动游戏
    playGame();

    m_recorder = 0;
}

void MainScene::playGame()
{
    //启动定时器
    m_Timer.start();

    //监听定时器
    connect(&m_Timer,&QTimer::timeout,[=](){
        //主机移动
        if (m_plane.m_X >= 0 && m_plane.m_X <= GAME_WIDTH - m_plane.m_Rect.width())
        {
            m_plane.m_X += (m_plane.m_direction_a + m_plane.m_direction_d) * MYPLANE_SPEED;
        }
        if (m_plane.m_Y >= 0 && m_plane.m_Y <= (GAME_HEIGHT - m_plane.m_Rect.height()))
        {
            m_plane.m_Y += (m_plane.m_direction_w + m_plane.m_direction_s) * MYPLANE_SPEED;
        }
        //边界检测
        if(m_plane.m_X <= 0 )
        {
            m_plane.m_X = 0;
        }
        else if(m_plane.m_X >= GAME_WIDTH - m_plane.m_Rect.width())
        {
            m_plane.m_X = GAME_WIDTH - m_plane.m_Rect.width();
        }
        if(m_plane.m_Y <= 0)
        {
            m_plane.m_Y = 0;
        }
        else if(m_plane.m_Y >= GAME_HEIGHT - m_plane.m_Rect.height())
        {
            m_plane.m_Y = GAME_HEIGHT - m_plane.m_Rect.height();
        }
        m_plane.m_Rect.moveTo(m_plane.m_X, m_plane.m_Y);
        //敌机出场
        enemyToScene();
        //更新游戏元素坐标
        updatePosition();
        //重新绘制图片
        update();
    });
}

void MainScene::updatePosition()
{
    //更新地图坐标
    m_map.mapPosition();

    //计算子弹坐标
    for(int i = 0 ;i < BULLET_NUM;i++)
    {
        //如果子弹状态为非空闲，计算发射位置
        if(!m_plane.m_bullets[i].m_Free)
        {
            m_plane.m_bullets[i].updatePosition();
        }
    }

    //敌机坐标计算
    for(int i = 0 ; i< ENEMY_NUM;i++)
    {
        //非空闲敌机 更新坐标
        if(m_enemys[i].m_Free == false)
        {
           m_enemys[i].updatePosition();
        }
    }
}

void MainScene::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    //绘制地图
    painter.drawPixmap(0,m_map.m_map1_posY , m_map.m_map1);
    painter.drawPixmap(0,m_map.m_map2_posY , m_map.m_map2);

    //绘制主机
    painter.drawPixmap(m_plane.m_X, m_plane.m_Y, m_plane.m_Plane);

    //绘制子弹
    for(int i = 0 ;i < BULLET_NUM;i++)
    {
        //如果子弹状态为非空闲，计算发射位置
        if(!m_plane.m_bullets[i].m_Free)
        {
            painter.drawPixmap(m_plane.m_bullets[i].m_X,m_plane.m_bullets[i].m_Y,m_plane.m_bullets[i].m_Bullet);
        }
    }

    //绘制敌机
    for(int i = 0 ; i< ENEMY_NUM;i++)
    {
        if(m_enemys[i].m_Free == false)
        {
            painter.drawPixmap(m_enemys[i].m_X,m_enemys[i].m_Y,m_enemys[i].m_enemy);
        }
    }
}

void MainScene::mouseMoveEvent(QMouseEvent *event)
{
    int x = event->x() - m_plane.m_Rect.width()/2; //鼠标位置 - 飞机矩形的一半
    int y = event->y() - m_plane.m_Rect.height()/2;

    //边界检测
    if(x <= 0 )
    {
        x = 0;
    }
    if(x >= GAME_WIDTH - m_plane.m_Rect.width())
    {
        x = GAME_WIDTH - m_plane.m_Rect.width();
    }
    if(y <= 0)
    {
        y = 0;
    }
    if(y >= GAME_HEIGHT - m_plane.m_Rect.height())
    {
        y = GAME_HEIGHT - m_plane.m_Rect.height();
    }
    m_plane.setPosition(x,y);
}

void MainScene::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_J)
    {
        m_plane.shoot();
    }

    if((event->key() == Qt::Key_W) && !event->isAutoRepeat())   //上
    {
        if(!m_plane.m_pressflag_w)
        {
            m_plane.m_direction_w = -1;
        }
        m_plane.m_pressflag_w = true;
    }
    if((event->key() == Qt::Key_S) && !event->isAutoRepeat())  //下
    {
        if(!m_plane.m_pressflag_s)
        {
           m_plane.m_direction_s = 1;
        }
        m_plane.m_pressflag_s = true;
    }
    if((event->key() == Qt::Key_A) && !event->isAutoRepeat())  //左
    {
        if(!m_plane.m_pressflag_a)
        {
            m_plane.m_direction_a = -1;
        }
        m_plane.m_pressflag_a = true;
    }
    if((event->key() == Qt::Key_D) && !event->isAutoRepeat())  //右
    {
        if(!m_plane.m_pressflag_d)
        {
            m_plane.m_direction_d = 1;
        }
        m_plane.m_pressflag_d = true;
    }

}

void MainScene::keyReleaseEvent(QKeyEvent *event)
{
    if((event->key() == Qt::Key_W)&& m_plane.m_direction_w == -1 && !event->isAutoRepeat())     //上
    {
        if(m_plane.m_pressflag_w)
        {
            m_plane.m_direction_w = 0;
        }
        m_plane.m_pressflag_w = false;
    }
    if((event->key() == Qt::Key_S)&& m_plane.m_direction_s == 1 && !event->isAutoRepeat())     //下
    {
        if(m_plane.m_pressflag_s)
        {
            m_plane.m_direction_s = 0;
        }
        m_plane.m_pressflag_s = false;
    }
    if((event->key() == Qt::Key_A)&& m_plane.m_direction_a == -1 && !event->isAutoRepeat())     //左
    {
        if(m_plane.m_pressflag_a)
        {
            m_plane.m_direction_a = 0;
        }
        m_plane.m_pressflag_a = false;
    }
    if((event->key() == Qt::Key_D)&& m_plane.m_direction_d == 1 && !event->isAutoRepeat())     //右
    {
        if(m_plane.m_pressflag_d)
        {
            m_plane.m_direction_d = 0;
        }
        m_plane.m_pressflag_d = false;
    }
}

void MainScene::enemyToScene()
{
    m_recorder++;
    if(m_recorder < ENEMY_INTERVAL)
    {
        return;
    }

    m_recorder = 0;

    for(int i = 0 ; i< ENEMY_NUM;i++)
    {
        if(m_enemys[i].m_Free)
        {
            //敌机空闲状态改为false
            m_enemys[i].m_Free = false;
            //设置坐标
            m_enemys[i].m_X = rand() % (GAME_WIDTH - m_enemys[i].m_Rect.width());
            m_enemys[i].m_Y = -m_enemys[i].m_Rect.height();
            break;
        }
    }
}












