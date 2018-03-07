#include "runway.h"

void RunWay::drawBackgroud(QPainter *painter)
{
    painter->save();
    painter->setBrush(Qt::gray);
    painter->drawRect(-width() / 2,-height() / 2 ,width(),height());
    painter->restore();
}

void RunWay::drawTwoTuochPoint(QPainter *painter)
{
    painter->save();
    painter->setBrush( QColor("#F0F8FF"));
    for(int i = 0;i < 4;i++){
        if(isCrosswise){
            painter->drawRect(-width() / 2 + 30,-21 + 13 * i, 30 ,5);
            painter->drawRect(width() / 2 - 60,-21 + 13 * i, 30 ,5 );
        }
        else {
            painter->drawRect(-21 + 13 * i,-height() / 2 + 30,5 ,30);
            painter->drawRect(-21 + 13 * i,height() / 2 - 60,5 ,30);
        }
    }
    painter->restore();
}

void RunWay::drawRunWayText(QPainter *painter)
{
    painter->save();
    painter->setPen(QColor("#F0F8FF"));
    QFont fontRunWay = painter->font();
    fontRunWay.setPixelSize(20);
    fontRunWay.setBold(true);
    painter->setFont(fontRunWay);

    QString headMember;
    if(this->m_head.length() == 1){
        headMember = "0" + this->m_head + "R";
    }
    else{
        headMember = this->m_head + "R";
    }

    QString rearMember;
    if(this->m_rear.length() == 1){
        rearMember = "0" + this->m_rear + "R";
    }
    else{
        rearMember = this->m_rear + "R";
    }
    if(isCrosswise){
        painter->rotate(- 90);
        QRectF headRectV = QRectF(-30,-width() / 2 + 30 + 30, 60 ,30);
        painter->drawText(headRectV,Qt::AlignHCenter, headMember);
        QRectF rearRectV = QRectF(-30,width() / 2 - 30 - 30 - 25, 60 ,30);
        painter->drawText(rearRectV,Qt::AlignHCenter, rearMember);
    }
    else{
        QRectF headRectV = QRectF(-30,-height() / 2 + 30 + 30, 60 ,30);
        painter->drawText(headRectV,Qt::AlignHCenter, headMember);
        QRectF rearRectV = QRectF(-30,height() / 2 - 30 - 30 - 30, 60 ,30);
        painter->drawText(rearRectV,Qt::AlignHCenter, rearMember);
    }
    painter->restore();
}

