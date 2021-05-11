#include "headers_window/gameover.h"
#include "ui_gameover.h"

gameover::gameover(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::gameover)
{
    ui->setupUi(this);
}

gameover::~gameover()
{
    delete ui;
}
