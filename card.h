#ifndef CARD_H
#define CARD_H

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
    CardSuit getSuit();
    CardPoint getPoint();

    Card();
private:
    CardSuit suit;
    CardPoint point;
};

#endif // CARD_H
