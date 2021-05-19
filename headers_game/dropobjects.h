#ifndef DROPOBJECTS_H
#define DROPOBJECTS_H
#include <QPixmap>

class MainScene;


class DropObject{
    friend class MainScene;
public:
    DropObject();
    DropObject(QString objectpath);

    //更新坐标
    void updatePosition();

    //掉落物被拾取
    void beGet();

    //设置掉落物参数
    void setObjectPath(QString objectpath);
    void setspeed(int speed);

protected:
    //掉落物资源对象
    QPixmap object;

    //宽
    int widthl;
    int widthr;

    //位置
    int X;
    int Y;

    //掉落物的矩形边框（碰撞检测）
    QRect rect;

    //状态
    bool free;

    //速度
    int speed;


};

class BloodBag :public DropObject{
public:
    BloodBag();
    BloodBag(QString objectpath);
    void updatePosition();
    void setObjectPath(QString objectpath);
};

class BcdFree :public DropObject{
public:
    BcdFree();
    BcdFree(QString objectpath);
    void updatePosition();
    void setObjectPath(QString objectpath);
};

class ScdFree :public DropObject{
public:
    ScdFree();
    ScdFree(QString objectpath);
    void updatePosition();
    void setObjectPath(QString objectpath);
};

class Coin :public DropObject{
    friend class MainScene;
public:
    Coin();
    Coin(QString objectpath);
    void updatePosition();
    void setObjectPath(QString objectpath);
    void updateInfo();
    void setBombPath(QString path);
protected:
    //放爆炸资源数组
    QVector<QPixmap> pixArr;

    //爆炸状态
    bool bombfree;

    //爆炸切图的时间间隔
    int recoder;

    //爆炸时加载的图片下标
    int index;

    //爆炸参数
    int bombmax;
    int bombinterval;
};

#endif // DROPOBJECTS_H
