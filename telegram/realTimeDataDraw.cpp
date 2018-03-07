#include "realtimedata.h"

void RealTimeData::paintEvent(QPaintEvent *event)
{
    updateAllContrlsSize();
    Q_UNUSED(event)
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing,true);
    int left = - width() / 2;
    int top = - height() / 2;
    int righ = width() / 2;
    int buttom = height() / 2;
    int sHeight = height();
    int sWidth = width();
    int subWidth = sWidth - 127;
    int lenWidthOne = subWidth / 5;
    painter.translate(righ, buttom);

    painter.save();
    // copy m_metar
    painter.setPen(Qt::black);
    painter.drawText(left + 10 ,top ,160,30
                     ,Qt::AlignLeft
                     ,"系统最近更新时间戳");
    painter.drawText(left + 360 ,top ,160,30
                     ,Qt::AlignLeft
                     ,QString("%1").arg(m_upd_t));
    // real time reference data
    painter.setPen(Qt::gray);
    painter.setBrush(QColor("#D9D9D9"));
    for(int metarNum = 1;metarNum < 13;metarNum++){
        painter.drawRoundedRect(left + 97/*100*/,top + sHeight * metarNum / 13
                                ,sWidth - 100
                                ,sHeight / 13 - 8
                                ,10,10);
    }
    painter.setBrush(QColor("#7EC0EE"));
    for(int metarNum = 1;metarNum < 13;metarNum++){
        painter.drawRect(left + 3,top + sHeight * metarNum / 13
                         ,100/*sWidth - 6*/
                         ,sHeight / 13 - 8);
    }
    painter.setPen(Qt::black);
    for(int subTitleNum = 1;subTitleNum < 13;subTitleNum++){
        painter.drawText(left + 4,top + sHeight * subTitleNum / 13,100,
                         sHeight / 13 - 8
                         ,Qt::AlignVCenter | Qt::AlignLeft
                         ,m_subDataNameList[subTitleNum]);
    }
    painter.restore();
    painter.save();

    painter.drawText(left + 100+lenWidthOne - 20
                     ,top+ sHeight / 13
                     ,20,sHeight / 13 - 8
                     ,Qt::AlignCenter
                     ,"/");
    painter.drawText(left + 100 + 4 + subWidth  / 5+lenWidthOne - 20
                     ,top+ sHeight / 13
                     ,20,sHeight / 13 - 8
                     ,Qt::AlignCenter
                     ,"G");
    painter.drawText(left + 100 + 12 + subWidth  * 3 / 5+lenWidthOne - 20
                     ,top+ sHeight / 13
                     ,20,sHeight / 13 - 8
                     ,Qt::AlignCenter
                     ,"V");

    painter.drawText(left + 100+lenWidthOne - 20
                     ,top+ sHeight * 2 / 13
                     ,20,sHeight / 13 - 8
                     ,Qt::AlignCenter
                     ,"/");
    painter.drawText(left + 100 + 4 + subWidth  / 5+lenWidthOne - 20
                     ,top+ sHeight * 2 / 13
                     ,20,sHeight / 13 - 8
                     ,Qt::AlignCenter
                     ,"G");
    painter.drawText(left + 100 + 12 + subWidth  * 3 / 5+lenWidthOne - 20
                     ,top+ sHeight * 2 / 13
                     ,20,sHeight / 13 - 8
                     ,Qt::AlignCenter
                     ,"V");

    painter.drawText(left + 100+lenWidthOne - 20
                     ,top+ sHeight * 3 / 13
                     ,20,sHeight / 13 - 8
                     ,Qt::AlignCenter
                     ,"/");
    painter.drawText(left + 100 + 4 + subWidth  / 5+lenWidthOne - 20
                     ,top+ sHeight * 3 / 13
                     ,20,sHeight / 13 - 8
                     ,Qt::AlignCenter
                     ,"G");
    painter.drawText(left + 100 + 12 + subWidth  * 3 / 5+lenWidthOne - 20
                     ,top+ sHeight * 3 / 13
                     ,20,sHeight / 13 - 8
                     ,Qt::AlignCenter
                     ,"V");

    painter.drawText(left + 100 ,top +  sHeight * 4 / 13
                     ,(width()-100) / 7
                     ,sHeight / 13 - 8
                     ,Qt::AlignCenter
                     ,"十分钟平均");

    painter.drawText(left + 100 + (width()-100) * 2 / 7
                     ,top +  sHeight * 4 / 13
                     ,(width()-100) / 7
                     ,sHeight / 13 - 8
                     ,Qt::AlignCenter
                     ,"最小值");

    painter.drawText(left + 100 + (width()-100) * 4 / 7
                     ,top +  sHeight * 4 / 13
                     ,(width()-100) / 7
                     ,sHeight / 13 - 8
                     ,Qt::AlignCenter
                     ,"方向");

    painter.drawText(left + 100,top + sHeight * 12 / 13
                     ,100,sHeight / 13 - 8
                     ,Qt::AlignCenter
                     ,"现在天气");

    painter.drawText(left + 100 + (sWidth - 100) / 2 - 60
                     ,top +  sHeight * 12 / 13
                     ,100,sHeight / 13 - 8
                     ,Qt::AlignCenter
                     ,"近时天气");
    painter.restore();
}
