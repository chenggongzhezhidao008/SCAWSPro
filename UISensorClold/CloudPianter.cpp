#include "awossensorcloud.h"

void AwosSensorCloud::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing,true);
    int left = - width() / 2;
    int top = - height() / 2;
    int righ = width() / 2;
    int buttom = height() / 2;
    painter.translate(righ, buttom);
    painter.setPen(Qt::NoPen);

    //画区域背景
    painter.save();
    painter.setBrush(Qt::white);
    painter.drawRoundedRect(left,top,width() - 2,height() - 2,3,3);
    painter.setBrush(Qt::gray);
    painter.drawRoundedRect(left + 2,top + 2,width() - 2,height() - 2,3,3);
    painter.setBrush(QColor("#D9D9D9"));
    painter.drawRoundedRect(left + 2,top + 2,width() - 4,height() - 4,3,3);
    painter.restore();

    //画区域标题
    painter.save();

    //1.画标题背景
    QLinearGradient gradT(0,top,0,top + 35);
    gradT.setColorAt(0,Qt::gray);
    gradT.setColorAt(0.5,QColor("#D9D9D9"));
    painter.setBrush(gradT);
    painter.drawRoundedRect(left + 2,top + 2,width() - 4,35,3,3);

    //2.画标题字样
    painter.setPen(QPen(QColor("#4A708B"),4));
    painter.drawText(left / 2 ,top + 2,righ,16,
                          Qt::AlignCenter,QString("云高(%1)").arg(this->m_runWayStr));

    painter.restore();

    painter.save();
    QFont font = painter.font();
    font.setBold(true);
    painter.setFont(font);
    painter.setPen(QPen(QColor("#4A708B"),5));
    painter.drawText(left + 2,buttom - 18,(width() - 8)/ 3,16,Qt::AlignCenter,"一层");
    painter.drawText(left + 4 + (width() - 8) / 3,buttom - 18,(width() - 8)/ 3,16,Qt::AlignCenter,"二层");
    painter.drawText(left + 6 + (width() - 8) * 2 / 3,buttom - 18,(width() - 8)/ 3,16,Qt::AlignCenter,"三层");
    painter.restore();

    painter.save();
    painter.setBrush(QColor("#F0F8FF"));
    painter.drawRoundedRect(left + 4,top + 19,(width() - 16)/ 3,height() - 40,6,6);
    painter.drawRoundedRect(left + 8 + (width() - 16) / 3,top + 19,(width() - 16)/ 3,height() - 40,6,6);
    painter.drawRoundedRect(left + 12 + (width() - 16) * 2 / 3,top + 19,(width() - 16)/ 3,height() - 40,6,6);
    QFont Textfont = painter.font();
    Textfont.setBold(true);
    Textfont.setPixelSize(18);
    painter.setFont(Textfont);
    painter.setPen(QPen(Qt::black,5));
    painter.drawText(left + 2,top + 17,(width() - 8)/ 3,height() - 36,Qt::AlignCenter,m_firstlay.split(".").value(0));
    painter.drawText(left + 4 + (width() - 8) / 3,top + 17,(width() - 8)/ 3,height() - 36,Qt::AlignCenter,m_secondlay.split(".").value(0));
    painter.drawText(left + 6 + (width() - 8) * 2 / 3,top + 17,(width() - 8)/ 3,height() - 36,Qt::AlignCenter,m_thirdlay.split(".").value(0));
    painter.restore();
}

void AwosSensorCloud::initCloudHeight()
{
    m_firstlay = "///";
    m_secondlay = "///";
    m_thirdlay = "///";
}

void AwosSensorCloud::initLocation()
{
    m_location = "NULL";
}
