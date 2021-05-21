#include "gamerecord.h"

Gamerecord::Gamerecord() {}
CommonRecord::CommonRecord() {}
EndlessRecord::EndlessRecord() {}

Gamerecord::Gamerecord(QString player_name, int score, int coins):
    player_name(player_name), score(score), coins(coins) {}

CommonRecord::CommonRecord(QString player_name, int score, int coins) :
    Gamerecord (player_name, score, coins) {}

EndlessRecord::EndlessRecord(QString player_name, int score, int coins, int difficulty) :
    Gamerecord (player_name, score, coins), difficulty(difficulty) {}

void CommonRecord::update()
{
    QFile File(COMMONRECORDFILE_PATH);
    QDataStream txt(&File);
    int record_num;
//    File.open(QIODevice::WriteOnly);
//    txt << 0;
//    File.close();
    File.open(QIODevice::ReadOnly);
    txt >> record_num;
    File.close();
    if (record_num == 0)
    {
        record_num++;
        File.open(QIODevice::WriteOnly);
        txt << record_num << this->player_name << this->score << this->coins;
        File.close();
    }
    else
    {
        CommonRecord record_list[record_num];
        QString t_name;

        int t_score;
        int t_coins;

        File.open(QIODevice::ReadOnly);
        for (int i=0; i<record_num; i++)
        {
            txt >> record_num >> t_name >> t_score >> t_coins;
            qDebug() << record_num << t_name << t_score;
            record_list[i] = CommonRecord(t_name, t_score, t_coins);
        }
        File.close();
        File.open(QIODevice::WriteOnly);
        for (int i=0; i<record_num; i++)
        {
            txt << record_num+1 << record_list[i].player_name << record_list[i].score << record_list[i].coins;
        }
        txt << record_num+1 << this->player_name << this->score << this->coins;
        File.close();
    }
}

void EndlessRecord::update()
{
    QFile File(ENDLESSRECORDFILE_PATH);
    QDataStream txt(&File);
    int record_num;
//    File.open(QIODevice::WriteOnly);
//    txt << 0;
//    File.close();
    File.open(QIODevice::ReadOnly);
    txt >> record_num;
    File.close();
    if (record_num == 0)
    {
        record_num++;
        File.open(QIODevice::WriteOnly);
        txt << record_num << this->player_name << this->score << this->coins << this->difficulty;
        File.close();
    }
    else
    {
        EndlessRecord record_list[record_num];
        QString t_name;

        int t_score;
        int t_coins;

        int t_difficulty;

        File.open(QIODevice::ReadOnly);
        for (int i=0; i<record_num; i++)
        {
            txt >> record_num >> t_name >> t_score >> t_coins >> t_difficulty;
            qDebug() << record_num << t_name << t_score;
            record_list[i] = EndlessRecord(t_name, t_score, t_coins, t_difficulty);
        }
        File.close();
        File.open(QIODevice::WriteOnly);
        for (int i=0; i<record_num; i++)
        {
            txt << record_num+1 << record_list[i].player_name << record_list[i].score << record_list[i].coins << record_list[i].difficulty;
        }
        txt << record_num+1 << this->player_name << this->score << this->coins << this->difficulty;
        File.close();
    }
}
