#include "gamepanel.h"
#include "ui_gamepanel.h"

#include <QRandomGenerator>

GamePanel::GamePanel(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::GamePanel)
{
    ui->setupUi(this);

    //1.设置背景图
    int num = QRandomGenerator::global()->bounded(10);
    QString path = QString(":/images/background-%1.png").arg(num+1);
    m_bkImage.load(path);

    //2.设置标题和大小
    this->setWindowTitle("欢乐斗地主");
    this->setFixedSize(1000,650);
    // 3. 实例化游戏控制类对象
    gameControlInit();

    // 4. 玩家得分(更新)
    updatePlayerScore();

    // 5. 切割游戏图片
    initCardMap();

    // 6. 初始化游戏中的按钮组
    initButtonsGroup();

    // 7. 初始化玩家在窗口中的上下文环境
    initPlayerContext();

    // 8. 扑克牌场景初始化
    initGameScene();
}

GamePanel::~GamePanel()
{
    delete ui;
}

void GamePanel::gameControlInit()
{
    m_gameCtl = new GameControl(this);
    m_gameCtl->playerInit();

    Robot* leftRobot = m_gameCtl->getLeftRobot();
    Robot* rightRobot = m_gameCtl->getRightRobot();
    UserPlayer* user = m_gameCtl->getUserPlayer();
    m_playerList << leftRobot << rightRobot << user;

}

void GamePanel::updatePlayerScore()
{
    ui->scorePanel->setScores( m_playerList[0]->getScore(),
                              m_playerList[1]->getScore(),
                              m_playerList[2]->getScore());
}

void GamePanel::initCardMap()
{
    // 1. 加载大图
    QPixmap pixmap(":/images/card.png");
    // 2. 计算每张图片大小
    m_cardSize.setWidth(pixmap.width() / 13);
    m_cardSize.setHeight(pixmap.height() / 5);

    // 3. 背景图
    m_cardBackImg = pixmap.copy(2*m_cardSize.width(), 4*m_cardSize.height(),
                                m_cardSize.width(), m_cardSize.height());
    // 正常花色
    for(int i=0, suit=Card::Suit_Begin+1; suit<Card::Suit_End; ++suit, ++i)
    {
        for(int j=0, pt=Card::Point_Begin+1; pt<Card::Point_SJ; ++pt, ++j)
        {
            Card card((Card::CardPoint)pt, (Card::CardSuit)suit);
            // 裁剪图片
            cropImage(pixmap, j*m_cardSize.width(), i*m_cardSize.height(), card);
        }
    }
    // 大小王
    Card c;
    c.setPoint(Card::Point_SJ);
    c.setSuit(Card::Suit_Begin);
    cropImage(pixmap, 0, 4*m_cardSize.height(), c);

    c.setPoint(Card::Point_BJ);
    cropImage(pixmap, m_cardSize.width(), 4*m_cardSize.height(), c);
}

void GamePanel::cropImage(QPixmap &pix, int x, int y, Card &c)
{
    QPixmap sub = pix.copy(x, y, m_cardSize.width(), m_cardSize.height());
    CardPanel* panel = new CardPanel(this);
    panel->setQPixmap(sub, m_cardBackImg);
    panel->setCard(c);
    panel->hide();
    m_cardMap.insert(c, panel);
}

void GamePanel::initButtonsGroup()
{
    ui->btnGroup->initButtons();
    ui->btnGroup->selectPanel(ButtonGroup::Start);

    connect(ui->btnGroup, &ButtonGroup::startGame, this, [=](){});
    connect(ui->btnGroup, &ButtonGroup::playHand, this, [=](){});
    connect(ui->btnGroup, &ButtonGroup::pass, this, [=](){});
    connect(ui->btnGroup, &ButtonGroup::betPoint, this, [=](){});
}

void GamePanel::initPlayerContext()
{
    // 1. 放置玩家扑克牌的区域
    const QRect cardsRect[] =
        {
            // x, y, width, height
            QRect(90, 130, 100, height() - 200),                    // 左侧机器人
            QRect(rect().right() - 190, 130, 100, height() - 200),  // 右侧机器人
            QRect(250, rect().bottom() - 120, width() - 500, 100)   // 当前玩家
        };
    const QRect playHandRect[] =
        {
            QRect(260, 150, 100, 100),                              // 左侧机器人
            QRect(rect().right() - 360, 150, 100, 100),             // 右侧机器人
            QRect(150, rect().bottom() - 290, width() - 300, 105)   // 当前玩家
        };
    const QPoint roleImgPos[] =
        {
            QPoint(cardsRect[0].left()-80, cardsRect[0].height() / 2 + 20),     // 左侧机器人
            QPoint(cardsRect[1].right()+10, cardsRect[1].height() / 2 + 20),    // 右侧机器人
            QPoint(cardsRect[2].right()-10, cardsRect[2].top() - 10)            // 当前玩家
        };

    // 循环
    int index = m_playerList.indexOf(m_gameCtl->getUserPlayer());
    for(int i=0; i<m_playerList.size(); ++i)
    {
        PlayerContext context;
        context.align = i==index ? Horizontal : Vertical;
        context.isFrontSide = i==index ? true : false;
        context.cardRect = cardsRect[i];
        context.playHandRect = playHandRect[i];
        // 提示信息
        context.info = new QLabel(this);
        context.info->resize(160, 98);
        context.info->hide();
        // 显示到出牌区域的中心位置
        QRect rect = playHandRect[i];
        QPoint pt(rect.left() + (rect.width() - context.info->width()) / 2,
                  rect.top() + (rect.height() - context.info->height()) / 2);
        context.info->move(pt);
        // 玩家的头像
        context.roleImg = new QLabel(this);
        context.roleImg->resize(84, 120);
        context.roleImg->hide();
        context.roleImg->move(roleImgPos[i]);
        m_contextMap.insert(m_playerList.at(i), context);
    }
}

void GamePanel::initGameScene()
{
    // 1. 发牌区的扑克牌
    m_baseCard = new CardPanel(this);
    m_baseCard->setQPixmap(m_cardBackImg, m_cardBackImg);
    // 2. 发牌过程中移动的扑克牌
    m_moveCard = new CardPanel(this);
    m_moveCard->setQPixmap(m_cardBackImg, m_cardBackImg);
    // 3. 最后的三张底牌(用于窗口的显示)
    for(int i=0; i<3; ++i)
    {
        CardPanel* panel = new CardPanel(this);
        panel->setQPixmap(m_cardBackImg, m_cardBackImg);
        m_last3Card.push_back(panel);
        panel->hide();
    }
    // 扑克牌的位置
    m_baseCardPos = QPoint((width() - m_cardSize.width()) / 2,
                           height() / 2 - 100);
    m_baseCard->move(m_baseCardPos);
    m_moveCard->move(m_baseCardPos);

    int base = (width() - 3 * m_cardSize.width() - 2 * 10) / 2;
    for(int i=0; i<3; ++i)
    {
        m_last3Card[i]->move(base + (m_cardSize.width() + 10) * i, 20);
    }
}

void GamePanel::paintEvent(QPaintEvent *ev)
{
    QPainter p(this);
    p.drawPixmap(rect(),m_bkImage);
}


