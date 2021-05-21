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
    QLabel *biaoti1 = new QLabel(this);
        QLabel *biaoti2 = new QLabel(this);
        QLabel *biaoti3 = new QLabel(this);
        QLabel *biaoti4 = new QLabel(this);
        QLabel *neirong1 = new QLabel(this);
        QLabel *neirong2 = new QLabel(this);
        QLabel *neirong3 = new QLabel(this);
        QLabel *neirong4 = new QLabel(this);
        QLabel *CYbiaoti = new QLabel(this);
        QLabel *CYneirong = new QLabel(this);
        QLabel *KYbiaoti = new QLabel(this);
        QLabel *lianjie = new QLabel(this);
        QFont Bfont;
        QFont Sfont;

        CYbiaoti->setFont(Bfont);
        CYbiaoti->setStyleSheet("color:#FF9900;");
        CYneirong->setFont(Bfont);
        KYbiaoti->setFont(Bfont);
        lianjie->setFont(Bfont);
        biaoti1->setFont(Bfont);
        biaoti2->setFont(Bfont);
        biaoti3->setFont(Bfont);
        biaoti4->setFont(Bfont);
        neirong1->setFont(Sfont);
        neirong2->setFont(Sfont);
        neirong3->setFont(Sfont);
        neirong4->setFont(Sfont);
        biaoti1->setStyleSheet("color:#0099FF;");
        biaoti2->setStyleSheet("color:#0099FF;");
        biaoti3->setStyleSheet("color:#0099FF;");
        biaoti4->setStyleSheet("color:#0099FF;");
        biaoti1->setText("关于操作：");
        biaoti2->setText("关于商店：");
        biaoti3->setText("关于技能：");
        biaoti4->setText("关于掉落物：");
        neirong1->setText("使用W，S，A，D进行移动，\n"
                          "J为普通攻击，Esc为暂停。");
        neirong2->setText("商店可用于解锁技能和道具以及升级\n"
                          "属性。金币可通过游玩游戏获得。");
        neirong3->setText("目前共有两个小技能：激光、导弹。\n"
                          "以及两个大技能：清屏、护盾。");
        neirong4->setText("血包：回复一点生命值。\n"
                          "金币：获取一金币。\n"
                          "灰CD：重置激光和导弹的CD。\n"
                          "红CD：重置清屏和护盾的CD。");
        biaoti1->setAlignment(Qt::AlignTop);
        biaoti2->setAlignment(Qt::AlignTop);
        biaoti3->setAlignment(Qt::AlignTop);
        biaoti4->setAlignment(Qt::AlignTop);
        neirong1->setAlignment(Qt::AlignTop);
        neirong2->setAlignment(Qt::AlignTop);
        neirong3->setAlignment(Qt::AlignTop);
        neirong4->setAlignment(Qt::AlignTop);
        biaoti1->setGeometry(QRect(100, 60, 100, 18));
        biaoti2->setGeometry(QRect(100, 130, 100, 18));
        biaoti3->setGeometry(QRect(100, 200, 100, 18));
        biaoti4->setGeometry(QRect(100, 270, 100, 18));
        neirong1->setGeometry(QRect(130, 80, 360, 100));
        neirong2->setGeometry(QRect(130, 150, 360, 100));
        neirong3->setGeometry(QRect(130, 220, 360, 100));
        neirong4->setGeometry(QRect(130, 290, 360, 100));
        CYbiaoti->setGeometry(QRect(100, 500, 100, 18));
        CYbiaoti->setText("小组成员：");
        CYneirong->setGeometry(QRect(175, 458, 360, 100));
        CYneirong->setText("金智勇，宁慧霖，邓又铭");
        KYbiaoti->setGeometry(QRect(100, 540, 100, 18));
        KYbiaoti->setStyleSheet("color:#FF9900;");
        KYbiaoti->setText("开源代码：");
        lianjie->setGeometry(QRect(175, 500, 360, 100));
        lianjie->setOpenExternalLinks(true);
        lianjie->setText("<style> a {text-decoration: none} </style><a style='color: blue;' href=\"https://github.com/Fennel1/qt_AircraftBattle\">Github");

}

void GameHelp::sendslot_back()
{
    emit signal_back();
}
