#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <algorithm>
#include <QMainWindow>
#include <QPushButton>
#include <QPainter>
#include <QRect>
#include <QDebug>
#include <QValidator>
#include <QInputDialog>
#include "headers_game/mainscene.h"
#include "player.h"
#include "gamerecord.h"
using namespace std;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    friend bool cmp(const Gamerecord & a, const Gamerecord & b);

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
    void common_sort();
    void endless_sort();
    void buy_health();
    void buy_speed();
    void buy_bulletinterval();
    void update_playerfile();

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
    int cost_of_health;
    int cost_of_speed;
    int cost_of_bulletinterval;

    Ui::MainWindow *ui;
    QPushButton btn_back;

    QRect rect_ok_and_cancel;
    QPushButton btn_ok;
    QPushButton btn_cancel;
    QLabel label_rect;
    QLineEdit input_number_of_reborn;

    //判断弹窗绘制后显示哪个交互
    bool is_reborn;
    bool is_missle;
    bool is_laser;
    bool is_shield;
    bool is_screenclear;
    bool is_health;
    bool is_speed;
    bool is_bulletinterval;

    //记录
    CommonRecord common_record[10];
    EndlessRecord endless_record[10];

    Player *player;
};

bool cmp(const Gamerecord & a, const Gamerecord & b);

#endif // MAINWINDOW_H
