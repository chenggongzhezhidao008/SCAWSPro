#include "Ui_power.h"

Ui_powerCard::Ui_powerCard(QWidget *parent) :
    QWidget(parent)
{
    this->setWindowFlags(Qt::FramelessWindowHint);
}

void Ui_powerCard::paintEvent(QPaintEvent *event)
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

    //UID light draw
    painter.save();
    painter.setBrush(QColor("#FFFFFF"));
    painter.drawRoundedRect(-v1,-_height/2 + 10+v2+20+v1+20,v1,v1,v3,v3);
    painter.setPen(QPen(Qt::white,3));
    painter.drawText(2,-_height/2 + (10+v2+20+v1+20) + v1/2-8,_with/2-v3,16,
                     Qt::AlignVCenter||Qt::AlignLeft,"UID");
    painter.restore();

    //PWR light draw
    painter.save();
    painter.setBrush(QColor("#00FF00"));
    painter.drawRoundedRect(-v1,-_height/2 + 10+v2+20+v1+20+v1+30,v1,v1,v3,v3);
    painter.setPen(QPen(Qt::white,3));
    painter.drawText(2,-_height/2 + (10+v2+20+v1+20)+v1+30 + v1/2-8,_with/2-v3,16,
                     Qt::AlignVCenter||Qt::AlignLeft,"PWR");
    painter.restore();

    //TxD light draw
    painter.save();
    painter.setBrush(QColor("#000000"));
    painter.drawRoundedRect(-v1,_height/2 - (10+v2+20+v1+10 +v1+20+v9+20 +v1),v1,v1,v3,v3);
    painter.setPen(QPen(Qt::white,3));
    painter.drawText(2,_height/2 - (10+v2+20+v1+10 +v1+20+v9+20 +v1) + v1/2-8,_with/2-v3,16,
                     Qt::AlignVCenter||Qt::AlignLeft,"OFF");
    painter.restore();

    // on or off button; v9
    painter.save();
    painter.setBrush(QColor("#000000"));
    painter.drawRoundedRect(-v1,_height/2 - (10+v2+20+v1+10 +v1+v9+20),v2,v9,4,4);
    painter.setBrush(QColor("#00FF00"));
    painter.setPen(Qt::NoPen);
    QPoint startPoint1(0,_height/2 - (10+v2+20+v1+10 +v1+v9+20)+3);
    QPoint endPoint1(0,_height/2 - (10+v2+20+v1+10 +v1+v9+20)+v9-3);
    QLinearGradient start1(startPoint1,endPoint1),end1(endPoint1,startPoint1);
    start1.setColorAt(0.5,QColor("#5B5B5B"));
    start1.setColorAt(1,QColor("#EAEAEA"));
    end1.setColorAt(0.5,QColor("#5B5B5B"));
    end1.setColorAt(1,QColor("#EAEAEA"));
    if(true){
        painter.setBrush(start1);
    }else{
        painter.setBrush(end1);
    }
    painter.drawRect(-v1+3,_height/2 - (10+v2+20+v1+10 +v1+v9+20)+3,v2-6,(v9-6)/2);
    painter.drawRect(-v1+3,_height/2 - (10+v2+20+v1+10 +v1+v9+20)+v9/2,v2-6,(v9-6)/2);

    if(true){
        painter.setPen(QPen(Qt::gray,3));
        painter.drawText(-v1+3,_height/2 - (10+v2+20+v1+10 +v1+v9+20)+3,v2-6,(v9-6)/2,Qt::AlignCenter,"0");
        painter.setPen(QPen(Qt::white,3));
        painter.drawText(-v1+3,_height/2 - (10+v2+20+v1+10 +v1+v9+20)+v9/2,v2-6,(v9-6)/2,Qt::AlignCenter,"1");

    }else{
        painter.setPen(QPen(Qt::white,3));
        painter.drawText(-v1+3,_height/2 - (10+v2+20+v1+10 +v1+v9+20)+3,v2-6,(v9-6)/2,Qt::AlignCenter,"0");
        painter.setPen(QPen(Qt::gray,3));
        painter.drawText(-v1+3,_height/2 - (10+v2+20+v1+10 +v1+v9+20)+v9/2,v2-6,(v9-6)/2,Qt::AlignCenter,"1");
    }

    painter.restore();

    //RxD light draw
    painter.save();
    painter.setBrush(QColor("#000000"));
    painter.drawRoundedRect(-v1,_height/2 - (10+v2+20+v1+10 +v1),v1,v1,v3,v3);
    painter.setPen(QPen(Qt::white,3));
    painter.drawText(2,_height/2 - (10+v2+20+v1 +10 +v1) + v1/2-8,_with/2-v3,16,
                     Qt::AlignVCenter||Qt::AlignLeft,"ON");
    painter.restore();

}
