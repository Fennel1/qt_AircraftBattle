#include "headers_window/gamehelp.h"


GameHelp::GameHelp(QWidget *parent) : QWidget(parent)
{
    resize(480,700);

    this->setWindowTitle(tr("游戏帮助"));
    //返回按钮
    btn_back.setParent(this);
    btn_back.setText("返回");
    btn_back.resize(100,40);
    connect(&btn_back, &QPushButton::clicked, this, &GameHelp::sendslot_back);
    QLabel *lbl = new QLabel(this);
    QFont lbl_font;
    lbl_font.setPointSize(12);      //设置字体大小
    lbl->setFont(lbl_font);
    lbl->setText("test\nadwa\na\na\na\na\nasna\na\nasna\na\nas");
    lbl->setGeometry(QRect(150, 180, 180, 340)); //设置大小和位置
    lbl->setAlignment(Qt::AlignTop);

}

void GameHelp::sendslot_back()
{
    emit signal_back();
}
