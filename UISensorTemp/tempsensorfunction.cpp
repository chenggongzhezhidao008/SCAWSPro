#include "tempsensorshow.h"
#include <QDebug>

void TempSensorShow::drawBackground(QPainter *painter)
{
    painter->save();
    painter->translate(this->width()/2,this->height()/2);
    painter->setBrush(QBrush(QColor("#4F4F4F")));
    painter->drawRect(-(this->width() / 2)
                      ,-(this->height() / 2)
                      ,this->width()
                      ,this->height());
    painter->restore();
}

void TempSensorShow::drawScale(QPainter *painter)
{
    painter->save();
    painter->translate(this->width()/2,this->height()/2);
    painter->setBrush(QBrush(QColor("#262626")));
    painter->drawRect(-(this->width() / 2)
                      ,-(this->height() / 2)
                      ,this->width() / 2
                      ,this->height());
    painter->restore();
}

void TempSensorShow::drawScaleLine(QPainter *painter)
{
    painter->save();
    painter->translate(this->width()/2,this->height()/2);
    QPen pen;
    pen.setWidth(2);
    pen.setColor(Qt::white);
    painter->setPen(pen);
    scale = (this->height() - 2) / 10;
    for(int i = 0; i < 12;i++){
        if(i % 2 == 0){
            painter->drawLine(-(this->width() / 2) + 30
                              ,(this->height() / 2) - 5 - scale * i
                              ,-2,(this->height() / 2) - 5 - scale * i);
        }
        else{
            painter->drawLine(-(this->width() / 2) + 30
                              ,(this->height() / 2) - 5 - scale * i
                              ,-8,(this->height() / 2) - 5 - scale * i);
        }
    }
    painter->restore();
}

void TempSensorShow::drawPlusOrMinus(QPainter *painter)
{
    //background
    painter->save();
    painter->translate(this->width()/2,this->height()/2);
    painter->setBrush(QBrush(QColor("#F0F8FF")));
    painter->drawRect(-(this->width() / 2) + 2
                      ,-(this->height() / 2) + 2
                      ,(this->width() / 2) - 20
                      ,this->height() -4);
    painter->restore();

    //PlusOrMinus
    qreal interval = (this->m_temp /50) * this->height();
    painter->save();
    painter->translate(this->width()/2,this->height()/2);
    painter->setBrush(QBrush(QColor("#36648B")));
    if(interval > 5){
        painter->drawRect(-(this->width() / 2) + 4
                          ,((this->height() / 2) - this->scale * 3) -  interval
                          ,(this->width() / 2) - 24
                          ,this->scale * 3 - 2 + interval);
    }
    else{
        painter->drawRect(-(this->width() / 2) + 4
                          ,((this->height() / 2) - this->scale * 3)- 3 -  interval
                          ,(this->width() / 2) - 24
                          ,this->scale * 3 + interval);
    }

    painter->restore();
}

void TempSensorShow::drawScaleValue(QPainter *painter)
{
    painter->save();
    painter->translate(this->width()/2,this->height()/2);
    painter->setPen(Qt::white);
    QFont font = painter->font();
    font.setPixelSize(12);
    painter->setFont(font);
    qreal scale = (this->height() - 2) / 10;
    for(int i = 0; i < 12;i++){
        QRectF fontRect = QRectF(10, (this->height() / 2) - 10 - scale * i,20,10);
        painter->drawText(fontRect,Qt::AlignHCenter,QString("%1").arg(-15 + i*5));
    }
    painter->restore();
}

