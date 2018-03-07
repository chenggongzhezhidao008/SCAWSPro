#include "installcfg.h"

InstallCFG::InstallCFG(QWidget *parent) :
    QWidget(parent)
{
    initInstallTabWidget();
    setShapeInstallTabWidget();
    setLocationInstallTabWidget();
    initWidgetsObj();
    init36selfCfgConnetion();
    initAirportCfgConnection();
    initSensorCFGConnection();
    initTestCFgConnection();
    initCFGoptionSingnalConnection();
    addIstallTab();
}

void InstallCFG::paintEvent(QPaintEvent *e)
{
    Q_UNUSED(e)
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing,true);
    painter.translate(width()/2,height()/2);
    int pWith = width();
    int pHeight = height();
    int left = - pWith / 2;
    int top = - pHeight / 2;
    if(paintWidth != pWith && paintHeght != pHeight){
        paintWidth = pWith;
        paintHeght = pHeight;
        setTabWidgetGeomerty();
    }
    painter.setPen(Qt::NoPen);

    //画区域背景
    painter.save();
    painter.setBrush(Qt::white);
    painter.drawRoundedRect(left,top,pWith - 2,pHeight - 2,3,3);
    painter.setBrush(Qt::gray);
    painter.drawRoundedRect(left + 2,top + 2,pWith - 2,
                            pHeight - 2,3,3);
    painter.setBrush(QColor("#D9D9D9"));
    painter.drawRoundedRect(left + 2,top + 2,pWith - 4,
                            pHeight - 4,3,3);
    painter.restore();
}

void InstallCFG::initInstallTabWidget()
{
    installTabWidget =  new QTabWidget(this);
}

void InstallCFG::setShapeInstallTabWidget()
{
    installTabWidget->setTabShape(QTabWidget::Triangular);
}

void InstallCFG::setLocationInstallTabWidget()
{
    installTabWidget->setTabPosition(QTabWidget::North);
}

void InstallCFG::addIstallTab()
{
    if(w_airport && w_testPort && w_3616 && w_sensor){
        installTabWidget->addTab(w_airport,"机场");
        installTabWidget->addTab(w_3616,"3616");
        installTabWidget->addTab(w_sensor,"SenSor");
        installTabWidget->addTab(w_testPort,"测试端口");
    }
}

void InstallCFG::setTabWidgetGeomerty()
{
    installTabWidget->setGeometry(4,4,width()- 8,height() - 4);
}

void InstallCFG::initSizeValue()
{
    paintWidth = 0;
    paintHeght = 0;
}

void InstallCFG::initWidgetsObj()
{
    w_airport = new AirportCFGCom(this);
    w_3616 = new Unit3616CFGCom(this);
    w_sensor = new SensorCFGCom(this);
    w_testPort = new TestPortCFGCom(this);
}

void InstallCFG::initAirportCfgConnection()
{
    if(w_airport){
        connect(this,SIGNAL(backAirInfoSignal(SensorMap)),w_airport,SLOT(backAirInfoSlot(SensorMap)));
        connect(this,SIGNAL(backRunwayInfoSignal(SensorMap)),w_airport,SLOT(backRunwayInfoSlot(SensorMap)));
        connect(this,SIGNAL(backMatchInfoSignal(SensorMap)),w_airport,SLOT(backMatchInfoSlot(SensorMap)));
    }
}

void InstallCFG::init36selfCfgConnetion()
{
    if(w_3616){
        connect(this,SIGNAL(Configure3616Signal(SensorMap))
                ,w_3616,SLOT(Configure3616Slot(SensorMap)));
        connect(this,SIGNAL(sensorStatusSignal(SensorMap))
                ,w_3616,SLOT(sensorStatusSlot(SensorMap)));
        connect(this,SIGNAL(sensorLIBsSignal(SensorMap))
                ,w_3616,SLOT(sensorLIBsSlot(SensorMap)));
        connect(this,SIGNAL(serialCardParamersSignal(SensorMap))
                ,w_3616,SLOT(serialCardParamersSlot(SensorMap)));
        connect(this,SIGNAL(AFFIX9NewMessageSendUp(QString,InforData))
                ,w_3616,SLOT(AFFIX9NewMessageSendUp(QString,InforData)));
    }
}

void InstallCFG::initSensorCFGConnection()
{
    if(w_sensor){
        connect(this,SIGNAL(backRequeryAFFIX9menberSignal(QString,InforData))
                ,w_sensor,SLOT(backRequeryAFFIX9menberSlot(QString,InforData)));
        connect(this,SIGNAL(ExternSensorInfoListSignale(SensorMap))
                ,w_sensor,SLOT(externSensorDealList(SensorMap)));
    }
}

void InstallCFG::initTestCFgConnection()
{
    if(w_testPort){
        connect(this,SIGNAL(backAirInfoSignal(SensorMap)),w_testPort,SLOT(backAirInfoSlot(SensorMap)));
        connect(this,SIGNAL(backRunwayInfoSignal(SensorMap)),w_testPort,SLOT(backRunwayInfoSlot(SensorMap)));
        connect(this,SIGNAL(backMatchInfoSignal(SensorMap)),w_testPort,SLOT(backMatchInfoSlot(SensorMap)));
    }
}

/*  ----------------------
 *  function description
 *  系统部分中的设备配置部分
 *  的所有用户操作信号和链接。
 *  ----------------------
 */
void InstallCFG::initCFGoptionSingnalConnection()
{
    if(w_airport
            &&w_3616
            &&w_sensor
            &&w_testPort)
    {
        connect(w_airport,SIGNAL(MenuOptionSlot(QString))
                ,SIGNAL(CFGOptions(QString)));
        connect(w_3616,SIGNAL(MenuOptionSlot(QString))
                ,SIGNAL(CFGOptions(QString)));
        connect(w_sensor,SIGNAL(MenuOptionSlot(QString))
                ,SIGNAL(CFGOptions(QString)));
        connect(w_testPort,SIGNAL(MenuOptionSlot(QString))
                ,SIGNAL(CFGOptions(QString)));
    }
}


