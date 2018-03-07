#include "atcmainsublineshowcom.h"

atcMainSubLineShowCom::atcMainSubLineShowCom(QWidget *parent) :
    QWidget(parent)
{
    initCountValue();
    initVlaueStr();
    initValueSize();
    initWaringValue();
    initUnit();
}

void atcMainSubLineShowCom::paintEvent(QPaintEvent *e)
{
    Q_UNUSED(e);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing,true);
    painter.translate( width() / 2, height() / 2);
    painter.setPen(Qt::NoPen);

    painter.save();
    if(m_Waring){
        painter.setBrush(QColor("#CDCD00"));
        QRect waringRect1(- width() / 2 + 1.5,- height() / 2 + 1.5, width() - 3, height() - 3);
        painter.drawRoundRect(waringRect1,12,16);
    }
    else{
        painter.setBrush(QBrush(QColor("#C9C9C9")));
        QRect waringRect2(- width() / 2 + 1.5,- height() / 2 + 1.5, width() - 3, height() - 3);
        painter.drawRoundRect(waringRect2,12,16);
    }
    painter.restore();
    painter.save();
    painter.setBrush(QColor("#F0F8FF"));
    painter.drawRect(-(width() / 2) + 6,-(height() / 2) + 6,width() - 12,height() - 12);
    painter.restore();

    painter.save();
    painter.restore();

    //绘制内容
    painter.save();
    if(m_Waring){ //告警闪烁
        if(m_count % 2 == 0){
            painter.setPen(QColor("#CDCD00"));
            painter.setBrush(QColor("#FF0000"));
        }
        else{
            painter.setPen(QColor("#0000FF"));
            painter.setBrush(QColor("#CDCD00"));
        }
        m_count ++;
    }
    else{
        painter.setPen(QColor("#F0F8FF"));
    }

    painter.drawRoundedRect(-width() / 2 + width() * 4 / 5 + 8,-6,6,6,3,3);
    painter.setPen(Qt::black);
    painter.drawText(width() / 10 + 3,-height() / 2 + 6,width() / 5,height() / 2 - 3,Qt::AlignBottom |Qt::AlignRight,m_unit);
    QFont fontRVRValue = painter.font();
    fontRVRValue.setPixelSize(m_fontSize);
    fontRVRValue.setBold(true);
    painter.setFont(fontRVRValue);
    QRectF RVRValueRect = QRectF(-width() / 2 + 1.5,-height() / 2 + 1.5,width() * 3 / 5,height() - 3);
    painter.drawText(RVRValueRect,Qt::AlignCenter,m_Text);
    painter.restore();
}

void atcMainSubLineShowCom::initCountValue()
{
    m_count = 0;
}

void atcMainSubLineShowCom::initVlaueStr()
{
    m_Text = "06";
}

void atcMainSubLineShowCom::initValueSize()
{
    m_fontSize = 16;
}

void atcMainSubLineShowCom::initWaringValue()
{
    m_Waring = false;
}

void atcMainSubLineShowCom::initUnit()
{
    m_unit = "unit";
}
