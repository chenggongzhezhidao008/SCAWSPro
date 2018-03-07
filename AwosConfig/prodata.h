#ifndef PRODATA_H
#define PRODATA_H

#include <QObject>
#include <QVector>
#include <QApplication>
#include <QSettings>
#include "UISensorHumid/humidsensorout.h"
#include "UiSensorRunWay/runway.h"
#include "UiSensorRvr/rvrsensoruot.h"
#include "UISensorTemp/tempsensorshow.h"
#include "UiSensorWind/windmeter.h"
#include "UIWaveLine/waveline.h"
#include "windRoseArea/windrosearea.h"
#include "UISensorClold/awossensorcloud.h"
#include "UIPress/press.h"
#include "UIWeather/weather.h"
#include <QStringList>

//project object data
class UserData;
class System;
class Comm;
class Database;
class AwosData;
class Warings;
class ProData : public QObject
{
    Q_OBJECT
public:
    explicit ProData(QObject *parent = 0);
    UserData *user;
    System *system;
    Comm *comm;
    Database * databaseTables;

    int loadIniFile();//load all config file

    //Awos Data
    AwosData *awosDataModel;
    Warings *waring;
    int initAwosFile();

private:
    QString m_strExeRoot;// app path
};

//awos 数据 2017.5.9

// user data
class UserData : public QObject
{
    Q_OBJECT
public:
    explicit UserData(QObject *parent = 0);
    QString userTablePath;
    QSettings *tableUser;
};

//system file
class System
{
public:
    System() {}
    QString name;
    QString version;
    QString company;
    QString systemFile;
    QString dataFile;
};

//communicate file
class Comm
{
public:
    Comm() {}
    QString ip;
    int sendPort;
    int reciPort;
};

// database tables
class Database : public QObject
{
    Q_OBJECT
public:
    explicit Database(QObject *parent = 0);
    QString dataTablePath;
    QSettings *tablesCloud;
    QSettings *tablesHumTemp;
    QSettings *tablesPress;
    QSettings *tablesRain;
    QSettings *tablesVIS;
    QSettings *tablesWind;
    QSettings *tablesPW;
    QSettings *tablesPV;
    QSettings *tablesBIASLIGHT;
    QSettings *tablesManual;
    QSettings *tablesRunway;
    QSettings *tableWaringIfo;
    QSettings *tableOtherSensorUser;
};

// sensor data
class AwosAirport;
class AwosRunway;
class AwosInUsedRunway;
class AwosTelegram;
class AwosSensorList;
#include "windRoseArea/runwaydataarea.h"
#include "windRoseArea/windrosearea.h"
class AwosData : public QObject
{
    Q_OBJECT
public:
    explicit AwosData(QObject *parent = 0);
    QString awosDataPath;
    AwosAirport *airport;
    AwosRunway *runwayInfor;
    AwosInUsedRunway *inUsedWay;
    AwosSensorList *sensorList;
    AwosTelegram *telegram;
};

// warings
class Warings : public QObject
{
   Q_OBJECT
public:
   explicit Warings(QObject *parent = 0);
   QStringList notDealdList;
};


class AwosAirport : public QObject
{
    Q_OBJECT
public:
    explicit AwosAirport(QObject *parent = 0);
    QString awosAirportPath;
    QSettings *awosAirportSet;
};

class AwosRunway : public QObject
{
    Q_OBJECT
public:
    explicit AwosRunway(QObject *parent = 0);
    QString awosRunWayPath;
    QSettings *awosRunWaySet;
};

class AwosInUsedRunway : public QObject
{
    Q_OBJECT
public:
    explicit AwosInUsedRunway(QObject *parent = 0);
    QString awosRunwayAreasPath;
    QSettings *awosRunwayAreasSet;
    QVector<Press *> pressList;
    QVector<Weather *> weatherList;
    QVector<AwosSensorCloud *> cloudSensorList;
    QVector<RunWayDataArea *> dataAreaList;
    QVector<WindRoseArea *> roseAreaList;
    QVector<RunWay *> runwaylist;
    QList<QString> runwayNameAndIdList;
};

class AwosSensorList : public QObject
{
    Q_OBJECT
public:
    explicit AwosSensorList(QObject *parent = 0);
    QString awosSensorListPath;
    QSettings *awosSensorListSet;
};

class AwosTelegram : public QObject
{
    Q_OBJECT
public:
    explicit AwosTelegram(QObject *parent = 0);
    QString awosTelegrmPath;
    QSettings *awosTelegrmSet;
};

#endif // PRODATA_H
