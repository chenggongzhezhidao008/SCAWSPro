#ifndef WORKESTATIONCFG_H
#define WORKESTATIONCFG_H

#include <QWidget>
#include <QPainter>
#include <QPaintEvent>
#include <QSettings>
#include "runwaycfg.h"


class WorkeStationCFG : public QWidget
{
    Q_OBJECT
public:
    explicit WorkeStationCFG(QWidget *parent = 0);

protected:
    void paintEvent(QPaintEvent *e);

signals:

public slots:
    void runWays_setting_config(QSettings *&sensor);
    void usedWay_setting_config(QSettings *&sensor);

private:
    int m_with;
    int m_heigh;
    void m_init_size();

    RunWayCFg * Cfg;
    void m_init_cfg();
    void m_set_geometry();

    // locate config;
    QSettings *m_runwayInfor;
    QSettings *m_usedRunWay;
    void m_init_setting_vlaues();
};

#endif // WORKESTATIONCFG_H
