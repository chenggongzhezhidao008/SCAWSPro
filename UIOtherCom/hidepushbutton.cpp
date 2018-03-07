#include "hidepushbutton.h"
#include <QDebug>

HidePushbutton::HidePushbutton(QWidget *parent) :
    QWidget(parent)
{
    clearTimer = new QTimer(this);
    connect(clearTimer,SIGNAL(timeout()),this,SLOT(clear()));
    clearTimer->start(3000);
    count = 0;
    flag = false;
    m_updateFlag = false;
}

void HidePushbutton::setSignalFlag(bool update)
{
    this->m_updateFlag = update;
}

void HidePushbutton::mousePressEvent(QMouseEvent *e)
{
    if(e->button() == Qt::LeftButton){//判断鼠标事件的按钮名称
        flag = true;
        count ++;
        if(count % 3 == 0){
            emit removeFilter(this->m_updateFlag);
        }
    }
    e->accept();//接收事件
}

void HidePushbutton::paintEvent(QPaintEvent *event)
{
  Q_UNUSED(event)
}

bool HidePushbutton::event(QEvent *event)
{
   if(event->type() == QEvent::ToolTip){
       qDebug()<<"SC 鼠标悬停！";
   }
   else if(event->type() == QEvent::Leave){
       qDebug()<<"SC 鼠标离开！";
   }
    return QWidget::event(event);
}

void HidePushbutton::clear()
{
    if(flag){
        count = 0;
        flag = false;
    }
}
