#include "card.h"

void Card::setSuit(CardSuit s)
{
    this->suit = s;
}

void Card::setPoint(CardPoint p)
{
    this->point = p;
}

Card::CardSuit Card::getSuit()
{
    return this->suit;
}

Card::CardPoint Card::getPoint()
{
    return this->point;
}

Card::Card() {}
