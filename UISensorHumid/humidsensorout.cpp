#include "humidsensorout.h"

HumidSensorOut::HumidSensorOut(QWidget *parent) :
    QWidget(parent)
{
    //    painter = NULL;
    this->m_id = 0;
    this->m_humidityValue = 100;
    this->m_waringValue = -1;
    this->m_dayNightModel = "day";
    this->m_lastHumidity = 0.0f;
    point = QPoint();
    mousePressed = false;
}

void HumidSensorOut::initHumidityUI()
{
    this->m_humidUIWidth = this->width();
    this->m_humidUIHeight = this->height();
}

void HumidSensorOut::setLastHumidityValue(float humidity)
{
    this->m_lastHumidity = humidity;
}

void HumidSensorOut::setFlag(int flag)
{
    this->m_flag = flag;
}

void HumidSensorOut::setSensorId(int id)
{
    this->m_id = id;
    update();
}

void HumidSensorOut::setHumidity(float humidity)
{
    this->m_humidityValue = humidity;
    update();
}

void HumidSensorOut::setWaring(float waring)
{
    this->m_waringValue = waring;
    update();
}

void HumidSensorOut::setDayNigth(QString model)
{
    this->m_dayNightModel = model;
    update();
}

void HumidSensorOut::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)
    QPainter painter(this);
//    painter.save();
    painter.translate(this->width()/2,this->height()/2);
    painter.setPen(Qt::NoPen);
    //绘制背景
    drawBackground(&painter);
    //绘制刻度
    drawScale(&painter);
    //绘制刻度线
    drawScaleLine(&painter);
    //绘制动态增减条
    drawPlusOrMinus(&painter);
    //绘制刻度数值
    drawScaleValue(&painter);
//    painter.restore();
}









