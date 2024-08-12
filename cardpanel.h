#ifndef CARDPANEL_H
#define CARDPANEL_H

#include "card.h"
#include "player.h"

#include <QWidget>

class CardPanel : public QWidget
{
    Q_OBJECT
public:
    explicit CardPanel(QWidget *parent = nullptr);

    void setQPixmap(QPixmap front,QPixmap back);
    QPixmap getQPixmap();

    void setFront(bool flag);
    bool getFront();

    void setSelected(bool flag);
    bool getSelected();

    void setCard(Card& card);
    Card getCard();

    void setPlayer(Player* player);
    Player* getPlayer();

protected:
    void paintEvent(QPaintEvent * event);
    void mousePressEvent(QMouseEvent *event);

private:
    QPixmap m_front;
    QPixmap m_back;

    bool isFront;
    bool isSelected;

    Card m_card;

    Player* player;
signals:
};

#endif // CARDPANEL_H
