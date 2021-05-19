#ifndef GAMERECORD_H
#define GAMERECORD_H

#include <QString>
#include <QFile>
#include <QDebug>
#include <QDataStream>
#include "headers_game/config.h"

class Gamerecord
{
public:
    Gamerecord();
    Gamerecord(QString player_name, int score, int coins);
protected:
    QString player_name;

    int score;
    int coins;
};

class CommonRecord : public Gamerecord
{
public:
    CommonRecord();
    CommonRecord(QString player_name, int score, int coins);
    void update();
};

class EndlessRecord : public Gamerecord
{
public:
    EndlessRecord();
    EndlessRecord(QString player_name, int score, int coins, int difficulty);
    void update();
private:
    int difficulty;
};

#endif // GAMERECORD_H
