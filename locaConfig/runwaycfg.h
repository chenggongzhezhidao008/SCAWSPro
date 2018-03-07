#ifndef RUNWAYCFG_H
#define RUNWAYCFG_H

#include <QWidget>
#include <QPainter>
#include <QPaintEvent>
#include "UiSensorRunWay/runway.h"
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QComboBox>
#include <QCheckBox>

class RunWayCFg : public QWidget
{
    Q_OBJECT
public:
    explicit RunWayCFg(QWidget *parent = 0);

protected:
    void paintEvent(QPaintEvent *e);
    bool eventFilter(QObject *obj, QEvent *event);

signals:
    void _select_runway_signal(QString runWayStr);
    void _select_sensor_signal(QString snesorInfoStr);

public slots:
    void _set_way_number(QString headStr,QString rearStr);

private slots:
    void _select_way_slot(bool select);
    void _select_sensor_slot(QString str);

private:
    int m_with;
    int m_heigh;
    void m_init_size();

    RunWay *m_runway;
    void m_init_runway();
    void m_set_runway_Geometry();

    // 跑道选择
    QCheckBox *m_check;

    // 气压组
    QLabel *Mpresslab; QComboBox *MpressBox;

    // 风组
    QLabel *Lwindlab; QComboBox *LwindBox;
    QLabel *Mwindlab; QComboBox *MwindBox;
    QLabel *Rwindlab; QComboBox *RwindBox;

    // 云组
    QLabel *Lcloudlab; QComboBox *LcloudBox;
    //    QLabel *Mcloudlab; QComboBox *McloudBox;
    QLabel *Rcloudlab; QComboBox *RcloudBox;

    // 温湿度组
    QLabel *Lhumtemplab; QComboBox *LhumtempBox;
    QLabel *Mhumtemplab; QComboBox *MhumtempBox;
    QLabel *Rhumtemplab; QComboBox *RhumtempBox;

    // 能见度组
    QLabel *Lvislab; QComboBox *LvisBox;
    QLabel *Mvislab; QComboBox *MvisBox;
    QLabel *Rvislab; QComboBox *RvisBox;

    // 雨组
    QLabel *Lrainlab; QComboBox *LrainBox;
    QLabel *Mrainlab; QComboBox *MrainBox;
    QLabel *Rrainlab; QComboBox *RrainBox;
    void m_init_contrls();
    void m_set_contrls_geometry();
    void m_init_connections();

    QString runwayStr;
};

#endif // RUNWAYCFG_H
