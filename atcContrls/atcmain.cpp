#include "atcmain.h"

ATCMAIN::ATCMAIN(QWidget *parent) :
    QWidget(parent)
{

    inintContrls();
    installContrlsEventFilter();

    initAckObj();
    installAckEventFilter();

    initTeleObj();
    installTeleEventFilter();
}

bool ATCMAIN::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::MouseMove
            || event->type() == QEvent::HoverEnter
            || event->type() == QEvent::HoverLeave
            || event->type() == QEvent::HoverMove)
    {
        event->accept();
        return true;
    }
    else{
        return QWidget::eventFilter(obj, event);
    }
}
// wind = location（left meter；mind meter;right meter）
// value = data name str(find in the function:ATCMainWindRose::setData(QString value))
// + : + data value str
void ATCMAIN::setDataValue(QString wind, QString value)
{
    if(wind == "left"){
       setWindRoseValue(meterOne,value);
    }
    else if(wind == "mid"){
       setWindRoseValue(meterTwo,value);
    }
    else if(wind == "right"){
       setWindRoseValue(meterThree,value);
    }
}

void ATCMAIN::setShowOutGeometry()
{
    setContrlsGeometry();
    setAckGeometry();
    setTelegramGeometry();
}

void ATCMAIN::inintContrls()
{
    runway = new RunWay(this);
    meterOne = new ATCMainWindRose(this);
    meterTwo = new ATCMainWindRose(this);
    meterThree = new ATCMainWindRose(this);
}

void ATCMAIN::setContrlsGeometry()
{
    meterTwo->setEnableCloud(false);
    runway->setGeometry(2,height() * 2 / 16 - height() / 28,width() - 4 ,height() / 14);
    meterOne->setGeometry(2,height() * 2 / 8,(width() - 2) / 3 - 2,height() * 4 / 8);
    meterTwo->setGeometry((width() - 2) / 3,height() * 2 / 8,(width() - 2) / 3 - 2,height() * 4 / 8);
    meterThree->setGeometry((width() - 2) * 2 / 3,height() * 2 / 8,(width() - 2) / 3 - 2,height() * 4 / 8);
}

void ATCMAIN::installContrlsEventFilter()
{
    runway->installEventFilter(this);
    meterOne->installEventFilter(this);
    meterTwo->installEventFilter(this);
    meterThree->installEventFilter(this);
}

void ATCMAIN::setWindRoseValue(ATCMainWindRose *&rose,QString Value)
{
    rose->setData(Value);
}

void ATCMAIN::initAckObj()
{
    ack = new atcMainACK(this);
}

void ATCMAIN::installAckEventFilter()
{
    ack->installEventFilter(this); // 安装事件
}

void ATCMAIN::setAckGeometry()
{
    ack->setGeometry(2,height() * 3 / 4,width() - 4,height() / 8);
}

void ATCMAIN::initTeleObj()
{
    telegram = new AFTNHurdle(this);
}

void ATCMAIN::installTeleEventFilter()
{
    telegram->installEventFilter(this);
}

void ATCMAIN::setTelegramGeometry()
{
    telegram->setGeometry(2,height() * 7 / 8,width() - 4,height() / 8);
}
