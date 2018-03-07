#include "glablecom_selectbutton.h"

GlableSelectButton::GlableSelectButton(QWidget *parent) :
    QWidget(parent)
{
    initValue();
    initButtonNameValue();
}

void GlableSelectButton::paintEvent(QPaintEvent *e)
{
    Q_UNUSED(e)
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing,true);
    painter.translate(width()/2,height()/2);

    painter.save();
    painter.setPen(Qt::NoPen);
    QPoint configStartPoint(0,0);
    QPoint configEndPoint(0,height());
    QLinearGradient gradMet1(configStartPoint,configEndPoint);
    QLinearGradient gradMet2(configStartPoint,configEndPoint);
    gradMet1.setColorAt(0,QColor("#4A708B"));
    gradMet1.setColorAt(1,QColor("#00688B"));
    gradMet2.setColorAt(0,QColor("#CAE1FF"));
    gradMet2.setColorAt(1,QColor("#B0E0E6"));
    if(!m_clicked){
        painter.setBrush(gradMet1);
    }
    else{
        painter.setBrush(gradMet2);
    }
    painter.drawRect(-width()/2,-height()/2,width(),height());
    painter.setPen(QPen(Qt::white,3));
    QFont f = painter.font();
    f.setBold(true);
    f.setPixelSize(12);
    painter.setFont(f);
    QString name;
    name = m_name.split(":").value(1).trimmed();
    painter.drawText(-width()/2,-height()/2,width(),height(),Qt::AlignCenter,name);
    painter.restore();
}

void GlableSelectButton::mousePressEvent(QMouseEvent *e)
{
    Q_UNUSED(e)
    m_clicked = true;
    m_release = true;
    emit buttonClick(m_name);
    update();
}

void GlableSelectButton::mouseReleaseEvent(QMouseEvent *e)
{
    Q_UNUSED(e)
    if(m_clicked){
        m_clicked = false;
    }
    if(m_release){
        update();
    }
}

void GlableSelectButton::initValue()
{
    m_clicked = false;
    m_release = false;
}

void GlableSelectButton::initButtonNameValue()
{
    m_name = "xxx:button";
}
