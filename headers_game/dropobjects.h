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
private:
    int bloodup;      //加血量
};











#endif // DROPOBJECTS_H
