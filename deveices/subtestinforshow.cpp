#include "subtestinforshow.h"

subTestInforShow::subTestInforShow(QWidget *parent) :
    QWidget(parent)
{
}

void subTestInforShow::paintEvent(QPaintEvent *e)
{
    Q_UNUSED(e)
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing,true);
    painter.translate(width() / 2,height() / 2);
    int left = - width() / 2;
    int top = - height() / 2;
    painter.save();
//    painter.setPen(QPen(Qt::green,5));
    painter.setBrush(Qt::gray);
    painter.drawRect(left,top,width(),height());
//    painter.drawText(0,0,width(),height(),Qt::AlignCenter,"Hello Scroll!");
    painter.restore();
}
