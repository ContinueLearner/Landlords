#include "card.h"

void Card::setSuit(CardSuit s)
{
    this->suit = s;
}

void Card::setPoint(CardPoint p)
{
    this->point = p;
}

Card::CardSuit Card::getSuit()const
{
    return this->suit;
}

Card::CardPoint Card::getPoint()const
{
    return this->point;
}

Card::Card() {}

Card::Card( CardPoint p,CardSuit s)
{
    this->point = p;
    this->suit = s;
}


bool operator==(const Card& c1,const Card& c2)
{
    return (c1.getPoint() == c2.getPoint() && c1.getSuit() == c2.getSuit());
}

uint qHash(const Card& c)
{
    return c.getPoint() * 100 + c.getSuit();
}


bool lessSort(const Card &c1, const Card &c2)
{
    if(c1.getPoint() != c2.getPoint())return c1.getPoint() < c2.getPoint();
    else if(c1.getSuit() != c2.getSuit())return c1.getSuit() < c2.getSuit();
}

bool greaterSort(const Card &c1, const Card &c2)
{
    if(c1.getPoint() != c2.getPoint())return c1.getPoint() > c2.getPoint();
    else if(c1.getSuit() != c2.getSuit())return c1.getSuit() > c2.getSuit();
}

bool operator <(const Card& c1, const Card& c2)
{
    return lessSort(c1,c2);
}
