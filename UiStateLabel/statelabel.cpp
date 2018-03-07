#include "statelabel.h"

StateLabel::StateLabel(QWidget *parent) :
    QWidget(parent)
{
//    painter = NULL;
    m_sensorId = 0;
    m_comId = 0;
    m_comName = "name";
    m_state = "connecting";
    m_fontSize = 16;
    //    m_data = "///";
    //    m_dataColor = "#ff0000";
}

void StateLabel::setSensorId(int senId)
{
    this->m_sensorId = senId;
    update();
}

void StateLabel::setComId(int comId)
{
    this->m_comId = comId;
    update();
}

void StateLabel::setComName(QString comName)
{
    this->m_comName = comName;
    update();
}

void StateLabel::setState(QString state)
{
    this->m_state = state;
    update();
}

void StateLabel::setFontSize(int size)
{
    this->m_fontSize = size;
    update();
}

//void StateLabel::setData(QString data)
//{
//    this->m_data = data;
//    update();
//}

//void StateLabel::setDataColor(QString colorHexStr)
//{
//    this->m_dataColor = colorHexStr;
//    update();
//}

void StateLabel::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing,true);
    painter.translate(this->width() / 2,this->height() / 2);
    painter.setPen(Qt::NoPen);
    //***************
    painter.save();
    QPen pen;
    pen.setWidth(2);
    pen.setColor(Qt::gray);
    painter.setPen(pen);
    painter.setBrush(palette().background());
    painter.drawRoundRect(-(this->width() / 2),-(this->height() / 2),this->width(),this->height());
    painter.restore();
    //*************** status name
    painter.save();
    painter.setPen(QColor("#E6E6FA"));/*Qt::green*/
    QFont font = painter.font();
    font.setBold(true);
    font.setPixelSize(this->m_fontSize);
    painter.setFont(font);
    QRect textRect(-(this->width() / 2),-(this->height() / 2),this->width() / 3,this->height());
    painter.drawText(textRect,Qt::AlignLeft | Qt::AlignVCenter,this->m_comName);
    painter.restore();
    //***************
    painter.save();
    QLinearGradient linearGrad(QPointF((this->width() / 2) - this->height() -1,-(this->height() / 2) + 1),
                               QPointF(this->height() - 2,this->height() -2));

    if(m_state == "connecting"){
        linearGrad.setColorAt(0, Qt::black);
        linearGrad.setColorAt(1, Qt::white);
    }
    else if( m_state == "disconnected"){
        linearGrad.setColorAt(0, Qt::white);
        linearGrad.setColorAt(0.5, Qt::red);
    }
    else if(m_state == "OnLine"){
        linearGrad.setColorAt(0, Qt::white);
        linearGrad.setColorAt(0.5, Qt::green);
    }
    painter.setBrush(linearGrad);
    QRect stateFontRect((this->width() / 2) - this->height() -1,-(this->height() / 2) + 1,
                        this->height() - 2,this->height() -2);
    painter.drawRoundedRect(stateFontRect,(this->height()+2) / 2,(this->height()+2) / 2);
    //    QString text;
    //    if(m_state == "connecting"){
    //        painter.setPen(QColor("#4F4F4F"));
    //        text = "Start..";
    //    }
    //    else if( m_state == "disconnected"){
    //        painter.setPen(QColor("#FF0000"));
    //        text = "NotOnLine";
    //    }
    //    else if(m_state == "OnLine"){
    //        painter.setPen(QColor("#00FF00"));
    //        text = "OnLine";
    //    }
    //    QFont stateFont = painter.font();
    //    stateFont.setPixelSize(16);
    //    stateFont.setBold(true);
    //    painter.setFont(stateFont);
    //    painter.drawText(stateFontRect,Qt::AlignCenter,text);
    painter.restore();
}
