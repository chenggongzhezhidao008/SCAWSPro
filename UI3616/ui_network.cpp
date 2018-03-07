#include "Ui_Network.h"

Ui_NetworkCard::Ui_NetworkCard(QWidget *parent) :
    QWidget(parent)
{
    this->setWindowFlags(Qt::FramelessWindowHint);
}

void Ui_NetworkCard::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)
    int _with = width();
    int _height = height();
    QPainter painter(this);
    QFont font;
    font.setBold(true);
    font.setPixelSize(12);
    painter.setFont(font);
    painter.setRenderHint(QPainter::Antialiasing,true);
    painter.translate(_with/2,_height/2);
    // background color
    painter.save();
    painter.setBrush(QColor("#404040"));
    painter.drawRoundedRect(-_with/2,-_height/2,_with,_height,4,4);
    painter.restore();

    int v1 = _with /5;     // 20
    int v2 = _with * 2/5;  // 40
    int v3 = _with /10;    // 10
    int v4 = _with /2;     // 50
    int v5 = _with * 3/50; // 6
    int v6 = _with * 3/10; // 30
    int v9 = _with * 3/5;  // 60
    int v10 = _with /25;   // 4
    int v12 = _with /4;    // 25
    int v20 = _with /20;       // 5
    int v21 = _with *38/100;   // 38
    // boilt color
    painter.save();
    painter.setBrush(QColor("#7A8B8B"));
    painter.drawRoundedRect(-v1,-_height/2 + 10,v2,v2,v1,v1);
    painter.drawRoundedRect(-v1,_height/2 - 10 - v2,v2,v2,v1,v1);
    painter.setPen(QPen(Qt::black,3));
    painter.drawLine(-v5,-_height/2 + v1 + 10,v5,-_height/2 + + v1 + 10);
    painter.drawLine(0,-_height/2 + v1 + 10-v5,0,-_height/2 + v1 + 10+v5);
    painter.drawLine(-v5,_height/2-10-v2+v1,v5,_height/2-10-v2+v1);
    painter.drawLine(0,_height/2-10-v2+v1-v5,0,_height/2-10-v2+v1+v5);
    painter.restore();

    //small boilt color
    painter.save();
    painter.setBrush(QColor("#7A8B8B"));
    painter.drawRoundedRect(-v3,-_height/2 + 10+v2+20,v1,v1,v3,v3);
    painter.drawRoundedRect(-v3,_height/2 - (10+v2+20)- v1,v1,v1,v3,v3);
    painter.setPen(QPen(Qt::black,3));
    painter.drawLine(-v5,-_height/2+10+v2+20+v1/2,v5,-_height/2+10+v2+20+v1/2);
    painter.drawLine(-v5,_height/2 -(10+v2+20+v1)+v1/2,v5,_height/2 -(10+v2+20+v1)+v1/2);
    painter.restore();

    //ALARM light color
    painter.save();
    painter.setPen(Qt::white);
    painter.drawText(-_with/2,-_height/2 + (10+v2+20+v1+20),_with,v1,Qt::AlignCenter,"ALARM");
    painter.setPen(Qt::NoPen);
    painter.setBrush(QColor("#EE0000"));
    painter.drawRoundedRect(-v20*3,-_height/2 + (10+v2+20+v1+20+v1),v6,v6,v20*3,v20*3);
    painter.restore();

    //operating light color
    painter.save();
    painter.setPen(Qt::white);
    painter.drawText(-_with/2,-_height/2 + (10+v2+20+v1+20+v1+10+v6),_with,v1,Qt::AlignCenter,"OPERATING");
    painter.setPen(Qt::NoPen);
    painter.setBrush(QColor("#00FF00"));
    painter.drawRoundedRect(-v3,-_height/2 + (10+v2+20+v1+20+v1+10+v6+v1),v1,v1,v3,v3);
    painter.restore();

    //console port color
    painter.save();   //下方最顶画到110位置
    painter.setPen(Qt::white);
    painter.drawText(-_with/2+_with/10,_height/2 -(10+v2+20+v1+20+v1+v9),_with-_with/10,v1,Qt::AlignCenter,"CONSOLE");
    painter.setPen(Qt::NoPen);
    painter.setBrush(QColor("#FCFCFC"));
    painter.drawRoundedRect(-v12,_height/2 - (10+v2+20+v1+20+v9),v9,v9,v10,v10);
    painter.setBrush(QColor("#4D4D4D"));
    painter.drawRect(-5,_height/2 - (10+v2+20+v1+20+v9)*185/190,v6,v4);
    painter.drawRect(-8,_height/2 - (10+v2+20+v1+20+v9)*179/190,v6,v21);
    painter.drawRect(-12,_height/2 - (10+v2+20+v1+20+v9)*175/190,v6,v6);
    painter.restore();
}
