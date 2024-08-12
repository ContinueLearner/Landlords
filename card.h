#ifndef CARD_H
#define CARD_H

#include <qglobal.h>
#include <QVector>

class Card
{
public:
    enum CardSuit
    {
        Suit_Begin,
        Diamond,
        Club,
        Heart,
        Spade,
        Suit_End
    };

    enum CardPoint
    {
        Point_Begin,
        Point_3,
        Point_4,
        Point_5,
        Point_6,
        Point_7,
        Point_8,
        Point_9,
        Point_10,
        Point_J,
        Point_Q,
        Point_K,
        Point_A,
        Point_2,
        Point_SJ,//small joker
        Point_BJ,//big joker
        Point_End
    };

    void setSuit(CardSuit s);
    void setPoint(CardPoint p);
    CardSuit getSuit()const;
    CardPoint getPoint()const;

    Card();
private:
    CardSuit suit;
    CardPoint point;
};

// 对象比较
bool lessSort(const Card& c1, const Card& c2);
bool greaterSort(const Card& c1, const Card& c2);
bool operator <(const Card& c1, const Card& c2);

bool operator==(const Card& c1,const Card& c2);
uint qHash(const Card& c);


// 定义类型的别名
using CardList = QVector<Card>;
#endif // CARD_H
