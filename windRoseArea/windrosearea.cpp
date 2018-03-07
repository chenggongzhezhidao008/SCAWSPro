#include "windrosearea.h"

WindRoseArea::WindRoseArea(QWidget *parent) :
    QWidget(parent)
{
    m_runWayStr = "R04跑道";
    initAllContrls();
    m_tempAngle = 0;
    windAnimation = NULL;
    setInitValue();
    initZeroTimer();
    initLocation();
}

void WindRoseArea::setEnablecloudCtl(bool openFlag)
{
    if(m_CloudBase){
        m_CloudBase->setEnable(false);
    }
}

void WindRoseArea::showSubContrl()
{
    int thisWidth = width() - 16;
    int thisHeigh = height();
    int lableWidth = (thisWidth - 4) / 2 - 56;
    int lableHeigh = (thisHeigh - 14) / 4 - 3;
    m_mor->setGeometry(20,14 + (thisHeigh - 14) * 0 / 4,lableWidth,lableHeigh);
    m_mor->setDataName("跑道视程");
    m_mor->setUnitString("m");
    m_mor->setTimestring("");
    m_mor->setFontSize(24);
    m_mor->show();
    m_rvr->setGeometry(20,14 + (thisHeigh - 14) * 1 / 4,lableWidth,lableHeigh);
    m_rvr->setDataName("能见度值");
    m_rvr->setUnitString("m");
    m_rvr->setTimestring("");
    m_rvr->setFontSize(24);
    m_rvr->show();
    m_CloudBase->setGeometry(20,14 + (thisHeigh - 14) * 2 / 4,lableWidth,lableHeigh);
    m_CloudBase->setDataName("云底高度");
    m_CloudBase->setUnitString("m");
    m_CloudBase->setTimestring("");
    m_CloudBase->setFontSize(24);
    m_CloudBase->show();
    m_gust->setGeometry(20,14 + (thisHeigh - 14) * 3 / 4,lableWidth,lableHeigh);
    m_gust->setDataName("阵风");
    m_gust->setUnitString("m/s");
    m_gust->setTimestring("");
    m_gust->setFontSize(24);
    m_gust->show();
    int minValue = qMin((thisWidth - 4) / 2 + 20 + 4,thisHeigh - 20);
    m_wind->setGeometry((thisWidth - 4) * 3 / 4 - 14 - minValue / 2,
                        (thisHeigh - 20) / 2 + 18 - minValue / 2 - 4,minValue + 4,minValue);
    m_wind->show();
}

void WindRoseArea::setRunFlag(int flag)
{
    this->m_flag = flag;
}

void WindRoseArea::setAirportId(int airportId)
{
    this->m_airportId = airportId;
}

void WindRoseArea::setRunWayId(int runwayId)
{
    this->m_runwayId = runwayId;
}

void WindRoseArea::setWindId(int windId)
{
    this->m_windId = windId;
}

void WindRoseArea::setVisId(int visId)
{
    this->m_visId = visId;
}

void WindRoseArea::setCloudId(int cloudId)
{
    this->m_cloudId = cloudId;
}

void WindRoseArea::setRunwayName(QString runWayName)
{
    this->m_runWayStr = runWayName;
    update();
    if(m_wind){
        m_wind->setRunUpAngle(m_runWayStr);
    }
}

void WindRoseArea::setRunwayUsed(QString usedStr)
{
    this->m_usedStr = usedStr;
}

void WindRoseArea::setCurrentWindSpeed(QString currentSpeed)
{
    this->m_currentSpeed = currentSpeed;
    if(m_wind){
        m_wind->setWindCurrentSpeed(m_currentSpeed);
    }
}

void WindRoseArea::setCurrentWindAngle(int currentAngle)
{
    this->m_currentAngle = currentAngle;
    if(m_wind){
        m_wind->setWindCurrentAngle(m_currentAngle);
    }
}

void WindRoseArea::setTenWindMinAngle(int tenMinAngle)
{
    this->m_tenMinAngle = tenMinAngle;
    if(m_wind){
        m_wind->setTenWindMinAngle(m_tenMinAngle);
    }
}

void WindRoseArea::setTenWindMaxAngle(int tenMaxAngle)
{
    this->m_tenMaxAngle = tenMaxAngle;
    if(m_wind){
        m_wind->setTenWindMaxAngle(m_tenMaxAngle);
    }
}

void WindRoseArea::setWindPointAngle(int pointAngle)
{
    this->m_pointAngle = pointAngle;
    if(m_wind){
        if(!windAnimation){
            windAnimation = new QPropertyAnimation(m_wind,"twoWindAvAngle");
            windAnimation->setDuration(500);
        }
        windAnimation->setStartValue(m_tempAngle);
        windAnimation->setEndValue(m_pointAngle);
        windAnimation->start();
        m_tempAngle = m_pointAngle;
    }
}

void WindRoseArea::setZfeng10(QString speed)
{
    if(speed == "11111.111"){
        this->m_zfeng10 = "";
    }
    else{
        this->m_zfeng10 = speed;
    }
    if(m_gust){
        m_gust->setShowContext(m_zfeng10);
    }
}

void WindRoseArea::setMorValue(QString mor)
{
    m_morValue = mor.split(".").value(0).trimmed();
    if(m_mor)
    {
        m_mor->setShowContext(m_morValue);
    }
    setp = 0;
}

void WindRoseArea::setRvrValue(QString rvr)
{
    m_rvrValue = rvr.split(".").value(0).trimmed();
    if(m_rvr)
    {
        m_rvr->setShowContext(m_rvrValue);
    }
    setp = 0;
}
void WindRoseArea::setCLDBaseHight(QString cloudHight)
{
    QString value;
    value = cloudHight.split(".").value(0).trimmed();
    this->m_CloudBhight = value;
    if(m_CloudBase){
        m_CloudBase->setShowContext(m_CloudBhight);
    }
}

void WindRoseArea::setMorMax(int mor)
{
    m_morMax = mor;
}

void WindRoseArea::setRvrMax(int rvr)
{
    m_rvrMax = rvr;
}

void WindRoseArea::setMorMin(int mor)
{
    m_morMin = mor;
}

void WindRoseArea::setRvrMin(int rvr)
{
    m_rvrMin = rvr;
}

void WindRoseArea::setWaringBool(WaringTepy waring)
{
    QStringList m_key = m_waringBool.keys();
    QStringList key = waring.keys();
    bool finded = false;
    for(int i = 0; i < m_key.length(); i++){
        if(m_key.value(i) == key.value(0)){
            finded = true;
            m_waringBool[m_key.value(i)] = waring[key.value(0)];
        }
    }
    if(!finded){
        m_waringBool[key.value(0)] = waring[key.value(0)];
    }
    m_key.clear();
    m_key = m_waringBool.keys();
    for(int j = 0; j < m_key.length(); j++){
        if(m_key.value(j) == "rvr"){
            if(m_waringBool[m_key.value(j)] == true){
                m_mor->setWaring(true);
            }
            else{
                m_mor->setWaring(false);
            }
        }
        if(m_key.value(j) == "mor"){
            if(m_waringBool[m_key.value(j)] == true){
                m_rvr->setWaring(true);
            }
            else{
                m_rvr->setWaring(false);
            }
        }
    }
}

void WindRoseArea::setLocation(QString loca)
{
    this->m_location = loca;
}


bool WindRoseArea::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::MouseButtonPress || event->type() == QEvent::MouseMove) {
        event->accept();
        return true;
    }
    else{
        return QWidget::eventFilter(obj, event);
    }
}

void WindRoseArea::setZeroData()
{
    if(setp > 20)
    {
        setp = 0; //qDebug()<<"update vis wind data area";
        if(m_mor){
            if(m_morValue != "///") m_mor->setShowContext("NDATA");
        }
        if(m_rvr){
            if(m_rvrValue != "///") m_rvr->setShowContext("NDATA");
        }
    }
    setp++;
}

void WindRoseArea::initAllContrls()
{
    m_rvr = new RvrSensorUot(this);
    m_rvr->installEventFilter(this);
    m_mor = new RvrSensorUot(this);
    m_mor->installEventFilter(this);
    m_CloudBase = new RvrSensorUot(this);
    m_CloudBase->installEventFilter(this);
    m_gust = new RvrSensorUot(this);
    m_gust->installEventFilter(this);
    m_wind = new WindMeter(this);
    m_wind->installEventFilter(this);
    m_updateSubContrl = false;
}

void WindRoseArea::setInitValue()
{
    m_morValue = "///";
    m_rvrValue = "///";
    m_CloudBhight = "///";
}

void WindRoseArea::initZeroTimer()
{
    zeroTimer = new QTimer(this);
    connect(zeroTimer,SIGNAL(timeout())
            ,SLOT(setZeroData()));
    zeroTimer->start(1000);
    setp = 0;
}

void WindRoseArea::initLocation()
{
    m_location = "NULL";
}
