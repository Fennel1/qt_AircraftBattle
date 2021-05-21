#include "headers_window/mainwindow.h"
#include "ui_mainwindow.h"
#include "headers_game/config.h"

#include <QPainter>
#include <QProxyStyle>
#include <QTabBar>
#include <QStyleOptionTab>
#include <QTabWidget>
#include <QTimer>

class CustomTabStyle : public QProxyStyle
{
public:
    QSize sizeFromContents(ContentsType type, const QStyleOption *option,
        const QSize &size, const QWidget *widget) const
    {
        QSize s = QProxyStyle::sizeFromContents(type, option, size, widget);
        if (type == QStyle::CT_TabBarTab) {
            s.transpose();
            s.rwidth() = 100; // 设置每个tabBar中item的大小
            s.rheight() = 50;
        }
        return s;
    }

    void drawControl(ControlElement element, const QStyleOption *option, QPainter *painter, const QWidget *widget) const
    {
        if (element == CE_TabBarTabLabel) {
            if (const QStyleOptionTab *tab = qstyleoption_cast<const QStyleOptionTab *>(option)) {
                QRect allRect = tab->rect;

                if (tab->state & QStyle::State_Selected) {
                    painter->save();
                    painter->setPen(0x89cfff);
                    painter->setBrush(QBrush(0x89cfff));
                    painter->drawRect(allRect.adjusted(6, 6, -6, -6));
                    painter->restore();
                }
                QTextOption option;
                option.setAlignment(Qt::AlignCenter);
                if (tab->state & QStyle::State_Selected) {
                    painter->setPen(0xf8fcff);
                }
                else {
                    painter->setPen(0x5d5d5d);
                }

                painter->drawText(allRect, tab->text, option);
                return;
            }
        }

        if (element == CE_TabBarTab) {
            QProxyStyle::drawControl(element, option, painter, widget);
        }
    }
};

MainWindow::MainWindow(Player *p, QWidget *parent) :
    ui(new Ui::MainWindow), QMainWindow(parent)
{    
    //初始化用户
    player = p;

    ui->setupUi(this);
    ui->tabWidget->setTabPosition(QTabWidget::West);
    ui->tabWidget->tabBar()->setStyle(new CustomTabStyle);

    //窗口标题
    setWindowTitle(GAME_TITLE);
    //窗口图标
    setWindowIcon(QIcon(GAME_ICON));
    //窗口大小
    resize(1050,750);
    //按钮
    btn_back.setParent(this);
    btn_back.setText(QStringLiteral("切换账号"));
    btn_back.move(0,600);
    btn_back.resize(100,40);

    common_sort();
    endless_sort();

    connect(&btn_back, &QPushButton::clicked, this, &MainWindow::sendslot_back);

    //将矩形初始为不显示
    is_reborn = false;
    is_missle = false;
    is_laser = false;
    is_shield = false;
    is_screenclear = false;
    is_health = false;
    is_speed = false;
    is_bulletinterval = false;
    //商店中交互后弹窗的设置
    rect_ok_and_cancel.setRect(100,150,400,500);
    btn_ok.setParent(this);
    btn_ok.setText(QStringLiteral("确定"));
    btn_ok.move(400, 630);
    btn_ok.resize(100, 50);
    btn_ok.hide();
    btn_cancel.setParent(this);
    btn_cancel.setText(QStringLiteral("取消"));
    btn_cancel.move(550, 630);
    btn_cancel.resize(100, 50);
    btn_cancel.hide();
    QValidator *vali_integer = new QIntValidator(1,99,this);
    input_number_of_reborn.setParent(this);
    input_number_of_reborn.setValidator(vali_integer);
    input_number_of_reborn.resize(300,50);
    input_number_of_reborn.move(370,530);
    input_number_of_reborn.setPlaceholderText(QStringLiteral("请输入购买数量(1~99)"));
    input_number_of_reborn.setFont(QFont("consolas",12));
    input_number_of_reborn.hide();

    //花费金币的设置
    cost_of_reborn = 50;
    cost_of_missle = 100;
    cost_of_laser = 300;
    cost_of_shield = 1000;
    cost_of_screenclear = 500;
    cost_of_health = 100;
    cost_of_speed = 200;
    cost_of_bulletinterval = 300;

    //ui中控件的设置
    QTimer *timer_value_of_coins = new QTimer;
    timer_value_of_coins->start();
    connect(timer_value_of_coins, &QTimer::timeout, [=](){
        ui->label_value_of_coins->setText(QStringLiteral("金币数: ")+QString::number(player->coins));
    });

    QTimer * timer_btn_missle = new QTimer;
    timer_btn_missle->start();
    connect(timer_btn_missle,&QTimer::timeout,[=](){
        if(player->has_missle)
        {
            ui->btn_skill_missle->setEnabled(false);
            ui->btn_skill_missle->setText(QStringLiteral("导弹(已拥有)"));
        }
    });

    QTimer * timer_btn_laser = new QTimer;
    timer_btn_laser->start();
    connect(timer_btn_laser,&QTimer::timeout,[=](){
        if(player->has_laser)
        {
            ui->btn_skill_laser->setEnabled(false);
            ui->btn_skill_laser->setText(QStringLiteral("激光(已拥有)"));
        }
    });

    QTimer * timer_btn_shield = new QTimer;
    timer_btn_shield->start();
    connect(timer_btn_shield,&QTimer::timeout,[=](){
        if(player->has_shield)
        {
            ui->btn_skill_shield->setEnabled(false);
            ui->btn_skill_shield->setText(QStringLiteral("护盾(已拥有)"));
        }
    });

    QTimer * timer_btn_screenclear = new QTimer;
    timer_btn_screenclear->start();
    connect(timer_btn_screenclear,&QTimer::timeout,[=](){
        if(player->has_screenclear)
        {
            ui->btn_skill_screenclear->setEnabled(false);
            ui->btn_skill_screenclear->setText(QStringLiteral("清屏(已拥有)"));
        }
    });

    QTimer * timer_btn_health = new QTimer;
    timer_btn_health->start();
    connect(timer_btn_health,&QTimer::timeout,[=](){
        ui->btn_health->setText("生命值(当前为:"+QString::number(player->myplane_health)+")");
        if(player->myplane_health >= 10)
        {
            ui->btn_health->setEnabled(false);
        }
    });

    QTimer * timer_btn_speed = new QTimer;
    timer_btn_speed->start();
    connect(timer_btn_speed,&QTimer::timeout,[=](){
        ui->btn_speed->setText("速度(当前为:"+QString::number(player->myplane_speed)+")");
        if(player->myplane_speed >= 8)
        {
            ui->btn_speed->setEnabled(false);
        }
    });

    QTimer * timer_btn_bulletinterval = new QTimer;
    timer_btn_bulletinterval->start();
    connect(timer_btn_bulletinterval,&QTimer::timeout,[=](){
        int level = 0;
        if(player->myplane_bulletinterval == 20) level = 1;
        else if(player->myplane_bulletinterval == 18) level = 2;
        else if(player->myplane_bulletinterval == 16) level = 3;
        else if(player->myplane_bulletinterval == 14) level = 4;
        ui->btn_bulletinterval->setText("射速(当前为:lv."+QString::number(level)+")");
//        qDebug() << player->myplane_bulletinterval << endl;
        if(player->myplane_bulletinterval <= 14)
        {
            ui->btn_bulletinterval->setEnabled(false);
        }
    });

    //仓库中的文字显示

    QTimer * timer_has_coins = new QTimer;
    timer_has_coins->start();
    connect(timer_has_coins, &QTimer::timeout, [=](){
        ui->label_has_coins->setText(QStringLiteral("金币数: ")+QString::number(player->coins));
    });

    QTimer * timer_has_reborn_coin = new QTimer;
    timer_has_reborn_coin->start();
    connect(timer_has_reborn_coin, &QTimer::timeout, [=](){
        ui->label_has_reborn_coin->setText(QStringLiteral("复活币数量: ")+QString::number(player->revivetokens_num));
    });

    QTimer * timer_has_missle = new QTimer;
    timer_has_missle->start();
    connect(timer_has_missle, &QTimer::timeout, [=](){
        if(player->has_missle)
        {
            ui->label_has_missle->show();
            ui->label_has_missle_no->hide();
        }
        else
        {
            ui->label_has_missle->hide();
            ui->label_has_missle_no->show();
        }
    });

    QTimer * timer_has_laser = new QTimer;
    timer_has_laser->start();
    connect(timer_has_laser, &QTimer::timeout, [=](){
        if(player->has_laser)
        {
            ui->label_has_laser->show();
            ui->label_has_laser_no->hide();
        }
        else
        {
            ui->label_has_laser->hide();
            ui->label_has_laser_no->show();
        }
    });

    QTimer * timer_has_shield = new QTimer;
    timer_has_shield->start();
    connect(timer_has_shield, &QTimer::timeout, [=](){
        if(player->has_shield)
        {
            ui->label_has_shield->show();
            ui->label_has_shield_no->hide();
        }
        else
        {
            ui->label_has_shield->hide();
            ui->label_has_shield_no->show();
        }
    });

    QTimer * timer_has_screenclear = new QTimer;
    timer_has_screenclear->start();
    connect(timer_has_screenclear, &QTimer::timeout, [=](){
        if(player->has_screenclear)
        {
            ui->label_has_screenclear->show();
            ui->label_has_screenclear_no->hide();
        }
        else
        {
            ui->label_has_screenclear->hide();
            ui->label_has_screenclear_no->show();
        }
    });

    QTimer * timer = new QTimer;
    timer->start();
    connect(timer,&QTimer::timeout,[=](){
        update();
    });

    //按钮的信号和槽连接
    connect(ui->btn_skill_missle,&QPushButton::clicked,this,&MainWindow::show_missle_rect);
    connect(ui->btn_skill_laser,&QPushButton::clicked,this,&MainWindow::show_laser_rect);
    connect(ui->btn_skill_shield,&QPushButton::clicked,this,&MainWindow::show_shield_rect);
    connect(ui->btn_skill_screenclear,&QPushButton::clicked,this,&MainWindow::show_screenclear_rect);
    connect(ui->btn_reborn_coin,&QPushButton::clicked,this,&MainWindow::show_reborn_rect);
    connect(&btn_ok,&QPushButton::clicked,this,&MainWindow::click_ok_button);
    connect(&btn_cancel,&QPushButton::clicked,this,&MainWindow::click_cancel_button);
    connect(ui->btn_health,&QPushButton::clicked,this,&MainWindow::buy_health);
    connect(ui->btn_speed,&QPushButton::clicked,this,&MainWindow::buy_speed);
    connect(ui->btn_bulletinterval,&QPushButton::clicked,this,&MainWindow::buy_bulletinterval);

    //生涯的显示设置
    QTimer * timer_data = new QTimer;
    timer_data->start();
    connect(timer_data,&QTimer::timeout,[=](){
        ui->label_score->setText("生涯得分: "+QString::number(player->mydata.score));
        ui->label_destorycommonenemy->setText("普通敌机: "+QString::number(player->mydata.destorycommonenemy));
        ui->label_destoryshootenemy->setText("射击型: "+QString::number(player->mydata.destoryshootenemy));
        ui->label_destoryspeedenemy->setText("撞击型: "+QString::number(player->mydata.destoryspeedenemy));
        ui->label_myplaneshoottime->setText("发射子弹数: "+QString::number(player->mydata.myplaneshoottime));
        ui->label_crashtime->setText("被碰撞次数: "+QString::number(player->mydata.crashtime));
        ui->label_beshottime->setText("被击中次数: "+QString::number(player->mydata.beshottime));
        ui->label_destoryedbycommonenemy->setText("普通敌机: "+QString::number(player->mydata.destroyedbycommonenemy));
        ui->label_destroyedbyshootenemy->setText("射击型: "+QString::number(player->mydata.destroyedbyshootenemy));
        ui->label_destroyedbyspeedenemy->setText("撞击型: "+QString::number(player->mydata.destroyedbyspeedenemy));
        ui->label_injury->setText("总受到伤害: "+QString::number(player->mydata.injury));
        ui->label_cure->setText("总回复血量: "+QString::number(player->mydata.cure));
        ui->label_screencleartime->setText("清屏: "+QString::number(player->mydata.screencleartime));
        ui->label_lasertime->setText("激光: "+QString::number(player->mydata.lasertime));
        ui->label_missletime->setText("导弹: "+QString::number(player->mydata.missletime));
        ui->label_shieldtime->setText("护盾: "+QString::number(player->mydata.shieldtime));
        ui->label_damageboss->setText("造成伤害: "+QString::number(player->mydata.damageboss));
        ui->label_destoryboss->setText("击毁次数: "+QString::number(player->mydata.destoryboss));
        ui->label_destroyedbyboss->setText("被击毁次数: "+QString::number(player->mydata.destroyedbyboss));

    });

    //设置排行榜
    QTimer * timer_record = new QTimer;
    timer_record->start();
    connect(timer_record,&QTimer::timeout,this,[=](){
        ui->label_common_0->setText("1st:  得分:"+QString::number(common_record[0].score)+"   金币:"+QString::number(common_record[0].coins)+"   玩家:"+QString(common_record[0].player_name));
        ui->label_common_1->setText("2nd:  得分:"+QString::number(common_record[1].score)+"   金币:"+QString::number(common_record[1].coins)+"   玩家:"+QString(common_record[1].player_name));
        ui->label_common_2->setText("3rd:  得分:"+QString::number(common_record[2].score)+"   金币:"+QString::number(common_record[2].coins)+"   玩家:"+QString(common_record[2].player_name));
        ui->label_common_3->setText("4th:  得分:"+QString::number(common_record[3].score)+"   金币:"+QString::number(common_record[3].coins)+"   玩家:"+QString(common_record[3].player_name));
        ui->label_common_4->setText("5th:  得分:"+QString::number(common_record[4].score)+"   金币:"+QString::number(common_record[4].coins)+"   玩家:"+QString(common_record[4].player_name));
        ui->label_common_5->setText("6th:  得分:"+QString::number(common_record[5].score)+"   金币:"+QString::number(common_record[5].coins)+"   玩家:"+QString(common_record[5].player_name));
        ui->label_common_6->setText("7th:  得分:"+QString::number(common_record[6].score)+"   金币:"+QString::number(common_record[6].coins)+"   玩家:"+QString(common_record[6].player_name));
        ui->label_common_7->setText("8th:  得分:"+QString::number(common_record[7].score)+"   金币:"+QString::number(common_record[7].coins)+"   玩家:"+QString(common_record[7].player_name));
        ui->label_common_8->setText("9th:  得分:"+QString::number(common_record[8].score)+"   金币:"+QString::number(common_record[8].coins)+"   玩家:"+QString(common_record[8].player_name));
        ui->label_common_9->setText("10th: 得分:"+QString::number(common_record[9].score)+"   金币:"+QString::number(common_record[9].coins)+"   玩家:"+QString(common_record[9].player_name));
        ui->label_endless_0->setText("1st:  得分:"+QString::number(endless_record[0].score)+"   金币:"+QString::number(endless_record[0].coins)+"   玩家:"+QString(endless_record[0].player_name));
        ui->label_endless_1->setText("2nd:  得分:"+QString::number(endless_record[1].score)+"   金币:"+QString::number(endless_record[1].coins)+"   玩家:"+QString(endless_record[1].player_name));
        ui->label_endless_2->setText("3rd:  得分:"+QString::number(endless_record[2].score)+"   金币:"+QString::number(endless_record[2].coins)+"   玩家:"+QString(endless_record[2].player_name));
        ui->label_endless_3->setText("4th:  得分:"+QString::number(endless_record[3].score)+"   金币:"+QString::number(endless_record[3].coins)+"   玩家:"+QString(endless_record[3].player_name));
        ui->label_endless_4->setText("5th:  得分:"+QString::number(endless_record[4].score)+"   金币:"+QString::number(endless_record[4].coins)+"   玩家:"+QString(endless_record[4].player_name));
        ui->label_endless_5->setText("6th:  得分:"+QString::number(endless_record[5].score)+"   金币:"+QString::number(endless_record[5].coins)+"   玩家:"+QString(endless_record[5].player_name));
        ui->label_endless_6->setText("7th:  得分:"+QString::number(endless_record[6].score)+"   金币:"+QString::number(endless_record[6].coins)+"   玩家:"+QString(endless_record[6].player_name));
        ui->label_endless_7->setText("8th:  得分:"+QString::number(endless_record[7].score)+"   金币:"+QString::number(endless_record[7].coins)+"   玩家:"+QString(endless_record[7].player_name));
        ui->label_endless_8->setText("9th:  得分:"+QString::number(endless_record[8].score)+"   金币:"+QString::number(endless_record[8].coins)+"   玩家:"+QString(endless_record[8].player_name));
        ui->label_endless_9->setText("10th: 得分:"+QString::number(endless_record[9].score)+"   金币:"+QString::number(endless_record[9].coins)+"   玩家:"+QString(endless_record[9].player_name));

    });



#if 0
    ui->tabWidget->setStyleSheet("QTabWidget::pane{ \
            border-left: 1px solid #eeeeee;\
        }");
#endif
}

void MainWindow::sendslot_back()
{
    emit signal_back();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    if(is_laser == true||is_missle == true||is_reborn == true||is_screenclear == true||is_shield == true||is_health == true||is_speed == true||is_bulletinterval == true)
    {
//        painter.begin(this);


        btn_ok.show();
        btn_cancel.show();
        if(is_reborn == true)
        {
            input_number_of_reborn.show();
        }
        else
        {
            input_number_of_reborn.hide();
        }

    }
    else
    {
        btn_ok.hide();
        btn_cancel.hide();
        input_number_of_reborn.hide();
    }
}

void MainWindow::on_btn_to_mainscene_clicked()
{
    //设置难度
    int difficulty = -1;
    if(ui->comboBox_choose_level->currentText() == "easy")
    {
        difficulty = 0;
    }
    else if(ui->comboBox_choose_level->currentText() == "normal")
    {
        difficulty = 1;
    }
    else if(ui->comboBox_choose_level->currentText() == "hard")
    {
        difficulty = 2;
    }
    else if(ui->comboBox_choose_level->currentText() == "lunatic")
    {
        difficulty = 3;
    }
    int model = -1;
    if(ui->comboBox_choose_model->currentText() == "普通模式")
    {
        model = 0;
    }
    else if(ui->comboBox_choose_model->currentText() == "无尽模式")
    {
        model = 1;
    }
    //设置模式
    MainScene* win_mainscene = new MainScene(difficulty, model, player, common_record, endless_record);
    win_mainscene->setWindowModality(Qt::ApplicationModal);
    win_mainscene->show();
}

void MainWindow::show_reborn_rect()
{
    is_missle = false;
    is_laser = false;
    is_shield = false;
    is_screenclear = false;
    is_reborn = true;
    is_health = false;
    is_speed = false;
    is_bulletinterval = false;
}

void MainWindow::show_missle_rect()
{
    is_reborn = false;
    is_laser = false;
    is_shield = false;
    is_screenclear = false;
    is_missle = true;
    is_health = false;
    is_speed = false;
    is_bulletinterval = false;
}

void MainWindow::show_laser_rect()
{
    is_reborn = false;
    is_missle = false;
    is_shield = false;
    is_screenclear = false;
    is_laser = true;
    is_health = false;
    is_speed = false;
    is_bulletinterval = false;
}


void MainWindow::show_shield_rect()
{
    is_reborn = false;
    is_missle = false;
    is_laser = false;
    is_screenclear = false;
    is_shield = true;
    is_health = false;
    is_speed = false;
    is_bulletinterval = false;
}


void MainWindow::show_screenclear_rect()
{
    is_reborn = false;
    is_missle = false;
    is_laser = false;
    is_shield = false;
    is_screenclear = true;
    is_health = false;
    is_speed = false;
    is_bulletinterval = false;
}

void MainWindow::buy_health()
{
    is_reborn = false;
    is_missle = false;
    is_laser = false;
    is_shield = false;
    is_screenclear = false;
    is_health = true;
    is_speed = false;
    is_bulletinterval = false;
}

void MainWindow::buy_speed()
{
    is_reborn = false;
    is_missle = false;
    is_laser = false;
    is_shield = false;
    is_screenclear = false;
    is_health = false;
    is_speed = true;
    is_bulletinterval = false;
}

void MainWindow::buy_bulletinterval()
{
    is_reborn = false;
    is_missle = false;
    is_laser = false;
    is_shield = false;
    is_screenclear = false;
    is_health = false;
    is_speed = false;
    is_bulletinterval = true;
}

void MainWindow::click_ok_button()
{
    if(is_missle == true)
    {
        if(player->coins >= cost_of_missle)
        {
            player->coins -= cost_of_missle;
            player->has_missle = true;
            is_missle = false;
        }
    }
    else if(is_laser == true)
    {
        if(player->coins >= cost_of_laser)
        {
            player->coins -= cost_of_laser;
            player->has_laser = true;
            is_laser = false;
        }
    }
    else if(is_shield == true)
    {
        if(player->coins >= cost_of_shield)
        {
            player->coins -= cost_of_shield;
            player->has_shield = true;
            is_shield = false;
        }
    }
    else if(is_screenclear == true)
    {
        if(player->coins >= cost_of_screenclear)
        {
            player->coins -= cost_of_screenclear;
            player->has_screenclear = true;
            is_screenclear = false;
        }
    }
    else if(is_reborn == true)
    {
        if(player->coins >= cost_of_reborn * (input_number_of_reborn.text()).toInt())
        {
            player->coins -= cost_of_reborn * (input_number_of_reborn.text()).toInt();
            player->revivetokens_num += cost_of_reborn * (input_number_of_reborn.text()).toInt();
            is_reborn = false;
        }
    }
    else if(is_health == true)
    {
        if(player->coins>cost_of_health)
        {
            player->coins -= cost_of_health;
            player->myplane_health += 1;
            is_health = false;
        }
    }
    else if(is_speed == true)
    {
        if(player->coins>cost_of_speed)
        {
            player->coins -= cost_of_speed;
            player->myplane_speed += 1;
            is_speed = false;
        }
    }
    else if(is_bulletinterval == true)
    {
        if(player->coins>cost_of_bulletinterval)
        {
            player->coins -= cost_of_bulletinterval;
            player->myplane_bulletinterval -= 2;
            is_bulletinterval = false;
        }
    }
}

void MainWindow::click_cancel_button()
{
    if(is_missle == true)
    {
        is_missle = false;
    }
    else if(is_laser == true)
    {
        is_laser = false;
    }
    else if(is_shield == true)
    {
        is_shield = false;
    }
    else if(is_screenclear == true)
    {
        is_screenclear = false;
    }
    else if(is_reborn == true)
    {
        is_reborn = false;
    }
    else if(is_health == true)
    {
        is_health = false;
    }
    else if(is_speed == true)
    {
        is_speed = false;
    }
    else if(is_bulletinterval == true)
    {
        is_bulletinterval = false;
    }
}

bool cmp(const Gamerecord &a, const Gamerecord &b)
{
    if (a.score > b.score)  return true;
    else if (a.score == b.score && a.coins > b.coins)   return true;
    else    return false;
}

void MainWindow::common_sort()
{
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
            qDebug() << temp[i].player_name << temp[i].score << endl;
        }
        sort(temp, temp+record_num, cmp);
        for (int i=0; i<record_num && i<10; i++)
        {
            common_record[i] = temp[i];
        }
        File.close();
    }

}

void MainWindow::endless_sort()
{
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
            txt >> record_num >> temp[i].player_name >> temp[i].score >> temp[i].coins;
        }
        sort(temp, temp+record_num, cmp);
        for (int i=0; i<record_num && i<10; i++)
        {
            endless_record[i] = temp[i];
        }
        File.close();
    }
}
