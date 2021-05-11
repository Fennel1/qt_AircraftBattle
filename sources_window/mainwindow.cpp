#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "config.h"

#include <QPainter>
#include <QProxyStyle>
#include <QTabBar>
#include <QStyleOptionTab>
#include <QTabWidget>

class CustomTabStyle : public QProxyStyle
{
public:
    QSize sizeFromContents(ContentsType type, const QStyleOption *option,
        const QSize &size, const QWidget *widget) const
    {
        QSize s = QProxyStyle::sizeFromContents(type, option, size, widget);
        if (type == QStyle::CT_TabBarTab) {
            s.transpose();
            s.rwidth() = 100; // 设置每个tabBar中item的大小
            s.rheight() = 50;
        }
        return s;
    }

    void drawControl(ControlElement element, const QStyleOption *option, QPainter *painter, const QWidget *widget) const
    {
        if (element == CE_TabBarTabLabel) {
            if (const QStyleOptionTab *tab = qstyleoption_cast<const QStyleOptionTab *>(option)) {
                QRect allRect = tab->rect;

                if (tab->state & QStyle::State_Selected) {
                    painter->save();
                    painter->setPen(0x89cfff);
                    painter->setBrush(QBrush(0x89cfff));
                    painter->drawRect(allRect.adjusted(6, 6, -6, -6));
                    painter->restore();
                }
                QTextOption option;
                option.setAlignment(Qt::AlignCenter);
                if (tab->state & QStyle::State_Selected) {
                    painter->setPen(0xf8fcff);
                }
                else {
                    painter->setPen(0x5d5d5d);
                }

                painter->drawText(allRect, tab->text, option);
                return;
            }
        }

        if (element == CE_TabBarTab) {
            QProxyStyle::drawControl(element, option, painter, widget);
        }
    }
};

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tabWidget->setTabPosition(QTabWidget::West);
    ui->tabWidget->tabBar()->setStyle(new CustomTabStyle);
    //窗口标题
    setWindowTitle(GAME_TITLE);
    //窗口图标
    setWindowIcon(QIcon(GAME_ICON));
    //窗口大小
    resize(1050,750);
    //按钮
    btn_back.setParent(this);
    btn_back.setText("切换账号");
    btn_back.move(0,600);
    btn_back.resize(100,40);

    connect(&btn_back, &QPushButton::clicked, this, &MainWindow::sendslot_back);
    /*
    //play game界面设置
    QPushButton* btn_to_mainscene = new QPushButton;
    ui->tabWidget->addTab(btn_to_mainscene, "play");
    btn_to_mainscene->setParent(this);
    btn_to_mainscene->setText("Start Game");
    btn_to_mainscene->move(410,380);
    btn_to_mainscene->resize(260,50);
    btn_to_mainscene->setFont(QFont("consolas",16));

    connect(&*btn_to_mainscene, &QPushButton::clicked, this, &MainWindow::change_window_to_mainscene);
    */

#if 0
    ui->tabWidget->setStyleSheet("QTabWidget::pane{ \
            border-left: 1px solid #eeeeee;\
        }");
#endif
}

void MainWindow::sendslot_back()
{
    emit signal_back();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btn_to_mainscene_clicked()
{
    MainScene* win_mainscene = new MainScene;
    win_mainscene->setWindowModality(Qt::ApplicationModal);
    win_mainscene->show();
}
