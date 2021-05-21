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

    connect(&btn_back, &QPushButton::clicked, this, &MainWindow::sendslot_back);

    //将矩形初始为不显示
    is_reborn = false;
    is_missle = false;
    is_laser = false;
    is_shield = false;
    is_screenclear = false;
    //商店中交互后弹窗的设置
    rect_ok_and_cancel.setRect(100,150,400,500);
    btn_ok.setParent(this);
    btn_ok.setText(QStringLiteral("确定"));
    btn_ok.move(200, 500);
    btn_ok.resize(100, 50);
    btn_ok.hide();
    btn_cancel.setParent(this);
    btn_cancel.setText(QStringLiteral("取消"));
    btn_cancel.move(350, 500);
    btn_cancel.resize(100, 50);
    btn_cancel.hide();
    QValidator *vali_integer = new QIntValidator(1,99,this);
    input_number_of_reborn.setParent(this);
    input_number_of_reborn.setValidator(vali_integer);
    input_number_of_reborn.resize(300,50);
    input_number_of_reborn.move(170,400);
    input_number_of_reborn.setPlaceholderText(QStringLiteral("请输入购买数量(1~99)"));
    input_number_of_reborn.setFont(QFont("consolas",12));
    input_number_of_reborn.hide();

    //花费金币的设置
    cost_of_reborn = 1;
    cost_of_missle = 2;
    cost_of_laser = 3;
    cost_of_shield = 4;
    cost_of_screenclear = 5;

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
    if(is_laser == true||is_missle == true||is_reborn == true||is_screenclear == true||is_shield == true)
    {
        //        painter.begin(this);
        painter.setPen(Qt::NoPen);
        painter.setBrush(QColor(0,170,255,100));
        painter.drawRoundRect(rect_ok_and_cancel);
        painter.setPen(QColor(0,0,0));
        QFont font("consolas", 15);
        painter.setFont(font);
        painter.drawText(200,300,QStringLiteral("确定购买"));
        btn_ok.show();
        btn_cancel.show();
        if(is_reborn == true)
        {
            input_number_of_reborn.show();
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
    MainScene* win_mainscene = new MainScene(0, 0, player);
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
}

void MainWindow::show_missle_rect()
{
    is_reborn = false;
    is_laser = false;
    is_shield = false;
    is_screenclear = false;
    is_missle = true;
}

void MainWindow::show_laser_rect()
{
    is_reborn = false;
    is_missle = false;
    is_shield = false;
    is_screenclear = false;
    is_laser = true;
}


void MainWindow::show_shield_rect()
{
    is_reborn = false;
    is_missle = false;
    is_laser = false;
    is_screenclear = false;
    is_shield = true;
}


void MainWindow::show_screenclear_rect()
{
    is_reborn = false;
    is_missle = false;
    is_laser = false;
    is_shield = false;
    is_screenclear = true;
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
}
