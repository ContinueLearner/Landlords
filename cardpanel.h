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

    // 模拟扑克牌的点击事件
    void clicked();

protected:
    void paintEvent(QPaintEvent * event);
    void mousePressEvent(QMouseEvent *event);


signals:
    void cardSelected(Qt::MouseButton button);

private:
    QPixmap m_front;
    QPixmap m_back;

    bool m_isfront = true;
    bool m_isSelect = false;
    Card m_card;
    Player* m_owner = nullptr;
signals:
};

#endif // CARDPANEL_H
