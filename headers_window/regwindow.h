#ifndef REGWINDOW_H
#define REGWINDOW_H

#include <QDialog>
#include <QLabel>
#include <QFileDialog>
#include <QLineEdit>
#include <QWidget>
#include <QDebug>
#include <QPushButton>
#include <iostream>
#include <QFile>
#include "mainwindow.h"
#include "player.h"

#include <QMessageBox>
using namespace std;

class RegWindow : public QWidget
{
    Q_OBJECT
public:
    explicit RegWindow(QWidget *parent = nullptr);
    void sendslot_back();
    void reg();
    void change_window_to_mainwindow();
signals:
    void signal_back();

private:
//    MainWindow *win_mainwindow;
    Player *player;

    QPushButton btn_back;
    MainWindow *mainWindow;
    QLabel *userNameLbl;         //"用户名"标签
    QLabel *pwdLbl;              //"密码"标签
    QLineEdit *userNameLEd;      //用户名编辑行
    QLineEdit *pwdLEd;           //密码编辑行
    QLabel *btnConfirmPW;
    QLineEdit *ConfirmLEd;
    QPushButton btnConfirmReg;
    QLabel *phoneLbl;
    QLineEdit *phoneLEd;

};

#endif // REGWINDOW_H
