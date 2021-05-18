#ifndef PLAYER_H
#define PLAYER_H
#include <QPixmap>
#include "headers_game/data.h"

class MainScene;
class MainWindow;
class loginWindow;
class RegWindow;
class ForgetPW;

class Player
{
    friend class RegWindow;
    friend class MainScene;
    friend class MainWindow;
    friend class loginWindow;
    friend class ForgetPW;
public:
    Player();
    Player(QString id, QString password, QString phone,Data mydata, int coins, int myplane_health, int myplane_speed, int myplane_bulletinterval,
           QString myplane_path, bool has_screenclear, bool has_laser, bool has_missle, bool has_shield, int revivetokens_num);
    Player(const Player &p);
    Player& operator=(const Player &p);
protected:
    QString id;         //账户
    QString password;   //密码
    QString phone;
    Data mydata;    //数据

    int coins;  //金币

    //游戏参数
    int myplane_health;           //飞机生命值
    int myplane_speed;            //飞机速度
    int myplane_bulletinterval;   //飞机射速
    QString myplane_path;           //飞机皮肤

    //技能
    bool has_screenclear;
    bool has_laser;
    bool has_missle;
    bool has_shield;

    //道具
    int revivetokens_num;        //复活币

};

#endif // PLAYER_H

