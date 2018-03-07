#include "awossensorcloud.h"

AwosSensorCloud::AwosSensorCloud(QWidget *parent) :
    QWidget(parent)
{
    m_runwayId = 06;
    initCloudHeight();
    initLocation();
}
void AwosSensorCloud::setRunFlag(int flag)
{
    this->m_flag = flag;
}

void AwosSensorCloud::setAirportId(int airportId)
{
    this->m_airportId = airportId;
}

void AwosSensorCloud::setRunWayId(int runwayId)
{
    this->m_runwayId = runwayId;
}

void AwosSensorCloud::setCloudId(int cloudId)
{
    this->m_cloudId = cloudId;
}

void AwosSensorCloud::setRunwayName(QString runWayName)
{
    this->m_runWayStr = runWayName;
}

void AwosSensorCloud::setRunwayUsed(QString usedStr)
{
    this->m_usedStr = usedStr;
}

void AwosSensorCloud::setFirstlay(QString firstlay)
{
    if(firstlay == "///"){
        this->m_firstlay = "NCD";
    }
    else{
        this->m_firstlay = firstlay;
    }
    update();
}

void AwosSensorCloud::setSecondlay(QString secondlay)
{
    if(secondlay == "///"){
        this->m_secondlay = "NCD";
    }
    else{
        this-> m_secondlay = secondlay;
    }
    update();
}

void AwosSensorCloud::setThirdlay(QString thirdlay)
{
    if(thirdlay == "///"){
        this->m_thirdlay = "NCD";
    }
    else{
        this-> m_thirdlay = thirdlay;
    }
    update();
}

void AwosSensorCloud::setLocation(QString loca)
{
    this->m_location = loca;
}




