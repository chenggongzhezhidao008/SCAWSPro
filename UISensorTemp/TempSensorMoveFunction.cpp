
#include "tempsensorshow.h"

void TempSensorShow::mousePressEvent(QMouseEvent *e)
{
    if(e->button() == Qt::LeftButton){
        point = e->globalPos() - this->pos();
        mousePressed = true;
    }
    e->accept();
}

void TempSensorShow::mouseMoveEvent(QMouseEvent *e)
{
    QPoint p;
    if(e->buttons() == Qt::LeftButton && this->mousePressed){
        p = e->globalPos() - this->point;
        this->move(p);
    }
    qDebug()<<"ssdddd"<<p;
    e->accept();
}

void TempSensorShow::mouseReleaseEvent(QMouseEvent *e)
{
    if(e->button() == Qt::LeftButton){
        //判断鼠标事件的按钮名称
        this->mousePressed = false;
    }
    e->accept();
}
