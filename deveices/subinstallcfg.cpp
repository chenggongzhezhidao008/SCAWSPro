#include "subinstallcfg.h"

SubInstallCFG::SubInstallCFG(QWidget *parent) :
    QWidget(parent)
{
    initInstallTabWidget();
    setShapeInstallTabWidget();
    setLocationInstallTabWidget();
    initWidgetsObj();
    init36selfCfgConnetion();
    initAirportCfgConnection();
    addIstallTab();
}

void SubInstallCFG::paintEvent(QPaintEvent *e)
{
    Q_UNUSED(e)
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing,true);
    painter.translate(width()/2,height()/2);
    int pWith = width();
    int pHeight = height();

    if(paintWidth != pWith && paintHeght != pHeight){
        paintWidth = pWith;
        paintHeght = pHeight;
        setTabWidgetGeomerty();
    }
}

void SubInstallCFG::initInstallTabWidget()
{
    installTabWidget =  new QTabWidget(this);
}

void SubInstallCFG::setShapeInstallTabWidget()
{
    installTabWidget->setTabShape(QTabWidget::Triangular);
}

void SubInstallCFG::setLocationInstallTabWidget()
{
    installTabWidget->setTabPosition(QTabWidget::North);
}

void SubInstallCFG::addIstallTab()
{
    if(w_airport && w_testPort && w_3616 && w_sensor){
        installTabWidget->addTab(w_airport,"机场");
        installTabWidget->addTab(w_3616,"3616");
        installTabWidget->addTab(w_sensor,"SenSor");
        installTabWidget->addTab(w_testPort,"测试端口");
    }
}

void SubInstallCFG::setTabWidgetGeomerty()
{
    installTabWidget->setGeometry(0,0,width(),height());
}

void SubInstallCFG::initSizeValue()
{
    paintWidth = 0;
    paintHeght = 0;
}

void SubInstallCFG::initWidgetsObj()
{
    w_airport = new AirportCFGCom(this);
    w_3616 = new Unit3616CFGCom(this);
    w_sensor = new SensorCFGCom(this);
    w_testPort = new TestPortCFGCom(this);
}

void SubInstallCFG::init36selfCfgConnetion()
{
    if(w_3616){
        connect(this,SIGNAL(Configure3616Signal(SensorMap)),w_3616,SLOT(Configure3616Slot(SensorMap)));
        connect(this,SIGNAL(sensorStatusSignal(SensorMap)),w_3616,SLOT(sensorStatusSlot(SensorMap)));
        connect(this,SIGNAL(sensorLIBsSignal(SensorMap)),w_3616,SLOT(sensorLIBsSlot(SensorMap)));
        connect(this,SIGNAL(serialCardParamersSignal(SensorMap)),w_3616,SLOT(serialCardParamersSlot(SensorMap)));
    }
}

void SubInstallCFG::initAirportCfgConnection()
{
   if(w_airport){
       connect(this,SIGNAL(backAirInfoSignal(SensorMap)),w_airport,SLOT(backAirInfoSlot(SensorMap)));
       connect(this,SIGNAL(backRunwayInfoSignal(SensorMap)),w_airport,SLOT(backRunwayInfoSlot(SensorMap)));
       connect(this,SIGNAL(backMatchInfoSignal(SensorMap)),w_airport,SLOT(backMatchInfoSlot(SensorMap)));
   }
}


