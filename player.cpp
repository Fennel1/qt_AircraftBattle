#include "player.h"

Player::Player()
{
    myplane_path = COMMONENEMY_PATH;
    myplane_speed = 5;
    myplane_health = 5;
    myplane_bulletinterval = 20;
}

Player::Player(QString id, QString password,QString phone,Data mydata, int coins, int myplane_health, int myplane_speed, int myplane_bulletinterval,
               QString myplane_path, bool has_screenclear, bool has_laser, bool has_missle, bool has_shield, int revivetokens_num) :
    id(id), password(password),phone(phone),mydata(mydata), coins(coins), myplane_health(myplane_health), myplane_speed(myplane_speed),
    myplane_bulletinterval(myplane_bulletinterval), myplane_path(myplane_path), has_screenclear(has_screenclear), has_laser(has_laser),
    has_missle(has_missle), has_shield(has_shield), revivetokens_num(revivetokens_num) { }
Player::Player(const Player &p) :
    id(p.id), password(p.password),phone(p.phone) ,mydata(p.mydata), coins(p.coins), myplane_health(p.myplane_health),
    myplane_speed(p.myplane_speed),myplane_bulletinterval(p.myplane_bulletinterval), myplane_path(p.myplane_path),
    has_screenclear(p.has_screenclear), has_laser(p.has_laser),has_missle(p.has_missle), has_shield(p.has_shield),
    revivetokens_num(p.revivetokens_num) { }
Player& Player::operator=(const Player &p)
{
    if (this != &p)
    {
        id=p.id; password=p.password;phone=p.phone;mydata=p.mydata; coins=p.coins; myplane_health=p.myplane_health;
        myplane_speed=p.myplane_speed;myplane_bulletinterval=p.myplane_bulletinterval; myplane_path=p.myplane_path;
        has_screenclear=p.has_screenclear; has_laser=p.has_laser;has_missle=p.has_missle; has_shield=p.has_shield;
        revivetokens_num=p.revivetokens_num;
    }
    return *this;

}
