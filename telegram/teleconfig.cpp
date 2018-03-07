#include "teleconfig.h"

TeleConfig::TeleConfig(QWidget *parent) :
    QWidget(parent)
{
    _init_sub_coms();
    _init_size_value();
    m_init_telegram_sensors();
}

void TeleConfig::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing,true);
    painter.translate(width()/2,height()/2);
    if(_m_width != width() || _m_height != height()){
        _m_width = width();
        _m_height = height();
        _set_sub_coms_geometry();
    }
    int left = - width() / 2;
    int top = - height() / 2 ;
    int m_width = width();
    int m_title_width = (width()-10)/4;
    int m_title_height = 16;
    int m_height = height();

    // title draw.
    painter.save();
    painter.setPen(QPen(QColor("#4A708B"),1));
    painter.drawRoundedRect(left+1,top ,m_width,m_height,4,4);
    painter.drawRoundedRect(left+2,top ,m_title_width,m_height,4,4);
    painter.drawRoundedRect(left+m_title_width+5,top ,m_title_width,m_height,4,4);
    painter.drawRoundedRect(left+m_title_width*2+8,top ,m_title_width,m_height,4,4);
    painter.drawRoundedRect(left+m_title_width*3+11,top ,m_title_width,m_height,4,4);
    painter.setBrush(QColor("#F0F8FF"));
    painter.setPen(QPen(QColor("#4A708B"),1));
    painter.drawRoundedRect(left+2,top ,m_title_width,m_title_height,4,4);
    painter.drawRoundedRect(left+m_title_width+5,top ,m_title_width,m_title_height,4,4);
    painter.drawRoundedRect(left+m_title_width*2+8,top ,m_title_width,m_title_height,4,4);
    painter.drawRoundedRect(left+m_title_width*3+11,top ,m_title_width,m_title_height,4,4);
    painter.drawText(left+2,top ,m_title_width,m_title_height
                     ,Qt::AlignBottom | Qt::AlignHCenter,"METAR");
    painter.drawText(left+m_title_width+4,top ,m_title_width,m_title_height
                     ,Qt::AlignBottom | Qt::AlignHCenter,"METARREPORT");
    painter.drawText(left+m_title_width*2+6,top ,m_title_width,m_title_height
                     ,Qt::AlignBottom | Qt::AlignHCenter,"SPACI");
    painter.drawText(left+m_title_width*3+8,top ,m_title_width,m_title_height
                     ,Qt::AlignBottom | Qt::AlignHCenter,"SPACIREPORT");
    painter.restore();
}

void TeleConfig::_m_update_ctrl_item(QString ctl_Items)
{
    _m_set_metar_slot(ctl_Items);
    _m_set_spaci_slot(ctl_Items);
    _m_set_metar_report_slot(ctl_Items);
    _m_set_spaci_report_slot(ctl_Items);
}

void TeleConfig::telegram_setting_config(QSettings *&telegramSensor)
{
    m_telegramSensor = telegramSensor;
}

void TeleConfig::_m_set_metar_slot(QString set)
{
    m_metar_sub->m_update_items(set);
}

void TeleConfig::_m_set_spaci_slot(QString set)
{
    m_metar_report_sub->m_update_items(set);
}

void TeleConfig::_m_set_metar_report_slot(QString set)
{
    m_spaci_sub->m_update_items(set);
}

void TeleConfig::_m_set_spaci_report_slot(QString set)
{
    m_spaci_report_sub->m_update_items(set);
}

void TeleConfig::_init_sub_coms()
{
    m_metar_sub = new TeleCFGSubCom(this);
    m_metar_report_sub = new TeleCFGSubCom(this);
    m_spaci_sub = new TeleCFGSubCom(this);
    m_spaci_report_sub = new TeleCFGSubCom(this);
}

void TeleConfig::_set_sub_coms_geometry()
{
    int t_width = (width()-10)/4;
    m_metar_sub->setGeometry(3,17,t_width,height());
    m_metar_report_sub->setGeometry(t_width+6,17,t_width,height());
    m_spaci_sub->setGeometry(t_width*2+9,17,t_width,height());
    m_spaci_report_sub->setGeometry(t_width*3+12,17,t_width,height());
}

void TeleConfig::_init_size_value()
{
    _m_width = 0;
    _m_height = 0;
}

void TeleConfig::m_init_telegram_sensors()
{
    m_telegramSensor = NULL;
}
