#ifndef AFFIX9MESAGE_H
#define AFFIX9MESAGE_H

// card communicate config file
#include "affix9communicateset.h"
// add sensor config head file
#include "affix9addsensor.h"
//edit 3616 ip config file
#include "IpEdit/ip36edit.h"
// edit outside virtual sensors
#include "AFFIX9Message/affix9addoutsensor.h"

#include <QObject>
#include <QQueue>
#include <QString>
#include <QDebug>
#include <QMap>
#include <QVector>

typedef QMap<QString,QString> DataMap;
typedef QMap<QString,DataMap> SensorMap;

typedef QVector<AFFIX9ConfirmWind * > CardComm;
typedef QVector<AFFIX9AddSensor * > SenSorADD;
typedef QVector<Affix9AddOutSensor *> VirtualSensor;

typedef QQueue<QString> SC_COMMD;
typedef QString InforName;
typedef QString InforCtx;
typedef QMap<InforName,InforCtx> InforData;

typedef QString SenClassName;
typedef QString SendNameValueS;
typedef QMap<SenClassName,SendNameValueS> SenClassData;

class AFFIX9Mesage : public QObject
{
    Q_OBJECT
public:
    explicit AFFIX9Mesage(QObject *parent = 0);

signals:
    // this signal is used to send command of Affix9 Message Form
    void AFFIX9Message(QString headName,SC_COMMD commd);
    // this signal is used to back Affix9 menber data.
    void backRequeryAFFIX9menberSignal(QString requery,InforData menber);
    // this signal is used to back Affix9 SensorOut data.
    void backRequeryAffix9_out_sensor_menber_Signal(QString requery,InforData menber);
    // this signal is used to due message in this class
    void AFFIX9LocationDataDueSignal(QString optionStr);
    // this signal is used to send up AFFIX9 Message Data
    void AFFIX9NewMessageSendUp(QString dCtx,InforData data);
    // this signal is used to store data to database
    void storeAffix9ToDatabaseSignal(QString table,QString storeData);
    // state back and them update all sensor devices;
    void update_all_sensor_devices(QString type);

    void send_self_signal(QString commd);

public slots:
    void AFFIX9CommandOptions(QString optionStr);
    QString findAppointKeyValue(QString dataPart,QString key);
    QStringList findAppointKeyValues(InforData dataPart,QString key);
    void _Store_3616_Deceive_Infor(SensorMap data);
    void storeAffix9ToDatabaseSolt(QString storeData);

private:
    void addInfor(QString ctxStr,InforData *m_data,bool clearFlage = true);
    Ip36Edit *_3616_ipEdit;
    void init3616IpEdit();

private:
    InforData m_airPort;
    InforData m_runWay;
    InforData m_3616;
    InforData m_state36;
    InforData m_libary;
    InforData m_openModels;
    InforData m_cardCommunicate;
    InforData m_sensor;
    InforData m_basiLight;

    InforData findSensorInfoByClass(QString sClass);

    void openCommunicateSet(QString index);
    void closeCommunicateSet();
    CardComm cardVec;

    //sensor options
    SenClassData m_ClassStore;
    void initSensorClassData();
    SenClassData m_realExistSensor;
    void classfiySensors();

    SenSorADD sensorVec;
    void openSensorAdd(QString sClass);
    void openFram(QString name);
    void closeFram(QString deleteName);

    VirtualSensor outSensorVec;
    void openVirtualSenorAdd(QString sClass);

    int n_wind;
    int n_vis;
    int n_humitemp;
    int n_custom;
    void initNumberValue();

    QStringList libList;
    void initLib(QString libClass);
    void initAFFIX9LocaDataDueConn();

    QString _3616_Id;
    QString _3616_AirId;
    QString _airport_name;
    void _init_Deceive_3616_infor();

    QString upadte_sensor_type_str;
    void _init_update_sensor_type_value();

    void init_local_connection();
};

#endif // AFFIX9MESAGE_H
