#include "cardpanel.h"

#include <QPainter>

CardPanel::CardPanel(QWidget *parent)
    : QWidget{parent}
{}

void CardPanel::setQPixmap(QPixmap front, QPixmap back)
{
    m_front = front;
    m_back = back;

    setFixedSize(m_front.size());

    update();

}

QPixmap CardPanel::getQPixmap()
{
    return m_front;
}

void CardPanel::setFront(bool flag)
{
    this->isFront = flag;
}

bool CardPanel::getFront()
{
    return this->isFront;
}

void CardPanel::setSelected(bool flag)
{
    this->isSelected = flag;
}

bool CardPanel::getSelected()
{
    return this->isSelected;
}

void CardPanel::setCard(Card &card)
{
    this->m_card = card;
}

Card CardPanel::getCard()
{
    return this->m_card;
}

void CardPanel::setPlayer(Player *player)
{
    this->player = player;
}

Player *CardPanel::getPlayer()
{
    return this->player;
}

void CardPanel::paintEvent(QPaintEvent *event)
{
    QPainter p(this);
    if(isFront)
    {
        p.drawPixmap(rect(),this->m_front);
    }
    else
    {
        p.drawPixmap(rect(),this->m_back);
    }
}

void CardPanel::mousePressEvent(QMouseEvent *event)
{

}



