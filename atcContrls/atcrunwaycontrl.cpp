#include "atcrunwaycontrl.h"

AtcRunWayContrl::AtcRunWayContrl(QWidget *parent) :
    QWidget(parent)
{
}
void AtcRunWayContrl::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)
    QPainter painter(this);
    //int left = - width() / 2;
    //int top = -height() / 2;
    //int wid =  width();
    //int hei = height();
    painter.setRenderHint(QPainter::Antialiasing,true);
    painter.translate(width() / 2,height() / 2);
    painter.save();
    painter.restore();
}
