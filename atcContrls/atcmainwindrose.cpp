#include "atcmainwindrose.h"


ATCMainWindRose::ATCMainWindRose(QWidget *parent) :
    QWidget(parent)
{
    initRose();
    initSizeValue();
    installWindRose();

    initLineContrls();
    installLineContrl();
    initrunWayStrVlaue();
    initenable();
}

void ATCMainWindRose::paintEvent(QPaintEvent *e)
{
    Q_UNUSED(e)
    if(sWidth != width() || sHeght != height()){
        sWidth = width() ;
        sHeght = height();
        setRoseGeometry();
        setLineGeometry();
    }
    int left = -width() / 2 ;
    int top = -height() / 2;
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing,true);
    painter.translate(width() / 2,height() / 2);
    painter.setPen(Qt::NoPen);

    //画区域背景
    painter.save();
    painter.setBrush(Qt::white);
    painter.drawRoundedRect(left,top,width() - 2,height() - 2,3,3);
    painter.setBrush(Qt::gray);
    painter.drawRoundedRect(left + 2,top + 2,width() - 2,height() - 2,3,3);
    painter.setBrush(QColor("#D9D9D9"));
    painter.drawRoundedRect(left + 2,top + 2,width() - 4,height() - 4,3,3);
    painter.restore();

    //1.画标题背景
    painter.save();
    QLinearGradient gradT(0,top,0,-height() / 2 + 35);
    gradT.setColorAt(0,Qt::gray);
    gradT.setColorAt(0.5,QColor("#D9D9D9"));
    painter.setBrush(gradT);
    painter.drawRoundedRect(left + 2,top + 2,width() - 4,35,3,3);

    //2.画标题字样
    painter.setPen(QPen(QColor("#4A708B"),4));
    painter.drawText(left,top + 2,width() / 2,16,Qt::AlignCenter,this->m_runWayStr);
    painter.restore();

    //绘制数据标题名称
    painter.save();
    painter.setPen(QPen(Qt::gray,3));
    painter.drawText(left + 2,height() * 3 / 10,60,height() / 10,Qt::AlignCenter,"RVR 1 AVG");
    painter.drawText(left + 2,height() * 4 / 10,60,height() / 10,Qt::AlignCenter,"VIS 1 AVG");
    if(m_enable){
        painter.drawText(0,height() * 3 / 10,60,height() / 10,Qt::AlignCenter,"CLD");
    }
    painter.drawText(0,height() * 4 / 10,60,height() / 10,Qt::AlignCenter,"GUST");
    painter.restore();
}

bool ATCMainWindRose::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::MouseButtonPress || event->type() == QEvent::MouseMove) {
        event->accept();
        return true;
    }
    else{
        return QWidget::eventFilter(obj, event);
    }
}

void ATCMainWindRose::setRunWayname(QString name){
    this->m_runWayStr = name;
    update();
}

void ATCMainWindRose::setEnableCloud(bool enable){
    this->m_enable = enable;
    if(m_enable){
        m_CLD->show();
    }
    else{
        m_CLD->hide();
    }
    update();
}

void ATCMainWindRose::setData(QString value)
{
    QStringList datas;
    datas = value.split(":");
    QString dataKind,dataValue;
    dataKind = datas.value(0);
    dataValue = datas.value(1);
    if(dataKind == "RVR"){
        m_RVR->setValue(dataValue);
    }
    else if(dataKind == "VIS"){
        m_VIS->setValue(dataValue);
    }
    else if(dataKind == "CLD"){
        m_CLD->setValue(dataValue);
    }
    else if(dataKind == "GUST"){
        m_GUST->setValue(dataValue);
    }
    else if(dataKind == "currentAngle"){
        meter->setWindCurrentAngle(dataValue.toInt());
    }
    else if(dataKind == "currentSpeed"){
        meter->setWindCurrentSpeed(dataValue);
    }
    else if(dataKind == "maxAngle"){
        meter->setTenWindMaxAngle(dataValue.toInt());
    }
    else if(dataKind == "minAngle"){
        meter->setTenWindMinAngle(dataValue.toInt());
    }
    else if(dataKind == "runAngle"){
        meter->setRunUpAngle(dataValue);
    }
    else if(dataKind == "twoSecAvAngle"){
        meter->setTwoWindAvAngle(dataValue.toInt());
    }
    else{
        return ;
    }
}

void ATCMainWindRose::initRose()
{
    meter = new WindMeter(this);
}

void ATCMainWindRose::installWindRose()
{
    meter->installEventFilter(this);
}

void ATCMainWindRose::setRoseGeometry()
{
    qreal minSiz = height() * 5.5 / 7 - 4;
    meter->setGeometry(width() / 2 - minSiz / 2,12,minSiz,minSiz);
}

void ATCMainWindRose::initLineContrls()
{
    m_RVR = new atcMainSubLineShowCom(this);
    m_VIS = new atcMainSubLineShowCom(this);
    m_CLD = new atcMainSubLineShowCom(this);
    m_GUST = new atcMainSubLineShowCom(this);

    m_RVR->setUnit("m");
    m_VIS->setUnit("m");
    m_CLD->setUnit("m");
    m_GUST->setUnit("m/s");
}

void ATCMainWindRose::installLineContrl()
{
    m_RVR->installEventFilter(this);
    m_VIS->installEventFilter(this);
    m_CLD->installEventFilter(this);
    m_GUST->installEventFilter(this);
}

void ATCMainWindRose::setLineGeometry()
{
    qreal top = height() * 5.6 / 7;
    qreal Sheight = height() * 1.4 / 7;
    qreal swidth = width() / 2;
    qreal rightLineleftpos =  width() / 2;
    m_RVR->setGeometry(70,top ,swidth - 60,qreal(Sheight / 2));
    m_VIS->setGeometry(70,top + qreal(Sheight / 2),swidth - 60,qreal(Sheight / 2));
    m_CLD->setGeometry(rightLineleftpos + 50,top,swidth - 60,qreal(Sheight / 2));
    m_GUST->setGeometry(rightLineleftpos + 50,top + qreal(Sheight / 2),swidth - 60,qreal(Sheight / 2));
}

void ATCMainWindRose::initSizeValue()
{
    sWidth = 0;
    sHeght = 0;
}

void ATCMainWindRose::initrunWayStrVlaue()
{
    m_runWayStr = "Rxx";
}

void ATCMainWindRose::initenable()
{
    m_enable = true;
}
