#include "rvrsensoruot.h"

RvrSensorUot::RvrSensorUot(QWidget *parent) :
    QWidget(parent)
{
//   painter = NULL;
   this->m_id = 0;
   waringTimer = new QTimer(this);
   connect(waringTimer,SIGNAL(timeout()),this,SLOT(waringContrl()));
   waringTimer->start(1000);

   this->m_Waring = false;

   //测试数据
   this->m_Text = "///";
    m_unit = "U";
    m_time = "T";

    point = QPoint();
    mousePressed = false;

    this->m_enable = true;

    this->m_dataName = "NAME";
    m_fontSize = 36;

    m_timeSize = 20;
    m_dataNameSize = 12;
}

void RvrSensorUot::setSensorId(int id)
{
    this->m_id = id;
    update();
}

void RvrSensorUot::setFontSize(int size)
{
    this->m_fontSize = size;
}

void RvrSensorUot::setFlag(int flag)
{
    this->m_flag = flag;
}

void RvrSensorUot::setEnable(bool able)
{
    this->m_enable = able;
    update();
}

void RvrSensorUot::setDataName(QString name)
{
    this->m_dataName = name;
    update();
}

void RvrSensorUot::setWaring(bool waringFalge)
{
    this->m_Waring = waringFalge;
    update();
}

void RvrSensorUot::setShowContext(QString text)
{
    this->m_Text = text;
    update();
}

void RvrSensorUot::setDaynight(QString flag)
{
   this->daynightflag = flag;
    if(flag == QString("day")){//设置白天或者黑夜的颜色

    }
    else{

    }
    update();
}

void RvrSensorUot::setUnitString(QString unit)
{
    this->m_unit = unit;
    update();
}

void RvrSensorUot::setTimestring(QString time)
{
    this->m_time = time;
    update();
}

void RvrSensorUot::setTimeSize(int size)
{
    this->m_timeSize = size;
}

void RvrSensorUot::setDataNameSize(int size)
{
    this->m_dataNameSize = size;
}

void RvrSensorUot::initSize()
{
    this->m_width = this->width();
    this->m_high = this->height();
}

void RvrSensorUot::paintEvent(QPaintEvent *event)
{
   Q_UNUSED(event);
   QPainter painter(this);
   painter.setRenderHint(QPainter::Antialiasing,true);
   painter.translate(this->width() / 2,this->height() / 2);
   painter.setPen(Qt::NoPen);

   //绘制告警边框
   drawWaring(&painter);

   //绘制RVR数据显示区域
   drawRVRArea(&painter);

   //绘制RVR区域内部的文本文字
   drawRVRContext(&painter);

   //绘制RVR数据值文本区域
   drawRVRValue(&painter);
}





