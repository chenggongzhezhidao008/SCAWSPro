#ifndef DEVEICESTATECONTROL_H
#define DEVEICESTATECONTROL_H

#include "UI3616/dealcenter3616.h"
#include <QWidget>
#include <QPainter>
#include <QPaintEvent>
#include <QMap>
#include <QDebug>
#include <QPushButton> // RVR 参数调整隐藏按钮
#include <QTimer> // RVR 配置数据清除时钟
#include <QMouseEvent> // RVR 配置

typedef QMap <int,QString> SerialMap;
typedef QString InforName;
typedef QString InforCtx;
typedef QMap<InforName,InforCtx> InforData;

class deveiceStateControl : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(int deveice3616ID READ getDeveice3616ID WRITE setDeveice3616ID NOTIFY deveice3616IDChanged)
    Q_PROPERTY(SerialMap modleNameList READ getModleNameList WRITE setModleNameList NOTIFY modleNameListChanged)
    Q_PROPERTY(SerialMap sensorsNameMap READ getSensorsNameMap WRITE setSensorsNameMap NOTIFY sensorsNameMapChanged)

public:
    explicit deveiceStateControl(QWidget *parent = 0);
    int getDeveice3616ID() const { return this->m_3616Id;}
    SerialMap getModleNameList() const { return this->m_modelMap;}
    SerialMap getSensorsNameMap() const { return this->m_sensorNameMap;}

protected:
    void paintEvent(QPaintEvent *e);
    void mousePressEvent(QMouseEvent *e);

public slots:
    void setDeveice3616ID(int id);
    void setModleNameList(SerialMap modleNameMap);
    void setSensorsNameMap(SerialMap nameMap);
    void AFFIX9NewMessageSendUp(QString dCtx,InforData data);
    void remberTime(); // rvr 配置参数
    void do_rvr_config(); // rvr 配置参数

signals:
    void deveice3616IDChanged();
    void modleNameListChanged();
    void sensorsNameMapChanged();
    void cofg_rvr_values();

private:
    int m_3616Id;
    SerialMap titleMap;
    SerialMap cardMap;
    SerialMap m_modelMap;
    SerialMap m_sensorNameMap;
    SerialMap modeStateMap;
    SerialMap sensorStateMap;
    SerialMap sensorIdMap;
    SerialMap beyonRunWayMap;

    // store model Open Sate;
    InforData m_openModel;
    void updateSate();

    //QPushButton * m_rvr_set; // rvr 配置参数
    QTimer * m_time;   // rvr 配置参数
    int m_number;
    void m_init_push_button(); // rvr 配置参数
    void m_set_rvr_geomerty();
    int m_width;
    int m_height;
    void m_init_size();

    DealCenter3616 * center3616UI;
    bool m_select;
    void m_init_instance();
    void m_init_setGeomerty();

};

#endif // DEVEICESTATECONTROL_H
