#ifndef GAMEHELP_H
#define GAMEHELP_H

#include <QWidget>
#include <QPushButton>
#include "mainwindow.h"
#include "player.h"

#include <QApplication>
#include <QMainWindow>
#include <QLabel>
#include <QRect>
#include <QFont>
class GameHelp : public QWidget
{
    Q_OBJECT
public:
    explicit GameHelp(QWidget *parent = nullptr);
    void sendslot_back();


signals:
    void signal_back();

private:
    QPushButton btn_back;

    Player *player;

};


#endif // GAMEHELP_H
