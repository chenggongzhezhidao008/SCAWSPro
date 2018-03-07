#include "trendUI.h"
void TrendUI::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)
    setAllContrlsGeometry();
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing,true);
    int left = - width() / 2;
    int top = - height() / 2;
    int righ = width() / 2;
    int buttom = height() / 2;
    int sHeight = height();
    int sWidth = width();

    painter.translate(righ, buttom);
    painter.setPen(Qt::NoPen);

    // copy m_metar[1]
    painter.setPen(Qt::gray);
    painter.setBrush(QColor("#7EC0EE"));
    painter.setPen(Qt::NoPen);
    painter.setPen(Qt::black);
    painter.drawText(left + 10 ,top ,80,30,Qt::AlignCenter,"趋势报");
    painter.drawText(left + 100 ,top ,80,30,Qt::AlignCenter,"发报状态");

    // real time reference data
    painter.setPen(Qt::NoPen);
    for(int metarNum = 1;metarNum < 13;metarNum++){
        painter.drawRoundedRect(left + 3,top + sHeight * metarNum / 13 + 2,sWidth - 6,sHeight / 13 - 4,10,10);
    }

    painter.setPen(Qt::black);
    for(int subTitleNum = 1;subTitleNum < 13;subTitleNum++){
        painter.drawText(left + 4,top + sHeight * subTitleNum / 13 + 2,130,
                         sHeight / 13 - 4,Qt::AlignVCenter | Qt::AlignLeft,telegramLabelName[subTitleNum]);
    }
}
