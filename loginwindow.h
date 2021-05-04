#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QWidget>
#include <QPushButton>
#include "mainwindow.h"

class loginWindow : public QWidget
{
    Q_OBJECT
public:
    explicit loginWindow(QWidget *parent = nullptr);
    void sendslot_back();
    void change_window_to_mainwindow();
    void deal_slot_from_mainwindow();

signals:
    void signal_back();

private:
    QPushButton btn_back;
    QPushButton btn_confirm_login;

    MainWindow win_mainwindow;

};

#endif // LOGINWINDOW_H
