#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H


#include "regwindow.h"
#include <QLabel>
#include <QLineEdit>
#include "forgetpw.h"
#include <QWidget>
#include <QDebug>
#include <QPushButton>
#include <iostream>
#include <QFile>
#include "mainwindow.h"
#include "player.h"
using namespace std;
class loginWindow : public QWidget
{
    Q_OBJECT
public:
    explicit loginWindow(QWidget *parent = nullptr);
    void sendslot_back();
    void deal_slot_from_mainwindow();
    void login();
    void change_window_to_regwindow();
    void change_window_to_forgetPWwindow();
    void deal_slot_from_regwindow();
    void deal_slot_from_forgetPWwindow();
signals:
    void signal_back();

private:
    QPushButton btn_back;
    QPushButton btn_confirm_login;

    Player *player;

    MainWindow *mainWindow;
    RegWindow regWindow;
    ForgetPW forgetWindow;
    QPushButton btnRegister;
    QPushButton btnForger;
    QLabel *userNameLbl;         //"用户名"标签
    QLabel *pwdLbl;              //"密码"标签
    QLineEdit *userNameLEd;      //用户名编辑行
    QLineEdit *pwdLEd;           //密码编辑行


};

#endif // LOGINWINDOW_H
