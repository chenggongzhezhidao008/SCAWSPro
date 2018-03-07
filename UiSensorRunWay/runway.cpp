#include "runway.h"

RunWay::RunWay(QWidget *parent) :
    QWidget(parent)
{
    //    painter = NULL;
    this->m_runwayId = 0;
    estimateWidthHeight = false;
    isCrosswise = false;
    //跑道号
    this->m_head = "06";
    this->m_rear = "24";

    point = QPoint();
    mousePressed = false;
}

void RunWay::setFlag(int flag)
{
    this->m_flag = flag;
}

void RunWay::setAirportId(int airportid)
{
    this->m_airportId = airportid;
}

void RunWay::setRunWayId(int id)
{
    this->m_runwayId = id;
    update();
}

void RunWay::setHeadName(QString head)
{
    this->m_head = head;
    update();
}

void RunWay::setRearName(QString rear)
{
    this->m_rear = rear;
    update();
}

void RunWay::setWeather(QString weather)
{
    this->m_weather = weather;
    update();
}

void RunWay::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing,true);
    /*使用跑道的宽高值来确定跑道的横竖显示
    *isCrosswise:true 横向
    *isCrosswise:false 纵向
    */
    if(!estimateWidthHeight){
        if(this->width() > this->height()){
            isCrosswise = true;
        }
        else{
            isCrosswise = false;
        }
        estimateWidthHeight = true;
    }
    painter.translate(this->width() / 2,this->height() / 2);
    painter.setPen(Qt::NoPen);
    //绘制背景
    drawBackgroud(&painter);

    //绘制两段触地段
    drawTwoTuochPoint(&painter);

    //绘制跑道号文本
    drawRunWayText(&painter);
}








