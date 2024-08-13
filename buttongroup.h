#ifndef BUTTONGROUP_H
#define BUTTONGROUP_H

#include <QWidget>
#include <QPushButton>

namespace Ui {
class ButtonGroup;
}

class ButtonGroup : public QWidget
{
    Q_OBJECT

public:
    enum Panel{Start, PlayCard, PassOrPlay, CallLord, Empty};
    explicit ButtonGroup(QWidget *parent = nullptr);
    ~ButtonGroup();

    // 初始化按钮
    void initButtons();

    // 处理page页的切换
    void selectPanel(Panel type, int bet = 0);

signals:
    void startGame();
    void playHand();
    void pass();
    void betPoint(int bet);

private:
    Ui::ButtonGroup *ui;
};

#endif // BUTTONGROUP_H
