#include "workestationcfg.h"


WorkeStationCFG::WorkeStationCFG(QWidget *parent) :
    QWidget(parent)
{
    m_init_size();
    m_init_cfg();
    m_init_setting_vlaues();
}

void WorkeStationCFG::runWays_setting_config(QSettings *&sensor)
{
    m_runwayInfor  = sensor;
}

void WorkeStationCFG::usedWay_setting_config(QSettings *&sensor)
{
    m_usedRunWay  = sensor;
}

void WorkeStationCFG::paintEvent(QPaintEvent *e)
{
    Q_UNUSED(e)
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing,true);
    int _with = width();
    int _heigh = height();
    if(m_with != _with || m_heigh != _heigh){
        m_with = _with;
        m_heigh = _heigh;
        m_set_geometry();
    }
    painter.translate(_with / 2,_heigh / 2);
    painter.setPen(Qt::NoPen);

    //画区域背景
    painter.save();
    painter.setBrush(Qt::white);
    painter.drawRoundedRect(-_with / 2,-_heigh / 2,_with - 2,_heigh - 2,3,3);
    painter.setBrush(Qt::gray);
    painter.drawRoundedRect(-_with / 2 + 2,-_heigh / 2 + 2,_with - 2,_heigh - 2,3,3);
    painter.setBrush(QColor("#D9D9D9"));
    painter.drawRoundedRect(-_with / 2 + 2,-_heigh / 2 + 2,_with - 4,_heigh - 4,3,3);
    painter.restore();
    //    int v_left = -_with / 2 + 2;
    //    int v_top = -_heigh / 2 + 2;
    //    int v_width = _with - 4;
    //    int v_heigh = _heigh - 4;
}

void WorkeStationCFG::m_init_size()
{
    m_with = 0;
    m_heigh = 0;
}

void WorkeStationCFG::m_init_cfg()
{
    Cfg = new RunWayCFg(this);
    Cfg->_set_way_number(QString("15"),QString("33"));// TEST RUNWAY NUMBER
}

void WorkeStationCFG::m_set_geometry()
{
    Cfg->setGeometry(3,3,width() - 6,80);
}

void WorkeStationCFG::m_init_setting_vlaues()
{
    m_runwayInfor = NULL;
    m_usedRunWay = NULL;
}

