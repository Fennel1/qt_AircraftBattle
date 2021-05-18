#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QPainter>
#include <QRect>
#include <QDebug>
#include <QValidator>
#include <QInputDialog>
#include "headers_game/mainscene.h"
#include "player.h"
using namespace std;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(Player *p, QWidget *parent = nullptr);
    ~MainWindow();
    void sendslot_back();
    void change_window_to_mainscene();
    void paintEvent(QPaintEvent *event);

    void show_reborn_rect();
    void show_missle_rect();
    void show_laser_rect();
    void show_shield_rect();
    void show_screenclear_rect();
    void click_ok_button();
    void click_cancel_button();

signals:
    void signal_back();

private slots:

    void on_btn_to_mainscene_clicked();

private:
    int cost_of_reborn;
    int cost_of_missle;
    int cost_of_laser;
    int cost_of_shield;
    int cost_of_screenclear;

    Ui::MainWindow *ui;
    QPushButton btn_back;

    QRect rect_ok_and_cancel;
    QPushButton btn_ok;
    QPushButton btn_cancel;
    QLineEdit input_number_of_reborn;

    //判断弹窗绘制后显示哪个交互
    bool is_reborn;
    bool is_missle;
    bool is_laser;
    bool is_shield;
    bool is_screenclear;

    Player *player;
};

#endif // MAINWINDOW_H
