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
    win_mainwindow->show();
    this->hide();
}

void loginWindow::deal_slot_from_mainwindow()
{
    win_mainwindow->hide();
    show();
}
