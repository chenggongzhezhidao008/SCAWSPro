#include "rvrsensoruot.h"

#include <QDebug>

void RvrSensorUot::waringContrl()
{
    if(this->m_Waring){
        update();
    }
}

void RvrSensorUot::drawWaring(QPainter *painter)
{
    painter->save();
    if(this->m_Waring){
        painter->setBrush(QColor("#CDCD00"));
        QRect waringRect1(-this->width() / 2 + 1.5
                          ,-this->height() / 2 + 1.5
                          ,this->width() - 3
                          ,this->height() - 3);
        painter->drawRoundRect(waringRect1,12,16);
    }
    else{
        painter->setBrush(QBrush(QColor("#C9C9C9")));
        QRect waringRect2(-this->width() / 2 + 1.5
                          ,-this->height() / 2 + 1.5
                          ,this->width() - 3
                          ,this->height() - 3);
        painter->drawRoundRect(waringRect2,12,16);
    }
    painter->restore();
}

void RvrSensorUot::drawRVRArea(QPainter *painter)
{
    painter->save();
    if(this->m_enable){
        painter->setBrush(QColor("#F0F8FF"));
    }
    else
    {
        painter->setBrush(Qt::gray);
    }
    painter->drawRect(-(this->width() / 2) + 6,
                      -(this->height() / 2) + 6
                      ,this->width() - 12
                      ,this->height() - 12);
    painter->restore();
}

void RvrSensorUot::drawRVRContext(QPainter *painter)
{
    painter->save();
    painter->setPen(QColor("#4A708B"));//#292929 2017.5.9 修改字体颜色
    QFont fontName = painter->font();
    fontName.setPixelSize(m_dataNameSize);//20 2017.5.9 修改字体大小
    fontName.setBold(true);
    painter->setFont(fontName);

    QRectF nameRect = QRectF(-(this->width() / 2) + 10
                             ,-(this->height() / 2)+ 8
                             ,60 + 30
                             ,(this->height() / 2)); //2017.5.9 数据名称宽度加30:+30
    QString nameRVR = this->m_dataName;
    painter->drawText(nameRect,Qt::AlignLeft, nameRVR);

    QRectF unitRect = QRectF((this->width() / 2) - 40
                             ,-(this->height() / 2)+ 8
                             ,32
                             ,(this->height() / 2));
    QString unitRVR = this->m_unit;
    painter->drawText(unitRect,Qt::AlignHCenter | Qt::AlignRight, unitRVR);

    QFont fontSecond = painter->font();
    fontSecond.setPixelSize(m_timeSize);
    fontSecond.setBold(true);
    painter->setFont(fontSecond);
    QRectF SecondRect = QRectF((this->width() / 2) - 48
                               ,5 - 5
                               ,40
                               ,(this->height() / 2) );
    QString Second = this->m_time;
    painter->drawText(SecondRect
                      ,Qt::AlignCenter | Qt::AlignRight
                      ,Second);
    painter->restore();
}

void RvrSensorUot::drawRVRValue(QPainter *painter)
{
    painter->save();
    if(this->m_Waring)//告警闪烁
    {
        painter->setPen(QColor("#CDCD00"));
        //painter->setPen(QColor("#000000"));
    }
    else{
        painter->setPen(Qt::black);
    }
    QFont fontRVRValue = painter->font();
    fontRVRValue.setPixelSize(this->m_fontSize);
    fontRVRValue.setBold(true);
    painter->setFont(fontRVRValue);
    QRectF RVRValueRect = QRectF(-(this->width() / 2) + 10
                                 ,-(this->height() / 2) + (this->height() / 3)
                                 ,width() * 3 / 4
                                 ,this->height() * 3 / 4 - 10);
    QString RVRValue =  this->m_Text;
    painter->drawText(RVRValueRect,Qt::AlignHCenter | Qt::AlignBottom, RVRValue);
    painter->restore();
}

