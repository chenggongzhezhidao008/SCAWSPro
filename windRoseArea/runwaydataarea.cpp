#include "runwaydataarea.h"

RunWayDataArea::RunWayDataArea(QWidget *parent) :
    QWidget(parent)
{

    m_temp       = new RvrSensorUot(this);
    m_hum        = new RvrSensorUot(this);
    m_dew        = new RvrSensorUot(this);
    m_rain       = new RvrSensorUot(this);
    m_TNoneSpeed = new RvrSensorUot(this);
    m_TNoneAngle = new RvrSensorUot(this);
    m_TNtenSpeed = new RvrSensorUot(this);
    m_TNtenAngle = new RvrSensorUot(this);
    m_MNoneSpeed = new RvrSensorUot(this);
    m_MNoneAngle = new RvrSensorUot(this);
    m_MNtenSpeed = new RvrSensorUot(this);
    m_MNtenAngle = new RvrSensorUot(this);

    m_temp->installEventFilter(this);
    m_hum->installEventFilter(this);
    m_dew->installEventFilter(this);
    m_rain->installEventFilter(this);
    m_TNoneSpeed->installEventFilter(this);
    m_TNoneAngle->installEventFilter(this);
    m_TNtenSpeed->installEventFilter(this);
    m_TNtenAngle->installEventFilter(this);
    m_MNoneSpeed->installEventFilter(this);
    m_MNoneAngle->installEventFilter(this);
    m_MNtenSpeed->installEventFilter(this);
    m_MNtenAngle->installEventFilter(this);
    initZeroTimer();
    initLOcation();
}

bool RunWayDataArea::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::MouseButtonPress || event->type() == QEvent::MouseMove) {
        event->accept();
        return true;
    }
    else{
        return QWidget::eventFilter(obj, event);
    }
}

void RunWayDataArea::showSubContrl()
{
    m_temp->setDataName("温度");
    m_hum->setDataName("湿度");
    m_dew->setDataName("露点");
    m_rain->setDataName("雨");

    m_temp->setDataNameSize(13);
    m_hum->setDataNameSize(13);
    m_dew->setDataNameSize(13);
    m_rain->setDataNameSize(13);

    m_TNoneSpeed->setDataName("风速");
    m_TNoneAngle->setDataName("风向");
    m_TNtenSpeed->setDataName("风速");
    m_TNtenAngle->setDataName("风向");
    m_MNoneSpeed->setDataName("风速");
    m_MNoneAngle->setDataName("风向");
    m_MNtenSpeed->setDataName("风速");
    m_MNtenAngle->setDataName("风向");

    m_TNoneSpeed->setDataNameSize(13);
    m_TNoneAngle->setDataNameSize(13);
    m_TNtenSpeed->setDataNameSize(13);
    m_TNtenAngle->setDataNameSize(13);
    m_MNoneSpeed->setDataNameSize(13);
    m_MNoneAngle->setDataNameSize(13);
    m_MNtenSpeed->setDataNameSize(13);
    m_MNtenAngle->setDataNameSize(13);


    m_temp->setUnitString("℃");
    m_hum->setUnitString("％");
    m_dew->setUnitString("℃");
    m_rain->setUnitString("mm");

    m_TNoneSpeed->setUnitString("m/s");
    m_TNoneAngle->setUnitString("o");
    m_TNtenSpeed->setUnitString("m/s");
    m_TNtenAngle->setUnitString("o");
    m_MNoneSpeed->setUnitString("m/s");
    m_MNoneAngle->setUnitString("o");
    m_MNtenSpeed->setUnitString("m/s");
    m_MNtenAngle->setUnitString("o");

    m_temp->setTimestring("");
    m_hum->setTimestring("");
    m_dew->setTimestring("");
    m_rain->setTimestring("1h");
    m_TNoneSpeed->setTimestring("2m");
    m_TNoneAngle->setTimestring("2m");
    m_TNtenSpeed->setTimestring("10m");
    m_TNtenAngle->setTimestring("10m");

    m_MNoneSpeed->setTimestring("2m");
    m_MNoneAngle->setTimestring("2m");
    m_MNtenSpeed->setTimestring("10m");
    m_MNtenAngle->setTimestring("10m");

    m_rain->setTimeSize(12);

    m_MNtenAngle->setTimeSize(12);
    m_TNoneSpeed->setTimeSize(12);
    m_TNoneAngle->setTimeSize(12);
    m_TNtenSpeed->setTimeSize(12);
    m_TNtenAngle->setTimeSize(12);
    m_MNoneSpeed->setTimeSize(12);
    m_MNoneAngle->setTimeSize(12);
    m_MNtenSpeed->setTimeSize(12);
    m_MNtenAngle->setTimeSize(12);

    int areaBodyHeigh = (height() - 20) ;
    int areaBodyWidth = (width() - 4) - 12;
    int labelHeigh = areaBodyHeigh * 7 / 33;
    int labelWidth = areaBodyWidth / 3 - 10;

    m_temp->setGeometry(2 + 5,18 + areaBodyHeigh / 33,labelWidth,labelHeigh);
    m_hum->setGeometry(2 + 5,18 + areaBodyHeigh * 9 / 33,labelWidth,labelHeigh);
    m_dew->setGeometry(2 + 5,18 + areaBodyHeigh * 17 / 33,labelWidth,labelHeigh);
    m_rain->setGeometry(2 + 5,18 + areaBodyHeigh * 25 / 33,labelWidth,labelHeigh);

    m_TNoneSpeed->setGeometry(2 + areaBodyWidth / 3 + 5,18 + areaBodyHeigh / 33,labelWidth,labelHeigh);
    m_TNoneAngle->setGeometry(2 + areaBodyWidth / 3 + 5,18 + areaBodyHeigh * 9  / 33,labelWidth,labelHeigh);
    m_TNtenSpeed->setGeometry(2 + areaBodyWidth / 3 + 5,18 + areaBodyHeigh * 17 / 33,labelWidth,labelHeigh);
    m_TNtenAngle->setGeometry(2 + areaBodyWidth / 3 + 5,18 + areaBodyHeigh * 25 / 33,labelWidth,labelHeigh);

    m_MNoneSpeed->setGeometry(2 + areaBodyWidth * 2 / 3 + 5,18 + areaBodyHeigh / 33,labelWidth,labelHeigh);
    m_MNoneAngle->setGeometry(2 + areaBodyWidth * 2 / 3 + 5,18 + areaBodyHeigh * 9  / 33,labelWidth,labelHeigh);
    m_MNtenSpeed->setGeometry(2 + areaBodyWidth * 2 / 3 + 5,18 + areaBodyHeigh * 17 / 33,labelWidth,labelHeigh);
    m_MNtenAngle->setGeometry(2 + areaBodyWidth * 2 / 3 + 5,18 + areaBodyHeigh * 25 / 33,labelWidth,labelHeigh);

    m_TNoneSpeed->setFontSize(18);
    m_TNoneAngle->setFontSize(18);
    m_TNtenSpeed->setFontSize(18);
    m_TNtenAngle->setFontSize(18);

    m_MNoneSpeed->setFontSize(18);
    m_MNoneAngle->setFontSize(18);
    m_MNtenSpeed->setFontSize(18);
    m_MNtenAngle->setFontSize(18);

    m_temp->setFontSize(18);
    m_hum->setFontSize(18);
    m_dew->setFontSize(18);
    m_rain->setFontSize(18);

}

void RunWayDataArea::setRunFlag(int flag)
{
    this->m_flag = flag;
}

void RunWayDataArea::setAirportId(int airportId)
{
    this->m_airportId = airportId;
}

void RunWayDataArea::setRunWayId(int runwayId)
{
    this->m_runwayId = runwayId;
}

void RunWayDataArea::setWindId(int windId)
{
    this->m_windId = windId;
}

void RunWayDataArea::setHumitempId(int humitempId)
{
    this->m_humitempId = humitempId;
}

void RunWayDataArea::setRunwayName(QString runWayName)
{
    this->m_runWayStr = runWayName;
    update();
}

void RunWayDataArea::setRunwayUsed(QString usedStr)
{
    this->m_usedStr = usedStr;
}

void RunWayDataArea::setZOneSpeed(QString speed)
{
    m_zoneSpeed = speed;
    if(m_TNoneSpeed){
        m_TNoneSpeed->setShowContext(m_zoneSpeed);
    }
}

void RunWayDataArea::setZOneAngle(QString angle)
{
    m_zoneAngle  = angle;
    if(m_TNoneAngle){
        m_TNoneAngle->setShowContext(m_zoneAngle);
    }
}

void RunWayDataArea::setZTenSpeed(QString speed)
{
    m_ztenSpeed = speed;
    if(m_TNtenSpeed){
        m_TNtenSpeed->setShowContext(m_ztenSpeed);
    }
}

void RunWayDataArea::setZTenAngle(QString angle)
{
    m_ztenAngle = angle;
    if(m_TNtenAngle){
        m_TNtenAngle->setShowContext(m_ztenAngle);
    }
}

void RunWayDataArea::setCOneSpeed(QString speed)
{
    m_coneSpeed = speed;
    if(m_MNoneSpeed){
        m_MNoneSpeed->setShowContext(m_coneSpeed);
    }
}

void RunWayDataArea::setCOneAngle(QString angle)
{
    m_coneAngle = angle;
    if(m_MNoneAngle){
        m_MNoneAngle->setShowContext(m_coneAngle);
    }
}

void RunWayDataArea::setCTenSpeed(QString speed)
{
    m_ctenSpeed = speed;
    if(m_MNtenSpeed){
        m_MNtenSpeed->setShowContext(m_ctenSpeed);
    }
}

void RunWayDataArea::setCTenAngle(QString angle)
{
    m_ctenAngle = angle;
    if(m_MNtenAngle){
        m_MNtenAngle->setShowContext(m_ctenAngle);
    }
}

void RunWayDataArea::setTemp(QString temp)
{
    m_tempValue = temp;
    if(m_temp){
        m_temp->setShowContext(m_tempValue);
    }
}

void RunWayDataArea::setHumi(QString humi)
{
    m_humiValue = humi;
    if(m_hum){
        m_hum->setShowContext(m_humiValue);
    }
}

void RunWayDataArea::setDew(QString dew)
{
    m_dewValue = dew;
    if(m_dew){
        m_dew->setShowContext(m_dewValue);
    }
}

void RunWayDataArea::setRain(QString rain)
{
    m_rainValue = rain;
    if(m_rain){
        m_rain->setShowContext(m_rainValue);
    }
}

void RunWayDataArea::setZeroData()
{
    if(setp > 20){
       ;
    }
    setp++;
}

void RunWayDataArea::setLocation(QString loca)
{
    this->m_location = loca;
}

void RunWayDataArea::initZeroTimer()
{
//    zeroTimer = new QTimer(this);
//    connect(zeroTimer,SIGNAL(timeout())
//            ,SLOT(setZeroData()));
//    zeroTimer->start(1000);
    setp = 0;
}

void RunWayDataArea::initLOcation()
{
    m_location = "NULL";
}

