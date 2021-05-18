#include "headers_window/mainwindow.h"
#include "headers_window/thehome.h"
#include <QResource>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    theHome w;    //界面
//    MainScene w(1, 5);    //游戏
    w.show();

    return a.exec();
}


