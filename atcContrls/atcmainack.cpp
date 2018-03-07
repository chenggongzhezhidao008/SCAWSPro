#include "atcmainack.h"

atcMainACK::atcMainACK(QWidget *parent) :
    QWidget(parent)
{
    iniReleaseBoolValue();
    initAckvalue();
}

void atcMainACK::paintEvent(QPaintEvent *e)
{
    Q_UNUSED(e)
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing,true);
    painter.translate(width() / 2,height() / 2);
    painter.save();
    if(ackClickBool){
        painter.setBrush(QColor("#E8E8E8"));
    }
    else{
        painter.setBrush(QColor("#E0FFFF"));
    }
    painter.drawRoundedRect(-width() / 2 + 2,-height() / 2 + 2,width() / 17,height()- 4,6,6);
    painter.restore();
    painter.save();
    QFont f= painter.font();
    f.setPixelSize(23);
    painter.setFont(f);
    painter.drawText(-width() / 2 + 2,-height() / 2 + 2,width() / 17,height()- 4,Qt::AlignCenter,"ACK");
    painter.restore();
    painter.save();
    painter.setBrush(Qt::white);
    painter.drawRect(-width() / 2 + width() / 17+ 2,-height() / 2 + 2,width() * 16 / 17 - 4,height()- 4);
    painter.restore();
}

void atcMainACK::mousePressEvent(QMouseEvent *e)
{
  bool updateFlag = false;
  if(e->button() == Qt::LeftButton){
      int posX = e->pos().x();
      int posY = e->pos().y();
      if(posX > 2 && posX < (width() / 17) &&
              posY > 2 && posY < (height()- 4)){
          updateFlag = true;
          m_releaseBool = true;
          ackClickBool = true;
          qDebug()<<"clicked";
      }
  }
  if(updateFlag){
      update();
  }
}

void atcMainACK::mouseReleaseEvent(QMouseEvent *e)
{
    Q_UNUSED(e)

    if(ackClickBool){
        ackClickBool = false;
        qDebug()<<"ack";
    }

    if(m_releaseBool){
        m_releaseBool = false;
        update();
        qDebug()<<"update";
    }
}

void atcMainACK::iniReleaseBoolValue()
{
    m_releaseBool = false;
}

void atcMainACK::initAckvalue()
{
    ackClickBool = false;
}
