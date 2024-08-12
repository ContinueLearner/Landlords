#include "robot.h"

Robot::Robot(QObject *parent)
    : Player{parent}
{
    this->m_type = Type::Robot;
}

void Robot::prepareCallLord()
{

}

void Robot::preparePlayHand()
{

}
