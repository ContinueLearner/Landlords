#include "cards.h"
#include <QRandomGenerator>
#include <QDebug>

Cards::Cards()
{

}

void Cards::add(const Card &card)
{
    m_cards.insert(card);
}

void Cards::add(const Cards &cards)
{
    m_cards.unite(cards.m_cards);
}

void Cards::add(const QVector<Cards> &cards)
{
    for(int i=0; i<cards.count(); ++i)
    {
        add(cards.at(i));
    }
}

Cards &Cards::operator <<(const Card &card)
{
    add(card);
    return *this;
}

Cards &Cards::operator <<(const Cards &cards)
{
    add(cards);
    return *this;
}

void Cards::remove(const Card &card)
{
    m_cards.remove(card);
}

void Cards::remove(const Cards &cards)
{
    m_cards.subtract(cards.m_cards);
}

void Cards::remove(const QVector<Cards> &cards)
{
    for(int i=0; i<cards.size(); ++i)
    {
        remove(cards.at(i));
    }
}

int Cards::cardCount()
{
    return m_cards.size();
}

bool Cards::isEmpty()
{
    return m_cards.isEmpty();
}

void Cards::clear()
{
    m_cards.clear();
}

Card::CardPoint Cards::maxPoint()
{
    Card::CardPoint max = Card::Point_Begin;
    if(!m_cards.isEmpty())
    {
        for(auto point:this->m_cards)
        {
            if(point.getPoint() > max)max = point.getPoint();
        }
    }
    return max;
}

Card::CardPoint Cards::minPoint()
{
    Card::CardPoint min = Card::Point_End;
    if(!m_cards.isEmpty())
    {
        for(auto point:this->m_cards)
        {
            if(point.getPoint() < min)min = point.getPoint();
        }
    }
    return min;
}

int Cards::pointCount(Card::CardPoint point)
{
    int count = 0;
    for(auto _point:this->m_cards)
    {
        if(_point.getPoint() == point)count++;
    }
    return count;
}


bool Cards::contains(const Card &card)
{
    return this->m_cards.contains(card);
}

bool Cards::contains(const Cards &cards)
{
    return this->m_cards.contains(cards.m_cards);
}

Card Cards::takeRandomCard()
{
    int num = QRandomGenerator::global()->bounded(this->m_cards.size());
    QSet<Card>::const_iterator it = m_cards.constBegin();
    for(int i = 0;i<num;i++,it++);
    Card card = *it;
    m_cards.erase(it);
    return card;
}

CardList Cards::toCardList(SortType type)
{
    CardList list;
    for(auto point:this->m_cards)
    {
        list<<point;
    }
    if(type == Asc)
    {
        std::sort(list.begin(),list.end(),lessSort);
    }
    else if(type == Desc)
    {
        std::sort(list.begin(),list.end(),greaterSort);
    }
}

void Cards::printAllCardInfo()
{

}