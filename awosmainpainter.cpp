#include "awosmainfram.h"
#include <QPolygon>

void AwosMainFram::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)
//    if(painter == NULL){
//        painter = new QPainter(this);
//    }
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing,true);
    painter.translate(this->width() / 2,this->height() /2);
    painter.setPen(Qt::NoPen);
    painter.save();
    painter.setPen(QColor("#0000AA"));
    painter.drawLine(-this->width() / 2,-this->height() / 2 + 1, this->width() / 2,-this->height() / 2 + 1);
    painter.setPen(QColor("#F4A460"));
    painter.drawLine(-this->width() / 2,-this->height() / 2 + 1, -this->width() / 2,this->height() / 2 + 1);
    painter.drawLine(-this->width() / 2,this->height() / 2, this->width() / 2,this->height() / 2);
    painter.drawLine(this->width() / 2,-this->height() / 2 + 1, this->width() / 2,this->height() / 2 + 1);
    painter.restore();
}


