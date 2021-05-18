#include "headers_window/loginwindow.h"

loginWindow::loginWindow(QWidget *parent) : QWidget(parent)
{
    resize(480,700);
    //返回按钮
    btn_back.setParent(this);
    btn_back.setText("返回");
    btn_back.resize(100,40);

    connect(&btn_back, &QPushButton::clicked, this, &loginWindow::sendslot_back);
    //确认登录按钮
    btn_confirm_login.setParent(this);
    btn_confirm_login.setText("确认登录");
    btn_confirm_login.resize(200,40);
    btn_confirm_login.move(150,450);

    connect(&btn_confirm_login, &QPushButton::clicked, this, &loginWindow::change_window_to_mainwindow);

    player = new Player();
    win_mainwindow = new MainWindow(*player);
    //处理子界面信号
    connect(&*win_mainwindow, &MainWindow::signal_back, this, &loginWindow::deal_slot_from_mainwindow);
}

void loginWindow::sendslot_back()
{
    emit signal_back();
}

void loginWindow::change_window_to_mainwindow()
{
    //文件设置
    QFile playerFile(PLAYERFILE_PATH);
    QDataStream txt(&playerFile);

    //要导入的数据
    Data d;
    Player p("kim", "123", d, 1, 10, 2, 10, "123", true, true, true, true, 2);
    //数据导入进文件
    playerFile.open(QIODevice::WriteOnly);
    txt << p.id << p.password << p.mydata.score << p.mydata.coin << p.mydata.destorycommonenemy << p.mydata.destoryshootenemy << p.mydata.destoryspeedenemy << p.mydata.myplaneshoottime <<
           p.mydata.crashtime << p.mydata.beshottime << p.mydata.destroyedbycommonenemy << p.mydata.destroyedbyshootenemy << p.mydata.destroyedbyspeedenemy << p.mydata.injury << p.mydata.cure <<
           p.mydata.screencleartime << p.mydata.lasertime << p.mydata.missletime << p.mydata.shieldtime << p.mydata.screencleardestory << p.mydata.laserdestory << p.mydata.missledestory <<
           p.mydata.shielddefense << p.mydata.damageboss << p.mydata.destroyedbyboss << p.mydata.destoryboss << p.coins << p.myplane_health << p.myplane_speed << p.myplane_bulletinterval <<
           p.myplane_path << p.has_screenclear << p.has_laser << p.has_missle << p.has_shield << p.revivetokens_num;
    playerFile.close();

    //导出数据
    QString id;         //账户
    QString password;   //密码
    int coins;  //金币
    //游戏参数
    int myplane_health;           //飞机生命值
    int myplane_speed;            //飞机速度
    int myplane_bulletinterval;   //飞机射速
    QString myplane_path;           //飞机皮肤
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

    //数据从文件导出
    playerFile.open(QFile::ReadOnly);
    txt.setDevice(&playerFile);
    txt >> id >> password >> score >> coin >> destorycommonenemy >> destoryshootenemy >> destoryspeedenemy >> myplaneshoottime >>
           crashtime >> beshottime >> destroyedbycommonenemy >> destroyedbyshootenemy >> destroyedbyspeedenemy >> injury >> cure >>
           screencleartime >> lasertime >> missletime >> shieldtime >> screencleardestory >> laserdestory >> missledestory >>
           shielddefense >> damageboss >> destroyedbyboss >> destoryboss >> coins >> myplane_health >> myplane_speed >> myplane_bulletinterval >>
          myplane_path >> has_screenclear >> has_laser >> has_missle >> has_shield >> revivetokens_num;
    playerFile.close();


    //数据从文件到程序
    Data mydata(score, coin,destorycommonenemy, destoryshootenemy,  destoryspeedenemy,  myplaneshoottime,
                 crashtime,  beshottime,  destroyedbycommonenemy,  destroyedbyshootenemy,  destroyedbyspeedenemy,
                 injury,  cure,  screencleartime,  lasertime,  missletime,  shieldtime,  screencleardestory,
                 laserdestory,  missledestory,  shielddefense,  damageboss,  destroyedbyboss,  destoryboss);
    player = new Player( id,  password,  mydata,  coins,  myplane_health,  myplane_speed,  myplane_bulletinterval,
                  myplane_path,  has_screenclear,  has_laser,  has_missle,  has_shield,  revivetokens_num);

    if (player->id == "kim" && player->password == "123")
    {
        win_mainwindow->show();
        this->hide();
    }
}

void loginWindow::deal_slot_from_mainwindow()
{
    win_mainwindow->hide();
    show();
}
