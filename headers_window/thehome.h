#ifndef THEHOME_H
#define THEHOME_H

#include <QWidget>
#include <QPushButton>
#include "loginwindow.h"

class theHome : public QWidget
{
    Q_OBJECT
public:
    explicit theHome(QWidget *parent = nullptr);
    void change_window_to_loginwindow();
    void deal_slot_from_loginwindow();

signals:

private:
    //设置按钮
    QPushButton btn_to_login_window;
    QPushButton btn_to_help_window;
    //子界面
    loginWindow win_login;

};

#endif // THEHOME_H
