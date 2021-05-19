#include "headers_window/loginwindow.h"

loginWindow::loginWindow(QWidget *parent) : QWidget(parent)
{
    resize(480,700);

    //设置窗体标题
    this->setWindowTitle(tr("登录界面"));

    //用户名标签
    userNameLbl = new QLabel(this);
    userNameLbl->move(100,250);
    userNameLbl->setText("用户名:");

    //用户名输入框
    userNameLEd = new QLineEdit(this);
    userNameLEd->move(160,247);
    userNameLEd->setPlaceholderText(tr("请输入用户名"));

    //密码标签
    pwdLbl = new QLabel(this);
    pwdLbl->move(115,310);
    pwdLbl->setText("密码:");

    //密码输入框
    pwdLEd = new QLineEdit(this);
    pwdLEd->move(160,307);
    pwdLEd->setPlaceholderText("请输入密码");
    pwdLEd->setEchoMode(QLineEdit::Password);

    //返回按钮
    btn_back.setParent(this);
    btn_back.setText("返回");
    btn_back.resize(100,40);

    connect(&btn_back, &QPushButton::clicked, this, &loginWindow::sendslot_back);
    //确认登录按钮
    btn_confirm_login.setParent(this);
    btn_confirm_login.setText("确认登录");
    btn_confirm_login.resize(200,40);
    btn_confirm_login.move(150,380);
    connect(&btn_confirm_login, &QPushButton::clicked, this, &loginWindow::login);

    btnRegister.setParent(this);
    btnRegister.setText("注册账号");
    btnRegister.resize(200,40);
    btnRegister.move(150,430);
    connect(&btnRegister, &QPushButton::clicked, this, &loginWindow::change_window_to_regwindow);

    btnForger.setParent(this);
    btnForger.setText("忘记密码");
    btnForger.resize(200,40);
    btnForger.move(150,480);
    connect(&btnForger, &QPushButton::clicked, this, &loginWindow::change_window_to_forgetPWwindow);

    player = new Player;
    mainWindow = new MainWindow(player);
    connect(mainWindow, &MainWindow::signal_back, this, &loginWindow::deal_slot_from_mainwindow);
    connect(&regWindow, &RegWindow::signal_back, this, &loginWindow::deal_slot_from_regwindow);
    connect(&forgetWindow, &ForgetPW::signal_back, this, &loginWindow::deal_slot_from_forgetPWwindow);
}

void loginWindow::sendslot_back()
{
    emit signal_back();
}


void loginWindow::deal_slot_from_mainwindow()
{
    mainWindow->hide();
    show();
}

void loginWindow::login()
{
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
    QFile playerFile(PLAYERFILE_PATH);
    QDataStream txt(&playerFile);

    playerFile.open(QIODevice::ReadOnly);
    int player_num;
    txt >> player_num;
    playerFile.close();

    playerFile.open(QFile::ReadOnly);
    txt.setDevice(&playerFile);

    for(int i=0;i<player_num;i++){
        //数据从文件导出
        txt >> player_num >> id >> password >> phone >> score >> coin >> destorycommonenemy >> destoryshootenemy >> destoryspeedenemy >> myplaneshoottime >>
                crashtime >> beshottime >> destroyedbycommonenemy >> destroyedbyshootenemy >> destroyedbyspeedenemy >> injury >> cure >>
                screencleartime >> lasertime >> missletime >> shieldtime >> screencleardestory >> laserdestory >> missledestory >>
                shielddefense >> damageboss >> destroyedbyboss >> destoryboss >> coins >> myplane_health >> myplane_speed >> myplane_bulletinterval >>
                myplane_path >> has_screenclear >> has_laser >> has_missle >> has_shield >> revivetokens_num;
        qDebug() << player_num << id << password << has_laser << endl;
        if(userNameLEd->text().trimmed()==id&&pwdLEd->text().trimmed()==password){
            if (player != nullptr)
            {
                delete player;
            }
            Data mydata(score, coin,destorycommonenemy, destoryshootenemy,  destoryspeedenemy,  myplaneshoottime,
                        crashtime,  beshottime,  destroyedbycommonenemy,  destroyedbyshootenemy,  destroyedbyspeedenemy,
                        injury,  cure,  screencleartime,  lasertime,  missletime,  shieldtime,  screencleardestory,
                        laserdestory,  missledestory,  shielddefense,  damageboss,  destroyedbyboss,  destoryboss);
            player = new Player(id,  password, phone , mydata,  coins,  myplane_health,  myplane_speed,  myplane_bulletinterval,
                                myplane_path,  has_screenclear,  has_laser,  has_missle,  has_shield,  revivetokens_num);
            mainWindow->show();
            this->hide();
            playerFile.close();
            return;
        }
    }
    userNameLEd->clear();
    pwdLEd->clear();
    QMessageBox::warning(this, tr("失败！"),tr("用户名或密码错误！"),QMessageBox::Yes);
}

void loginWindow::change_window_to_regwindow()
{
    regWindow.show();
    this->hide();
}

void loginWindow::deal_slot_from_regwindow()
{
    regWindow.hide();
    show();
}

void loginWindow::change_window_to_forgetPWwindow()
{
    forgetWindow.show();
    this->hide();
}

void loginWindow::deal_slot_from_forgetPWwindow()
{
    forgetWindow.hide();
    show();
}
