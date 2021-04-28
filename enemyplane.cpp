#include "enemyplane.h"
#include "config.h"

EnemyPlane::EnemyPlane() : Bomb()
{
    //敌机资源加载
    m_enemy.load(ENEMY_PATH);

    //敌机位置
    m_X = 0;
    m_Y = 0;

    //敌机状态
    m_Free = true;

    //敌机速度
    m_Speed = ENEMY_SPEED;

    //敌机矩形
    m_Rect.setWidth(m_enemy.width());
    m_Rect.setHeight(m_enemy.height());
    m_Rect.moveTo(m_X,m_Y);

    //初始化发射间隔记录
    m_recorder = 0;

}

void EnemyPlane::updatePosition()
{
    //空闲状态，不计算坐标
    if(m_Free)
    {
        return;
    }

    m_X += m_Speed;
    m_Y += 2;

    if(m_X < 0)
    {
        m_Speed = ENEMY_SPEED;
    }
    else if(m_X > GAME_WIDTH-m_Rect.width())
    {
        m_Speed = -ENEMY_SPEED;
    }
    m_Rect.moveTo(m_X, m_Y);

    if(m_Y >= GAME_HEIGHT + m_Rect.height())
    {
        m_Free = true;
    }
}

void EnemyPlane::death()
{
    m_Free = true;
}

void EnemyPlane::shoot()
{
    //累加时间间隔记录变量
    m_recorder++;
    //判断如果记录数字 未达到发射间隔，直接return
    if(m_recorder < ENEMY_BULLETINTERVAL)
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
            m_bullets[i].m_X = m_X + m_Rect.width()*0.5;
            m_bullets[i].m_Y = m_Y ;
            break;
        }
     }
}
