#include "tempsensorshow.h"

TempSensorShow::TempSensorShow(QWidget *parent) :
    QWidget(parent)
{
       this->m_id = 0;
       m_temp = 35;
       m_waring = 0;
       scale = 0.0;
       m_dayNight = "";
       m_lastTemperature = 0.0f;
       point = QPoint();
       mousePressed = false;
}

void TempSensorShow::setFlag(int flag)
{
    this->m_flag = flag;
}

void TempSensorShow::setSensorId(int id)
{
    this->m_id = id;
    update();
}

void TempSensorShow::setTempValue(float temp)
{
    this->m_temp = temp;
    update();
}

void TempSensorShow::setWaringValue(float waring)
{
    this->m_waring = waring;
     update();
}

void TempSensorShow::setDayNight(QString model)
{
    this->m_dayNight = model;
    update();
}

void TempSensorShow::setLastTemperatureValue(float temperature)
{
    this->m_lastTemperature = temperature;
}

void TempSensorShow::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)
    QPainter painter;
    painter.begin(this);
    painter.setPen(Qt::NoPen);
    //绘制背景
    drawBackground(&painter);
    //绘制刻度部分
    drawScale(&painter);
    //绘制刻度线
    drawScaleLine(&painter);
    //绘制增减条
    drawPlusOrMinus(&painter);
    //绘制刻度数据数值
    drawScaleValue(&painter);
}

