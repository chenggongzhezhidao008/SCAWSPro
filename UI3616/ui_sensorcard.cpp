#include "ui_sensorcard.h"
#include <QLinearGradient>
#include <QRadialGradient>
#include <QConicalGradient>


Ui_sensorCard::Ui_sensorCard(QWidget *parent) :
    QWidget(parent)
{
    this->setWindowFlags(Qt::FramelessWindowHint);
}

void Ui_sensorCard::paintEvent(QPaintEvent *event)
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
    int v5 = _with * 3/50; // 6
    int v9 = _with * 3/5;  // 60
    int v10 = _with /25;   // 4
    int v20 = _with /20;   // 5

    // boilt color
    painter.save();
    painter.setBrush(QColor("#7A8B8B"));
    painter.drawRoundedRect(-v1,-_height/2 + v3,v2,v2,v1,v1);
    painter.drawRoundedRect(-v1,_height/2 - v3 - v2,v2,v2,v1,v1);
    painter.setPen(QPen(Qt::black,3));
    painter.drawLine(-v5,-_height/2 + v1 + v3,v5,-_height/2 + + v1 + v3);
    painter.drawLine(0,-_height/2 + v1 + v3-v5,0,-_height/2 + v1 + v3+v5);
    painter.drawLine(-v5,_height/2-v3-v2+v1,v5,_height/2-v3-v2+v1);
    painter.drawLine(0,_height/2-v3-v2+v1-v5,0,_height/2-v3-v2+v1+v5);
    painter.restore();

    //small boilt color
    painter.save();
    painter.setBrush(QColor("#7A8B8B"));
    painter.drawRoundedRect(-v3,-_height/2 + v3+v2+v3*2,v1,v1,v3,v3);
    painter.drawRoundedRect(-v3,_height/2 - (v3+v2+v3*2)- v1,v1,v1,v3,v3);
    painter.setPen(QPen(Qt::black,3));
    painter.drawLine(-v5,-_height/2+v3+v2+v3*2+v1/2,v5,-_height/2+v3+v2+v3*2+v1/2);
    painter.drawLine(-v5,_height/2 -(v3+v2+v3*2+v1)+v1/2,v5,_height/2 -(v3+v2+v3*2+v1)+v1/2);
    painter.restore();

    //UID light draw
    painter.save();
    painter.setBrush(QColor("#FFFFFF"));
    painter.drawRoundedRect(-v1,-_height/2 + v3+v2+v3*2+v1+v3*2,v1,v1,v3,v3);
    painter.setPen(QPen(Qt::white,3));
    painter.drawText(2,-_height/2 + (v3+v2+v3*2+v1+v3*2) + v1/2-8,_with/2-v3,16,
                     Qt::AlignVCenter||Qt::AlignLeft,"UID");
    painter.restore();

    //DCD light draw
    painter.save();
    painter.setBrush(QColor("#00FF00"));
    painter.drawRoundedRect(-v1,-_height/2 + v3+v2+v3*2+v1+v3*2+v1+v3*3,v1,v1,v3,v3);
    painter.setPen(QPen(Qt::white,3));
    painter.drawText(2,-_height/2 + (v3+v2+v3*2+v1+v3*2)+v1+v3*3 + v1/2-8,_with/2-v3,16,
                     Qt::AlignVCenter||Qt::AlignLeft,"DCD");
    painter.restore();

    //console port color
    painter.save();   //下方最顶画到110位置
    painter.setPen(Qt::white);
    painter.drawText(-_with/4,-_height/2+(v2+3*v1+9*v3+v9),_with*3/4
                     ,v1,Qt::AlignCenter,"RS232");
    painter.setPen(Qt::NoPen);
    painter.setBrush(QColor("#FCFCFC"));
    painter.drawRoundedRect(-_with/5,-_height/2+(v2+3*v1+9*v3),v9,v9,v10,v10);
    painter.setBrush(QColor("#4D4D4D"));
    painter.drawRect(-_with/5 +5,-_height/2+(v2+3*v1+9*v3)+v20,v9-20,v9-v3);
    painter.drawRect(-_with/5 +5,-_height/2+(v2+3*v1+9*v3)+_with*16/100,v9-16,v9-_with*32/100);
    painter.drawRect(-_with/5 +5,-_height/2+(v2+3*v1+9*v3)+v3*2,v9-10,v9-v3*4);
    painter.setBrush(QColor("#00FF00"));
    painter.drawRoundedRect(-_with/5 +5 + v9-19,-_height/2+(v2+3*v1+9*v3),10,_with*15/100,4,4);
    painter.setBrush(QColor("#FFD700"));
    painter.drawRoundedRect(-_with/5 +5 + v9-19,-_height/2+(v2+3*v1+9*v3+v9)-v3*2,10,_with*15/100,4,4);
    painter.restore();

    //SGN light draw
    painter.save();
    painter.setBrush(QColor("#00FF00"));
    painter.drawRoundedRect(-v1,-_height/2+(v2+4*v1+v9+_with),v1,v1,v3,v3);
    painter.setPen(QPen(Qt::white,3));
    painter.drawText(2,-_height/2+(v2+4*v1+v9+_with) + v1/2-8,_with/2-v3,16,
                     Qt::AlignVCenter||Qt::AlignLeft,"DCD");
    painter.restore();

    //TxD light draw
    painter.save();
    painter.setBrush(QColor("#00FF00"));
    painter.drawRoundedRect(-v1,-_height/2+(v2+5*v1+v9+_with*11/10) ,v1,v1,v3,v3);
    painter.setPen(QPen(Qt::white,3));
    painter.drawText(2,-_height/2+(v2+5*v1+v9+_with*11/10) + v1/2-8,_with/2-v3,16,
                     Qt::AlignVCenter||Qt::AlignLeft,"TxD");
    painter.restore();

    //RxD light draw
    painter.save();
    painter.setBrush(QColor("#00FF00"));
    painter.drawRoundedRect(-v1,-_height/2+(v2+6*v1+v9+_with*12/10),v1,v1,v3,v3);
    painter.setPen(QPen(Qt::white,3));
    painter.drawText(2,-_height/2+(v2+6*v1+v9+_with*12/10) + v1/2-8,_with/2-v3,16,
                     Qt::AlignVCenter||Qt::AlignLeft,"RxD");
    painter.restore();


    //UDC port color
    painter.save();                 //下方最顶画到110位置
    painter.setPen(Qt::white);
    painter.drawText(-10,_height/2 - (v3+v2+v3*2+v1+v3*2+v1+v9+v3*2+v1)-5,_with/2-_with/10
                     ,v1,Qt::AlignCenter,"UDC");
    painter.setPen(Qt::NoPen);
    painter.setBrush(QColor("#FCFCFC"));
    painter.drawRoundedRect(-_with/5,_height/2 - (v3+v2+v3*2+v1+v3*2+v1+v9+v3*2),v9,v9,v10,v10);
    painter.setBrush(QColor("#4D4D4D"));
    painter.drawRect(-_with/5 + 8,_height/2 - (v3+v2+v3*2+v1+v3*2+v1+v9+v3*2) +3,v9-15,v9-6);
    painter.drawRect(-_with/5 + 3,_height/2 - (v3+v2+v3*2+v1+v3*2+v1+v9+v3*2) +v9/2 -v2/2,v9-10,v2);
    painter.drawRect(-_with/5 + 1,_height/2 - (v3+v2+v3*2+v1+v3*2+v1+v9+v3*2) +v9/2 -v1/2,v9-8,v1);
    painter.restore();

    //RxD light draw
    painter.save();
    painter.setBrush(QColor("#000000"));
    painter.drawRoundedRect(-v1,_height/2 - (v3+v2+v3*2+v1+v3*2+v1),v1,v1,v3,v3);
    painter.setPen(QPen(Qt::white,3));
    painter.drawText(2,_height/2 - (v3+v2+v3*2+v1+v3*2+v1) + v1/2-8,_with/2-v3,16,
                     Qt::AlignVCenter||Qt::AlignLeft,"ADJ");
    painter.restore();
}
