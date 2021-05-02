#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>

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

signals:
    void signal_back();

private:
    Ui::MainWindow *ui;
    QPushButton btn_back;
};

#endif // MAINWINDOW_H
