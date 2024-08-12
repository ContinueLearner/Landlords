#ifndef GAMECONTROL_H
#define GAMECONTROL_H

#include <QObject>
#include "robot.h"
#include "userplayer.h"
#include "cards.h"

class GameControl : public QObject
{
    Q_OBJECT
public:
    // 游戏状态
    enum GameStatus
    {
        DispatchCard,
        CallingLord,
        PlayingHand
    };
    // 玩家状态
    enum PlayerStatus
    {
        ThinkingForCallLord,
        ThinkingForPlayHand,
        Winning
    };

    explicit GameControl(QObject *parent = nullptr);

    // 初始化玩家
    void playerInit();

    // 得到玩家的实例对象
    Robot* getLeftRobot();
    Robot* getRightRobot();
    UserPlayer* getUserPlayer();

    void setCurrentPlayer(Player* player);
    Player* getCurrentPlayer();

    // 得到出牌玩家和打出的牌
    Player* getPendPlayer();
    Cards getPendCards();

    // 初始化扑克牌
    void initAllCards();
    // 每次发一张牌
    Card takeOneCard();
    // 得到最后的三张底牌
    Cards getSurplusCards();
    // 重置卡牌数据
    void resetCardData();

    // 准备叫地主
    void startLordCard();
    // 成为地主

    // 清空所有玩家的得分
    void clearPlayerScore();
    // 得到玩家下注的最高分数


    // 处理叫地主


    // 处理出牌



private:
    Robot* m_robotLeft = nullptr;
    Robot* m_robotRight = nullptr;
    UserPlayer* m_user = nullptr;
    Player* m_currPlayer = nullptr;
    Player* m_pendPlayer = nullptr;
    Cards m_pendCards;
    Cards m_allCards;

};

#endif // GAMECONTROL_H
