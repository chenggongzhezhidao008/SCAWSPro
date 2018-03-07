#ifndef SUBINSTALLCFG_H
#define SUBINSTALLCFG_H

#include <QWidget>
#include <QPainter>
#include <QPaintEvent>
#include <QTabWidget>
#include <QWidget>
#include <QDebug>

#include "deveices/installcom_airportcfg.h"
#include "deveices/installcom_testportcfg.h"
#include "deveices/installcom_unit3616cfg.h"
#include "deveices/installcom_sensorcfg.h"

typedef QMap<QString,QString> DataMap;
typedef QMap<QString,DataMap> SensorMap;
typedef QString InforName;
typedef QString InforCtx;
typedef QMap<InforName,InforCtx> InforData;

class InstallCFG : public QWidget
{
    Q_OBJECT

public:
    explicit InstallCFG(QWidget *parent = 0);


protected:
    void paintEvent(QPaintEvent *e);

signals:

    //3616 自身配置文档V10.(根据合肥机场的信息调整的3616的配置)
    void backAirInfoSignal(SensorMap map);
    void backRunwayInfoSignal(SensorMap map);
    void backMatchInfoSignal(SensorMap map);

    //3616 自身配置文档V10.
    void Configure3616Signal(SensorMap senMap);
    void sensorStatusSignal(SensorMap senMap);
    void sensorLIBsSignal(SensorMap senMap);
    void serialCardParamersSignal(SensorMap senMap);

    // 系统部分，设备配置操作的附件9的配置信号
    void CFGOptions(QString optionStr);

    // 查询AFFix 9 后返回的信息
    void backRequeryAFFIX9menberSignal(QString query,InforData menber);

    // Affix 9 上传的数据
     void AFFIX9NewMessageSendUp(QString dCtx,InforData data);

    // 外部传感器信号
     void ExternSensorInfoListSignale(SensorMap map);

public slots:

private:
    QTabWidget *installTabWidget;
    void initInstallTabWidget();
    void setShapeInstallTabWidget();
    void setLocationInstallTabWidget();
    void addIstallTab();
    void setTabWidgetGeomerty();

    int paintWidth;
    int paintHeght;
    void initSizeValue();

    AirportCFGCom *w_airport;
    Unit3616CFGCom *w_3616;
    SensorCFGCom *w_sensor;
    TestPortCFGCom *w_testPort;
    void initWidgetsObj();
    void initAirportCfgConnection();
    void init36selfCfgConnetion();
    void initSensorCFGConnection();
    void initTestCFgConnection();
    void initCFGoptionSingnalConnection();
};

#endif // SUBINSTALLCFG_H
