#ifndef PROPS_H
#define PROPS_H

#include <string>

class Props
{
public:
    Props();

private:
    bool is_own;//该玩家是否拥有
    std::string name;//名称
    int id;//编号
    int price;//售价
};

#endif // PROPS_H
