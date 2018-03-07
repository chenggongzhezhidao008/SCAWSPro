#ifndef TELECONFIG_H
#define TELECONFIG_H

#include <QWidget>
#include <QPainter>
#include <QPaintEvent>
#include <QMouseEvent>
#include <QDebug>
#include <QSettings>
#include "telecfgsubcom.h"
class TeleConfig : public QWidget
{
    Q_OBJECT
public:
    explicit TeleConfig(QWidget *parent = 0);

protected:
    void paintEvent(QPaintEvent *event);

signals:

public slots:
    void _m_update_ctrl_item(QString ctl_Items);
    void telegram_setting_config(QSettings *&telegramSensor);

private slots:
    void _m_set_metar_slot(QString set);
    void _m_set_spaci_slot(QString set);
    void _m_set_metar_report_slot(QString set);
    void _m_set_spaci_report_slot(QString set);

private:
    TeleCFGSubCom *m_metar_sub;
    TeleCFGSubCom *m_metar_report_sub;
    TeleCFGSubCom *m_spaci_sub;
    TeleCFGSubCom *m_spaci_report_sub;
    void _init_sub_coms();
    void _set_sub_coms_geometry();

    int _m_width;
    int _m_height;
    void _init_size_value();

    QSettings *m_telegramSensor;
    void m_init_telegram_sensors();
};

#endif // TELECONFIG_H
