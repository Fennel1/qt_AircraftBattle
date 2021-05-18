#ifndef FORGETPW_H
#define FORGETPW_H


#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QWidget>
#include <QDebug>
#include <QPushButton>
#include <iostream>
#include <QFile>
#include "mainwindow.h"
#include "player.h"
#include <QMessageBox>

class ForgetPW : public QWidget
{
    Q_OBJECT
public:
    explicit ForgetPW(QWidget *parent = nullptr);
    void sendslot_back();
    void changePW();
signals:
    void signal_back();

private:
    QPushButton btn_back;
    QPushButton btnConfirm;

    Player *player;

    QLabel *userNameLbl;
    QLabel *phoneLbl;
    QLineEdit *userNameLEd;
    QLineEdit *phoneLEd;
    QLabel *pwdLbl;
    QLineEdit *pwdLEd;           //密码编辑行
    QLabel *btnConfirmPW;
    QLineEdit *ConfirmLEd;


};

#endif // FORGETPW_H
