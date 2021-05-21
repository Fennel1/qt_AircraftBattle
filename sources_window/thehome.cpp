#include "headers_window/thehome.h"

theHome::theHome(QWidget *parent) : QWidget(parent)
{
    btn_to_login_window.setParent(this);
    btn_to_login_window.setText("登录账号");
    btn_to_login_window.move(150,250);
    btn_to_login_window.resize(200,40);

    btn_to_help_window.setParent(this);
    btn_to_help_window.setText("游戏帮助");
    btn_to_help_window.move(150,350);
    btn_to_help_window.resize(200,40);

    //本窗口按钮信号连接
    connect(&btn_to_login_window, &QPushButton::clicked, this, &theHome::change_window_to_loginwindow);


    //对子窗口信号的处理
    connect(&win_login, &loginWindow::signal_back, this, &theHome::deal_slot_from_loginwindow);

    connect(&btn_to_help_window, &QPushButton::clicked, this, &theHome::change_window_to_gamehelp);

    connect(&game_help, &GameHelp::signal_back, this, &theHome::deal_slot_from_gamehelp);

    //设置窗口大小
    resize(480,700);
}

void theHome::change_window_to_loginwindow()
{
    win_login.show();
    this->hide();
}

void theHome::deal_slot_from_loginwindow()
{
    win_login.hide();
    show();
}

void theHome::change_window_to_gamehelp()
{
    game_help.show();
    this->hide();
}

void theHome::deal_slot_from_gamehelp()
{
    game_help.hide();
    show();
}
