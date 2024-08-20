#include "cardpanel.h"

#include <QMouseEvent>
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
    this->m_isfront = flag;
}

bool CardPanel::getFront()
{
    return this->m_isfront;
}

void CardPanel::setSelected(bool flag)
{
    this->m_isSelect = flag;
}

bool CardPanel::getSelected()
{
    return this->m_isSelect;
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
    this->m_owner = player;
}

Player *CardPanel::getPlayer()
{
    return this->m_owner;
}

void CardPanel::clicked()
{
    emit cardSelected(Qt::LeftButton);
}

void CardPanel::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter p(this);
    if(m_isfront)
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
    emit cardSelected(event->button());
}



