#include "press.h"

Press::Press(QObject *parent) :
    QObject(parent)
{
    initStartValue();
}

void Press::setRunFlag(int flag)
{
    this->m_flag = flag;
}

void Press::setAirportId(int airportId)
{
    this->m_airportId = airportId;
}

void Press::setRunWayId(int runwayId)
{
    this->m_runwayId = runwayId;
}

void Press::setPressId(int pressId)
{
    this->m_pressId = pressId;
}

void Press::setRunwayName(QString runWayName)
{
    this->m_runWayStr = runWayName;
}

void Press::setRunwayUsed(QString usedStr)
{
    this->m_usedStr = usedStr;
}

void Press::setLocation(QString loca)
{
    this->m_location = loca;
}

void Press::setPressValue(QString press)
{
    this->m_PressValue = press;
}

void Press::initStartValue()
{
    this->m_PressValue  = "Notdata";
}

void Press::initLocation()
{
    m_location = "NULL";
}
