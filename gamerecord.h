#ifndef GAMERECORD_H
#define GAMERECORD_H

#include <QString>
#include <QFileDialog>
#include <QFile>
#include <QDebug>
#include <QDataStream>
#include "headers_game/config.h"

class MainWindow;
class MainScene;

class Gamerecord
{
    friend class MainWindow;
    friend class MainScene;
    friend bool cmp (const Gamerecord & a, const Gamerecord & b);
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
    friend class MainWindow;
public:
    CommonRecord();
    CommonRecord(QString player_name, int score, int coins);
    void update();
};

class EndlessRecord : public Gamerecord
{
    friend class MainWindow;
public:
    EndlessRecord();
    EndlessRecord(QString player_name, int score, int coins, int difficulty);
    void update();
private:
    int difficulty;
};

#endif // GAMERECORD_H
