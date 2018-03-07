#ifndef INSTALLCOM_SENSORCFG_H
#define INSTALLCOM_SENSORCFG_H

#include <QString>
#include <QWidget>
#include <QPainter>
#include <QPaintEvent>
#include <QScrollArea>
#include "deveices/glablecom_handinfor.h"
#include "deveices/glablecom_selectbutton.h"
typedef QMap<int,QString> InforMap;

typedef int SenNum;
typedef QString SenCtx;

//用于保存所有传感器及传感器的所有参数。
typedef QMap<SenNum,SenCtx> SenRecordData;
typedef QString InforName;
typedef QString InforCtx;
typedef QMap<InforName,InforCtx> InforData;

//用于外部传感器的信息显示列表
typedef QMap<QString,QString> DataMap;
typedef QMap<QString,DataMap> SensorMap;


class SensorCFGCom : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(QString idAirportId READ idAirportId WRITE setIdAirportId NOTIFY idAirportIdChanged)

public:
    explicit SensorCFGCom(QWidget *parent = 0);
    QString idAirportId() const;

protected:
    void paintEvent(QPaintEvent *e);

signals:
    void idAirportIdChanged();
    void MenuOptionSlot(QString option);

public slots:
    void setIdAirportId(QString value);
    void backRequeryAFFIX9menberSlot(QString query,InforData menber);

    // 外部传感器处理列表
    void externSensorDealList(SensorMap extenSensor);

private slots:
    void addDataToShow(QString kind);
    InforMap sensorDeal(InforMap one,InforMap two);
private:
    QString m_idAairportId;
    void initIdAairportId();

    int windRows;
    int RVRRows;
    int tempHumiRows;
    int customRows;
    void initRowsValue();

    InforMap windMap;
    InforMap RVRMap;
    InforMap tempHumiMap;
    InforMap customMap;

    int ext_windRows;
    int ext_RVRRows;
    int ext_tempHumiRows;
    int ext_customRows;
    void ext_setZeroRowsValue();

    InforMap ext_windMap;
    InforMap ext_RVRMap;
    InforMap ext_tempHumiMap;
    InforMap ext_customMap;


    glableHandInfor *wind;   //statue36:刷新
    glableHandInfor *RVR;
    glableHandInfor *tempHumi;
    glableHandInfor *custom;
    void initInforCom();
    void setHandInforGeomerty();
    void initCustomMenus();
    void initMenuDealsConnection();

    QScrollArea  *ScrollAreaWind;
    QScrollArea  *ScrollAreaRVR;
    QScrollArea  *ScrollAreaTempHumi;
    QScrollArea  *ScrollAreaCustom;
    void initScrollArea();
    void addSubWidget();
    void setInforComGeometry();

    GlableSelectButton *UpWind;
    GlableSelectButton *UpRVR;
    GlableSelectButton *UpTempHumi;
    GlableSelectButton *UpCustom;
    void initButton();
    void setButtonGeometry();

    int comWidth;
    int comHeight;
    void initsizeValue();

    // all sensors
    SenRecordData m_sensorRecords;
};

#endif // INSTALLCOM_SENSORCFG_H
