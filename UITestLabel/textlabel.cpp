#include "textlabel.h"

TEXTLabel::TEXTLabel(QWidget *parent) :
    QWidget(parent)
{
//    painter = NULL;
    this->m_color = QColor("#E6E6FA");
    this->m_size = 16;
    this->m_border = false;
    this->m_unit = "";
}

void TEXTLabel::setText(QString text)
{
    this->m_text = text;
    update();
}

void TEXTLabel::setTextColor(QColor color)
{
    this->m_color = color;
    update();
}

void TEXTLabel::setBorder(bool border)
{
    this->m_border = border;
    update();
}

void TEXTLabel::setUnitStr(QString unit)
{
    this->m_unit = unit;
}

void TEXTLabel::setFontSize(int size)
{
    this->m_size = size;
    update();
}

void TEXTLabel::paintEvent(QPaintEvent *e)
{
    Q_UNUSED(e);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing,true);
    painter.translate(this->width() / 2, this->height() / 2);
    QRect fontRect(- this->width() / 2,- this->height() / 2,this->width(),this->height());
    //=========******have border
    painter.save();
    if(this->m_border){
        painter.setPen(this->m_color);
    }
    else{
        painter.setPen(Qt::NoPen);
    }
    painter.drawRoundRect(fontRect);
    painter.restore();
    //=========****** only have context of label
    if(this->m_unit == ""){
        painter.save();
        painter.setPen(this->m_color);
        QFont font = painter.font();
        font.setBold(true);
        font.setPixelSize(this->m_size);
        painter.setFont(font);
        painter.drawText(fontRect,Qt::AlignCenter,this->m_text);
        painter.restore();
    }
    else{
        //=========****** have unit and context of label
        painter.save();
        painter.setPen(this->m_color);
        QFont font = painter.font();
        font.setPixelSize(this->m_size);
        font.setBold(true);
        painter.setFont(font);
        QRect fontTextRect(- this->width() / 2,- this->height() / 2,this->width()*2 / 3,this->height());
        painter.drawText(fontTextRect,Qt::AlignCenter|Qt::AlignRight,this->m_text);
        if(this->m_unit == "oc"){
            QRect fontUnitRect1(this->width() / 6,- this->height() / 2,this->width() / 6,this->height() * 2 / 3 );
            painter.drawText(fontUnitRect1,Qt::AlignCenter,"o");
            QRect fontUnitRect2(this->width() * 2 / 6,- this->height() / 2,this->width() / 6,this->height());
            painter.drawText(fontUnitRect2,Qt::AlignCenter,"C");
        }
        else{
            QRect fontUnitRect(this->width() / 6,- this->height() / 2,this->width() / 3,this->height());
            painter.drawText(fontUnitRect,Qt::AlignCenter|Qt::AlignLeft,this->m_unit);
        }
        painter.restore();
    }
}
