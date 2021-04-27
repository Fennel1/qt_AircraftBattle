#ifndef THEHOME_H
#define THEHOME_H

#include <QMainWindow>
#include <QPushButton>
#include "choosemodel.h"

class theHome : public QMainWindow
{
    Q_OBJECT
public:
    explicit theHome(QWidget *parent = nullptr);
    void deal_slot_from_choosemodel();
    void change_window_to_choosemodel();


signals:

private:
    //设置按钮
    QPushButton btn_to_choose_model;
    QPushButton btn_to_help;
    QPushButton btn_to_list;
    QPushButton btn_to_shop;
    QPushButton btn_to_repository;
    QPushButton btn_to_login_window;
    //设置子窗口
    chooseModel win_choose;
};

#endif // THEHOME_H
