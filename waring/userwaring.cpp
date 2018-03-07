#include "userwaring.h"

UserWaring::UserWaring(QWidget *parent) :
    QWidget(parent)
{
}

void UserWaring::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)
    QPainter painter(this);
    painter.save();
    painter.drawText(0,0,width(),height(),Qt::AlignCenter,"sssssssssss");
    painter.restore();
}
