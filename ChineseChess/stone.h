#ifndef STONE_H
#define STONE_H

#include <QString>

class Stone
{
public:
    Stone();
    ~Stone();

    QString getText();
    void init(int );
public:
    enum TYPE{JIANG, CHE, PAO, MA, BING, SHI, XIANG};
    int _row;
    int _col;
    int _id;
    bool _dead;
    bool _red;
    TYPE _type;
    struct {
        int row, col;
        Stone::TYPE type;
    } StonePosMap[16] = {
    {0, 0, Stone::CHE},
    {0, 1, Stone::MA},
    {0, 2, Stone::XIANG},
    {0, 3, Stone::SHI},
    {0, 4, Stone::JIANG},
    {0, 5, Stone::SHI},
    {0, 6, Stone::XIANG},
    {0, 7, Stone::MA},
    {0, 8, Stone::CHE},

    {2, 1, Stone::PAO},
    {2, 7, Stone::PAO},

    {3, 0, Stone::BING},
    {3, 2, Stone::BING},
    {3, 4, Stone::BING},
    {3, 6, Stone::BING},
    {3, 8, Stone::BING}
    };
};

#endif // STONE_H
