#include "mainscene.h"
#include "thehome.h"
#include <QResource>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    theHome w;
    w.show();
    return a.exec();
}
