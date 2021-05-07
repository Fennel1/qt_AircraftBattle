#include "mainscene.h"
#include "thehome.h"
#include <QResource>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    theHome w;    //界面
//    MainScene w;    //游戏
    w.show();
    return a.exec();
}
