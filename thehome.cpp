#include "thehome.h"

theHome::theHome(QWidget *parent) : QMainWindow(parent)
{
    //定义pushbutton的各种属性
    btn_to_choose_model.setParent(this);
    btn_to_choose_model.setText("选择模式");
    btn_to_choose_model.move(150,300);
    btn_to_choose_model.resize(200,40);

    btn_to_login_window.setParent(this);
    btn_to_login_window.setText("登录账号");
    btn_to_login_window.move(150,250);
    btn_to_login_window.resize(200,40);

    btn_to_help.setParent(this);
    btn_to_help.setText("帮助");
    btn_to_help.move(380,670);
    btn_to_help.resize(100,30);

    btn_to_list.setParent(this);
    btn_to_list.setText("排行");
    btn_to_list.move(150,350);
    btn_to_list.resize(200,40);

    btn_to_shop.setParent(this);
    btn_to_shop.setText("商店");
    btn_to_shop.move(150,400);
    btn_to_shop.resize(100,40);

    btn_to_repository.setParent(this);
    btn_to_repository.setText("仓库");
    btn_to_repository.move(250,400);
    btn_to_repository.resize(100,40);

    //本界面按钮的信号连接
    connect(&btn_to_choose_model, &QPushButton::released, this, &theHome::change_window_to_choosemodel);
    //对子窗口信号的处理
    connect(&win_choose, &chooseModel::signal_back, this, &theHome::deal_slot_from_choosemodel);

    //设置窗口大小
    resize(480,700);

}

void theHome::change_window_to_choosemodel()
{
   win_choose.show();
   this->hide();
}

void theHome::deal_slot_from_choosemodel()
{
    win_choose.hide();
    show();
}
