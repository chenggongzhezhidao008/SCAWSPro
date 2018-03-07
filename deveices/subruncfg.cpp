#include "subruncfg.h"

SubRunCFG::SubRunCFG(QWidget *parent) :
    QWidget(parent)
{
}

void SubRunCFG::paintEvent(QPaintEvent *e)
{
    Q_UNUSED(e)
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing,true);
    painter.translate(width()/2,height()/2);

    int left = - width() / 2;
    int top = -height() / 2;
    painter.save();
    painter.setPen(QPen(Qt::green,4));
    painter.drawText(left,top,width(),height(),Qt::AlignCenter,"Hello Config!");
    painter.restore();
}
