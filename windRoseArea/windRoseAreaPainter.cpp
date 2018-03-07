#include "windrosearea.h"

void WindRoseArea::paintEvent(QPaintEvent *event)
{
   Q_UNUSED(event)
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing,true);
    painter.translate(width() / 2, height() / 2);
    painter.setPen(Qt::NoPen);

    //画区域背景
    painter.save();
    painter.setBrush(Qt::white);
    painter.drawRoundedRect(- width() / 2,- height() / 2,width() - 2,height() - 2,3,3);
    painter.setBrush(Qt::gray);
    painter.drawRoundedRect(- width() / 2 + 2,- height() / 2 + 2,width() - 2,height() - 2,3,3);
    painter.setBrush(QColor("#D9D9D9"));
    painter.drawRoundedRect(- width() / 2 + 2,- height() / 2 + 2,width() - 4,height() - 4,3,3);
    painter.restore();

    //画区域标题
    painter.save();

    //1.画标题背景
    QLinearGradient gradT(0,- height() / 2,0,-height() / 2 + 35);
    gradT.setColorAt(0,Qt::gray);
    gradT.setColorAt(0.5,QColor("#D9D9D9"));
    painter.setBrush(gradT);
    painter.drawRoundedRect(- width() / 2 + 2,- height() / 2 + 2,width() - 4,35,3,3);

    //2.画标题字样
    painter.setPen(QPen(QColor("#4A708B"),4));
    painter.drawText(- width() / 4 ,- height() / 2 + 2,width() / 2,16,Qt::AlignCenter,this->m_runWayStr);
    painter.restore();
}

