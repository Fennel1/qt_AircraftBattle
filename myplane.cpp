#include "myplane.h"
#include "config.h"

myPlane::myPlane() : Bomb()
{
    //初始化加载飞机图片资源
    m_Plane.load(MYPLANE_PATH);

    //初始化坐标
    m_X = GAME_WIDTH * 0.5 - m_Plane.width() * 0.5;
    m_Y = GAME_HEIGHT - m_Plane.height();

    //初始化矩形框
    m_Rect.setWidth(m_Plane.width());
    m_Rect.setHeight(m_Plane.height());
    m_Rect.moveTo(m_X,m_Y);

    //初始化发射间隔记录
    m_recorder = 0;
    m_shootflag = false;

    //飞机移动方向
    m_direction_w = 0;
    m_direction_s = 0;
    m_direction_a = 0;
    m_direction_d = 0;
    m_pressflag_w = false;
    m_pressflag_s = false;
    m_pressflag_a = false;
    m_pressflag_d = false;

    //飞机死亡
    isdeath = false;
}

void myPlane::setPosition(int x, int y)
{
    m_X = x;
    m_Y = y;
    m_Rect.moveTo(m_X, m_Y);
}

void myPlane::shoot()
{
    //累加时间间隔记录变量
    m_recorder++;
    //判断如果记录数字 未达到发射间隔，直接return
    if(m_recorder < BULLET_INTERVAL)
    {
       return;
    }
    //到达发射时间处理
    //重置发射时间间隔记录
    m_recorder = 0;

    //发射子弹
    for(int i = 0 ; i < BULLET_NUM;i++)
    {
        //如果是空闲的子弹进行发射
        if(m_bullets[i].m_Free)
        {
            //将改子弹空闲状态改为假
            m_bullets[i].m_Free = false;
            //设置发射的子弹坐标
            m_bullets[i].m_X = m_X + m_Rect.width()*0.5 - 10;
            m_bullets[i].m_Y = m_Y - 25 ;
            break;
        }
    }
//    for(int i=0; i<BULLET_NUM; i++)
//    {
//        if(m_bullets[i].m_Free)
//        {
//            m_bullets[i].m_Free = false;
//            m_bullets[i].m_X = m_X + m_Rect.width()/2;
//            m_bullets[i].m_Y = m_Y;
//            m_bullets[i].m_Rect.moveTo(m_bullets[i].m_X, m_bullets[i].m_Y);
//            break;
//        }
//    }
}
