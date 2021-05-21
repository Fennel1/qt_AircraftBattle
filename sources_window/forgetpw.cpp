#include "headers_window/forgetpw.h"

ForgetPW::ForgetPW(QWidget *parent) : QWidget(parent)
{
    resize(480,700);

    //设置窗体标题
    this->setWindowTitle(tr("找回密码"));

    //用户名标签
    userNameLbl = new QLabel(this);
    userNameLbl->move(100,250);
    userNameLbl->setText("用户名:");

    //用户名输入框
    userNameLEd = new QLineEdit(this);
    userNameLEd->move(160,247);
    userNameLEd->setPlaceholderText(tr("请输入用户名"));

    //电话标签
    phoneLbl = new QLabel(this);
    phoneLbl->move(115,310);
    phoneLbl->setText("电话:");

    //电话输入框
    phoneLEd = new QLineEdit(this);
    phoneLEd->move(160,307);
    QRegExp regExp("[0-9][0-9][0-9][0-9][0-9][0-9][0-9][0-9][0-9][0-9][0-9]");
    phoneLEd->setValidator(new QRegExpValidator(regExp,this));
    phoneLEd->setPlaceholderText("请输入电话");

    pwdLbl = new QLabel(this);
    pwdLbl->move(100,370);
    pwdLbl->setText("新密码：");

    pwdLEd = new QLineEdit(this);
    pwdLEd->move(160,367);
    pwdLEd->setPlaceholderText(tr("请输入新密码"));
    pwdLEd->setEchoMode(QLineEdit::Password);

    //密码标签
    btnConfirmPW = new QLabel(this);
    btnConfirmPW->move(85,430);
    btnConfirmPW->setText("确认密码:");

    //密码输入框
    ConfirmLEd = new QLineEdit(this);
    ConfirmLEd->move(160,427);
    ConfirmLEd->setPlaceholderText("请再次输入密码");
    ConfirmLEd->setEchoMode(QLineEdit::Password);


    btnConfirm.setParent(this);
    btnConfirm.setText("找回密码");
    btnConfirm.resize(200,40);
    btnConfirm.move(150,500);
    connect(&btnConfirm, &QPushButton::clicked, this, &ForgetPW::changePW);


    //返回按钮
    btn_back.setParent(this);
    btn_back.setText("返回");
    btn_back.resize(100,40);
    connect(&btn_back, &QPushButton::clicked, this, &ForgetPW::sendslot_back);


}
void ForgetPW::sendslot_back()
{
    emit signal_back();
}

void ForgetPW::changePW()
{
    //文件设置
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

    bool flag = false;
    playerFile.open(QFile::ReadOnly);
    txt.setDevice(&playerFile);
    for(int i=0;i<player_num;i++){
        //数据从文件导出
        txt >> player_num >>id >> password  >> phone >> score >> coin >> destorycommonenemy >> destoryshootenemy >> destoryspeedenemy >> myplaneshoottime >>
                crashtime >> beshottime >> destroyedbycommonenemy >> destroyedbyshootenemy >> destroyedbyspeedenemy >> injury >> cure >>
                screencleartime >> lasertime >> missletime >> shieldtime >> screencleardestory >> laserdestory >> missledestory >>
                shielddefense >> damageboss >> destroyedbyboss >> destoryboss >> coins >> myplane_health >> myplane_speed >> myplane_bulletinterval >>
                myplane_path >> has_screenclear >> has_laser >> has_missle >> has_shield >> revivetokens_num;

        if(id==userNameLEd->text().trimmed() && phone==phoneLEd->text().trimmed())
        {
            if(pwdLEd->text().trimmed()==ConfirmLEd->text().trimmed()){
                password=ConfirmLEd->text().trimmed();
                flag=true;
                qDebug() << 1 << endl;
            }
            else {
                userNameLEd->clear();
                pwdLEd->clear();
                ConfirmLEd->clear();
                QMessageBox::warning(this, tr("警告！"),tr("两次密码不一致！"),QMessageBox::Yes);
                return;
            }
        }

        Data mydata(score, coin,destorycommonenemy, destoryshootenemy,  destoryspeedenemy,  myplaneshoottime,
                    crashtime,  beshottime,  destroyedbycommonenemy,  destroyedbyshootenemy,  destroyedbyspeedenemy,
                    injury,  cure,  screencleartime,  lasertime,  missletime,  shieldtime,  screencleardestory,
                    laserdestory,  missledestory,  shielddefense,  damageboss,  destroyedbyboss,  destoryboss);
        player_list[i] = Player(id,  password, phone , mydata,  coins,  myplane_health,  myplane_speed,  myplane_bulletinterval,
                                myplane_path,  has_screenclear,  has_laser,  has_missle,  has_shield,  revivetokens_num);
    }
    playerFile.close();
    if(flag)
    {
        playerFile.open(QIODevice::WriteOnly);
        txt.setDevice(&playerFile);
        for(int i=0;i<player_num;i++){
            //数据导入进文件

            txt << player_num << player_list[i].id << player_list[i].password  << player_list[i].phone<< player_list[i].mydata.score << player_list[i].mydata.coin << player_list[i].mydata.destorycommonenemy << player_list[i].mydata.destoryshootenemy << player_list[i].mydata.destoryspeedenemy << player_list[i].mydata.myplaneshoottime <<
                   player_list[i].mydata.crashtime << player_list[i].mydata.beshottime << player_list[i].mydata.destroyedbycommonenemy << player_list[i].mydata.destroyedbyshootenemy << player_list[i].mydata.destroyedbyspeedenemy << player_list[i].mydata.injury << player_list[i].mydata.cure <<
                   player_list[i].mydata.screencleartime << player_list[i].mydata.lasertime << player_list[i].mydata.missletime << player_list[i].mydata.shieldtime << player_list[i].mydata.screencleardestory << player_list[i].mydata.laserdestory << player_list[i].mydata.missledestory <<
                   player_list[i].mydata.shielddefense << player_list[i].mydata.damageboss << player_list[i].mydata.destroyedbyboss << player_list[i].mydata.destoryboss << player_list[i].coins << player_list[i].myplane_health << player_list[i].myplane_speed << player_list[i].myplane_bulletinterval <<
                   player_list[i].myplane_path << player_list[i].has_screenclear << player_list[i].has_laser << player_list[i].has_missle << player_list[i].has_shield << player_list[i].revivetokens_num;
        }
        playerFile.close();
        QMessageBox::warning(this, tr("成功！"),tr("密码已修改！"),QMessageBox::Yes);
        sendslot_back();
        return;
    }

    QMessageBox::warning(this, tr("警告！"),tr("用户名或电话错误！"),QMessageBox::Yes);
    userNameLEd->clear();
    pwdLEd->clear();
    ConfirmLEd->clear();
    phoneLEd->clear();
}
