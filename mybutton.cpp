#include "mybutton.h"

#include <QMouseEvent>
#include <QPainter>

MyButton::MyButton(QWidget *parent)
    : QPushButton{parent}
{}

void MyButton::setImage(QString normal, QString hover, QString pressed)
{
    this->m_normal = normal;
    this->m_hover = hover;
    this->m_pressed = pressed;
    m_pixmap.load(normal);
    update();
}

void MyButton::mousePressEvent(QMouseEvent *ev)
{
    if(ev->button() == Qt::LeftButton)
    {
        m_pixmap.load(m_pressed);
        update();
    }
    QPushButton::mousePressEvent(ev);
}

void MyButton::mouseReleaseEvent(QMouseEvent *ev)
{
    if(ev->button() == Qt::LeftButton)
    {
        m_pixmap.load(m_normal);
        update();
    }
    QPushButton::mouseReleaseEvent(ev);
}

void MyButton::enterEvent(QEvent *ev)
{
    m_pixmap.load(m_hover);
    update();
}

void MyButton::leaveEvent(QEvent *ev)
{
    m_pixmap.load(m_normal);
}

void MyButton::paintEvent(QPaintEvent *ev)
{
    QPainter p(this);
    p.drawPixmap(rect(),m_pixmap);
}
