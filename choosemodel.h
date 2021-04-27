#ifndef CHOOSEMODEL_H
#define CHOOSEMODEL_H

#include <QWidget>
#include <QPushButton>
#include "mainscene.h"

class chooseModel : public QWidget
{
    Q_OBJECT
public:
    explicit chooseModel(QWidget *parent = nullptr);
    //发送信号
    void sendslot_back();
    void sendslot_to_mainscene();
    void change_window_to_mainscene();
    void deal_slot_from_mainscene();

signals:
    void signal_mainscene();
    void signal_back();

private:
    QPushButton btn_back;
    QPushButton btn_to_mainscene;
    QPushButton btn_to_model2;

    MainScene win_mainscene;
};

#endif // CHOOSEMODEL_H
