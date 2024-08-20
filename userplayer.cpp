#include "userplayer.h"

UserPlayer::UserPlayer(QObject *parent)
    : Player{parent}
{
    this->m_type = Type::User;
}

void UserPlayer::prepareCallLord()
{

}

void UserPlayer::preparePlayHand()
{
    emit startCountDown();
}
