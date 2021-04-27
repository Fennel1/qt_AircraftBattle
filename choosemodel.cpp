#include "choosemodel.h"

chooseModel::chooseModel(QWidget *parent) : QWidget(parent)
{
    //设置界面大小
    resize(480,700);
    //返回按钮
    btn_back.setParent(this);
    btn_back.setText("返回");
    btn_back.resize(100,40);

    connect(&btn_back, &QPushButton::clicked, this, &chooseModel::sendslot_back);
    //关卡模式按钮
    btn_to_mainscene.setParent(this);
    btn_to_mainscene.setText("关卡模式");
    btn_to_mainscene.move(150,250);
    btn_to_mainscene.resize(200,40);

    connect(&btn_to_mainscene, &QPushButton::clicked, this, &chooseModel::change_window_to_mainscene);
    //处理子窗口信号
    connect(&win_mainscene, &MainScene::signal_mainscene, this, &chooseModel::deal_slot_from_mainscene);
}

void chooseModel::sendslot_back()
{
    emit signal_back();
}

void chooseModel::sendslot_to_mainscene()
{
    emit signal_mainscene();
}

void chooseModel::change_window_to_mainscene()
{
   win_mainscene.show();
   this->hide();
}

void chooseModel::deal_slot_from_mainscene()
{
    win_mainscene.hide();
    show();
}
















