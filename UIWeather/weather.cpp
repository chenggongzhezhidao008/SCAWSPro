#include "weather.h"

Weather::Weather(QObject *parent) :
    QObject(parent)
{
    initStartValue();
}
void Weather::setRunFlag(int flag)
{
    this->m_flag = flag;
}

void Weather::setAirportId(int airportId)
{
    this->m_airportId = airportId;
}

void Weather::setRunWayId(int runwayId)
{
    this->m_runwayId = runwayId;
}

void Weather::setweatherId(int weatherId)
{
    this->m_weatherId = weatherId;
}

void Weather::setRunwayName(QString runWayName)
{
    this->m_runWayStr = runWayName;
}

void Weather::setRunwayUsed(QString usedStr)
{
    this->m_usedStr = usedStr;
}

void Weather::setLocation(QString loca)
{
    this->m_location = loca;
}

void Weather::setweatherValue(QString weather)
{
    this->m_weatherValue = weather;
}

void Weather::initStartValue()
{
    this->m_weatherValue  = "Notdata";
}

void Weather::initLocation()
{
    m_location = "NULL";
}
