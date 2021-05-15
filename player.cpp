#include "player.h"

Player::Player()
{

}

Player::Player(QString id, QString password, Data mydata, int coins, int myplane_health, int myplane_speed, int myplane_bulletinterval,
    QString myplane_path, bool has_screenclear, bool has_laser, bool has_missle, bool has_shield, int revivetokens_num) :
    id(id), password(password), mydata(mydata), coins(coins), myplane_health(myplane_health), myplane_speed(myplane_speed),
    myplane_bulletinterval(myplane_bulletinterval), myplane_path(myplane_path), has_screenclear(has_screenclear), has_laser(has_laser),
    has_missle(has_missle), has_shield(has_shield), revivetokens_num(revivetokens_num) { }
