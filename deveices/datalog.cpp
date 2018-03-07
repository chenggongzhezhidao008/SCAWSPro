#include "datalog.h"

DataLog::DataLog(QWidget *parent) :
    QWidget(parent)
{
    _m_init_log();
    _m_init_LogSize();
}

void DataLog::paintEvent(QPaintEvent *e)
{
    Q_UNUSED(e)
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing,true);
    if(width() != _m_width || height() != _m_height){
        _m_set_log_geometry();
        _m_width = width();
        _m_height = height();
    }
    int m_width = width();
    int m_height = height();
    int left = - m_width / 2;
    int top = - m_height / 2;
    int righ = m_width / 2;
    int buttom = m_height / 2;
    painter.translate(righ, buttom);
    painter.setPen(Qt::NoPen);

    //画区域背景
    painter.save();
    painter.setBrush(Qt::white);
    painter.drawRoundedRect(left,top,m_width - 2,m_height - 2,3,3);
    painter.setBrush(Qt::gray);
    painter.drawRoundedRect(left + 2,top + 2,m_width - 2,
                             m_height - 2,3,3);
    painter.setBrush(QColor("#D9D9D9"));
    painter.drawRoundedRect(left + 2,top + 2,m_width - 4,
                             m_height - 4,3,3);
    painter.restore();
}

void DataLog::add_log_record(QString logCtx,QString optioner)
{
    _m_log->_m_add_log_Slot(logCtx,optioner);
}

void DataLog::_m_init_log()
{
    _m_log = new LogShow(this);
}

void DataLog::_m_set_log_geometry()
{
     _m_log->setGeometry(2,2,width() - 2,height() - 2);
     add_log_record("system open succeed!","system");
}

void DataLog::_m_init_LogSize()
{
    _m_width = 0;
    _m_height = 0;
}

