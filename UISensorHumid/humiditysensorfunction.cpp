#include "humidsensorout.h"
#include <QDebug>

void HumidSensorOut::drawBackground(QPainter *painter)
{
    painter->save();
    painter->setBrush(QBrush(QColor("#4F4F4F")));/*#104E8B*/
    painter->drawRect(-(this->width() / 2), -(this->height() / 2),this->width(),this->height());
    painter->restore();
}

void HumidSensorOut::drawScale(QPainter *painter)
{
    painter->save();
    painter->setBrush(QBrush(QColor("#262626")/*Qt::black*/));
    painter->drawRect(-(this->width() / 2), -(this->height() / 2),this->width() / 2,this->height());
    painter->restore();
}

void HumidSensorOut::drawScaleLine(QPainter *painter)
{
    painter->save();
    QPen pen;
    pen.setWidth(2);
    pen.setColor(Qt::white);
    painter->setPen(pen);
    qreal scale = (this->height() - 2) / 10;
    for(int i = 0; i < 12;i++){
        if(i % 2 == 0){
            painter->drawLine(-(this->width() / 2) + 30, (this->height() / 2) - 3 - scale * i, -2, (this->height() / 2) - 3 - scale * i);
        }else{
            painter->drawLine(-(this->width() / 2) + 30, (this->height() / 2) - 3 - scale * i, -8, (this->height() / 2) - 3 - scale * i);
        }
    }
    painter->restore();
}

void HumidSensorOut::drawPlusOrMinus(QPainter *painter)
{
    //background
    painter->save();
    painter->setBrush(QBrush(QColor("#F0F8FF")/*Qt::white*/));
    painter->drawRect(-(this->width() / 2) + 2, -(this->height() / 2) + 2,(this->width() / 2) - 20,this->height() -4);
    painter->restore();

    //PlusOrMinus
    qreal length = (this->m_humidityValue /100) * this->height();
    painter->save();
    painter->setBrush(QBrush(QColor("#36648B")));
    if(this->m_humidityValue == 100){
        painter->drawRect(-(this->width() / 2) + 4, ((this->height() / 2)) + 2 - length,
                          (this->width() / 2) - 24,length - 4);
    }
    else{
        painter->drawRect(-(this->width() / 2) + 4, ((this->height() / 2) - 2) - length,
                          (this->width() / 2) - 24,length);
    }
    painter->restore();
}

void HumidSensorOut::drawScaleValue(QPainter *painter)
{
    painter->save();
    painter->setPen(Qt::white);
    QFont font = painter->font();
    font.setPixelSize(12);
    painter->setFont(font);
    qreal scale = (this->height() - 2) / 10;
    for(int i = 0; i < 12;i++){
        QRectF fontRect = QRectF(10, (this->height() / 2) - 10 - scale * i,20,10);
        painter->drawText(fontRect,Qt::AlignHCenter,QString("%1").arg(i*10));
    }
    painter->restore();
}



