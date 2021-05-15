#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include "headers_game/mainscene.h"
#include "player.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void sendslot_back();
    void change_window_to_mainscene();

signals:
    void signal_back();

private slots:

    void on_btn_to_mainscene_clicked();

private:
    Ui::MainWindow *ui;
    QPushButton btn_back;
};

#endif // MAINWINDOW_H
