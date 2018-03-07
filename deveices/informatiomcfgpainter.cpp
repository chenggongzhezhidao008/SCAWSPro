#include "informationcfg.h"
#include <QDebug>

void InformationCFG::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing,true);
    int left = -width() / 2;
    int top = - height() / 2;
    int uiwidth = width();
    int uiheight = height();
    if(subWidth != uiwidth && subHeight != uiheight){
        subWidth = uiwidth ;
        subHeight = uiheight;
        setInstallComGeomerty();
        setRunComGeomerty();
        setTestGeometry();
    }

    painter.translate(width() / 2,height() / 2);
    painter.save();
    painter.setPen(Qt::NoPen);
    painter.setBrush(QColor("#D9D9D9"));
    painter.drawRect(left,top,uiwidth,uiheight);

    painter.setPen(Qt::white);
    QPoint configStartPoint(0,top);
    QPoint configEndPoint(0,top + 30);
    QLinearGradient gradMet1(configStartPoint,configEndPoint);
    QLinearGradient gradMet2(configStartPoint,configEndPoint);
    gradMet1.setColorAt(0,QColor("#4A708B"));
    gradMet1.setColorAt(1,QColor("#00688B"));
    gradMet2.setColorAt(0,QColor("#CAE1FF"));
    gradMet2.setColorAt(1,QColor("#B0E0E6"));
    if(!setInstallDeveice){
        painter.setBrush(gradMet1);
    }
    else {
        painter.setBrush(gradMet2);
    }
    painter.drawRect(left,top,100,30);//drawRoundedRect ,15,15
    if(!setRun){
        painter.setBrush(gradMet1);
    }
    else{
        painter.setBrush(gradMet2);
    }
    painter.drawRect(left + 100,top,100,30);//drawRoundedRect ,15,15
    if(!setAirPort){
        painter.setBrush(gradMet1);
    }
    else {
        painter.setBrush(gradMet2);
    }
    painter.drawRect(left + 200,top,100,30);//drawRoundedRect ,15,15

    painter.drawText(left,top,100,30,Qt::AlignCenter,"安装配置");
    painter.drawText(left + 100,top,100,30,Qt::AlignCenter,"运行配置");
    painter.drawText(left + 200,top,100,30,Qt::AlignCenter,"测试配置");
    painter.restore();
    painter.save();

    painter.setPen(QPen(QColor("#4A708B"),2));
    painter.drawLine(left,top + 30,left + uiwidth,top + 30);
    //painter.drawRect(left,top + 30,uiwidth,uiheight - 30);
    painter.restore();

    if(set[1]){
        showOrcloseTestCom(false);
        showOrcloseRunCom(false);
        showOrcloseInstallCom(true);
        //安装配置
        painter.save();
        painter.setPen(Qt::NoPen);
        painter.restore();
    }
    else if(set[2]){
        showOrcloseTestCom(false);
        showOrcloseInstallCom(false);
        showOrcloseRunCom(true);

        //运行配置
        painter.save();
        painter.setPen(Qt::NoPen);
        painter.restore();
    }
    else if(set[3]){
        showOrcloseInstallCom(false);
        showOrcloseRunCom(false);
        showOrcloseTestCom(true);

        //测试端口配置
        painter.save();
        painter.setPen(Qt::NoPen);
        painter.restore();
    }
}

void InformationCFG::mousePressEvent(QMouseEvent *event)
{
    Q_UNUSED(event)
    bool buttonPress = false;
    if(event->button() == Qt::LeftButton)
    {
        int posX = event->pos().x();
        int posY = event->pos().y();
//        qDebug()<<"x:"<< QString("%1").arg(posX)<<"y:"<< QString("%1").arg(posY);
        if(posX > 0 && posX < 100 &&
                posY > 0 && posY < 30)
        {
            qDebug()<<"1";
            selectVlues(3,1);
            setInstallDeveice = true;
            buttonPress = true;
            buttonRelease = true;
        }
        if(posX > 100 && posX < 200 &&
                posY > 0 && posY < 30)
        {
            qDebug()<<"2";
            selectVlues(3,2);
            setRun = true;
            buttonPress = true;
            buttonRelease = true;
        }
        if(posX > 200 && posX < 300 &&
                posY > 0 && posY < 30)
        {
            qDebug()<<"3";
            selectVlues(3,3);
            setAirPort = true;
            buttonPress = true;
            buttonRelease = true;
        }
    }
    if(buttonPress){
        update();
    }
}

void InformationCFG::mouseReleaseEvent(QMouseEvent *event)
{
    Q_UNUSED(event)

    qDebug()<<"release button";
    if(setInstallDeveice){
        setInstallDeveice = false;
    }
    if(setRun){
        setRun = false;
    }
    if(setAirPort){
        setAirPort = false;
    }
    if(buttonRelease){
        buttonRelease = false;
        update();
    }
}


