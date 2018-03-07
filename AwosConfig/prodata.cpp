#include "prodata.h"
#include <QDebug>
#include <QDir>

ProData::ProData(QObject *parent) :
    QObject(parent)
{
    this->m_strExeRoot = QApplication::applicationDirPath() + "/";
    QDir::setCurrent(QApplication::applicationDirPath());
    system         = new System();
    user           = new UserData();
    comm           = new Comm();

    //database
    databaseTables = new Database();
    loadIniFile();

    //awos partment
    awosDataModel  = new AwosData();
    waring         = new Warings();
    initAwosFile();
}

int ProData::loadIniFile()
{
    //初始化根文件
    QSettings *systemSeting = new QSettings(m_strExeRoot+"/config.ini",QSettings::IniFormat);
    systemSeting->setIniCodec("utf-8");
    system->systemFile = m_strExeRoot + systemSeting->value("AwosSystem/path").toString();
    system->dataFile = m_strExeRoot + systemSeting->value("AwosData/path").toString();
    delete systemSeting;
    //systemSeting->deleteLater();

    //   初始化系统配置文件
    QSettings *systemConfig = new QSettings(system->systemFile,QSettings::IniFormat);
    systemConfig->setIniCodec("utf-8");

    if((systemConfig->allKeys().length()) > 0){
        system->name = systemConfig->value("system/name").toString();
        system->version = systemConfig->value("system/version").toString();
        system->company = systemConfig->value("system/company").toString();
        comm->ip = systemConfig->value("comm/ip").toString();
        comm->reciPort = systemConfig->value("comm/receport").toInt();
        comm->sendPort = systemConfig->value("comm/sendport").toInt();
    }
    else
    {
        qDebug()<<"SC system config file lost;please check out the file.";
    }
     delete systemConfig;

    //   初始化数据配置文件
    QSettings *dataConfig = new QSettings(system->dataFile,QSettings::IniFormat);
    dataConfig->setIniCodec("utf-8");
    if((dataConfig->allKeys().length()) > 0)
    {
        int count = dataConfig->value("Data/count").toInt();
        for(int i = 1;i <= count ;i++)
        {
            if((dataConfig->value(QString("Data/enable%1").arg(i)).toBool()))
            {
                QString nameStr = dataConfig->value(QString("Data/name%1").arg(i)).toString();
                QString pathStr = m_strExeRoot + dataConfig->value(QString("Data/path%1").arg(i)).toString() + "/";
                if(nameStr == "user")
                {
                    user->userTablePath = pathStr;
                    user->tableUser = new QSettings(user->userTablePath + "user.ini",QSettings::IniFormat);
                    user->tableUser->setIniCodec("utf-8");
                }
                //数据库表格
                //数据库表格只有settings 成员和所有数据表格配置文件的总路径dataTablePath
                if(nameStr == "database")
                {
                    databaseTables->dataTablePath = pathStr;
                    databaseTables->tablesCloud = new QSettings(databaseTables->dataTablePath + "cloud.ini",QSettings::IniFormat);
                    databaseTables->tablesCloud->setIniCodec("utf-8");
                    databaseTables->tablesHumTemp = new QSettings(databaseTables->dataTablePath + "humtemp.ini",QSettings::IniFormat);
                    databaseTables->tablesHumTemp->setIniCodec("utf-8");
                    databaseTables->tablesPress = new QSettings(databaseTables->dataTablePath + "press.ini",QSettings::IniFormat);
                    databaseTables->tablesPress->setIniCodec("utf-8");
                    databaseTables->tablesRain = new QSettings(databaseTables->dataTablePath + "rain.ini",QSettings::IniFormat);
                    databaseTables->tablesRain->setIniCodec("utf-8");
                    databaseTables->tablesVIS = new QSettings(databaseTables->dataTablePath + "vis.ini",QSettings::IniFormat);
                    databaseTables->tablesVIS->setIniCodec("utf-8");
                    databaseTables->tablesWind = new QSettings(databaseTables->dataTablePath + "wind.ini",QSettings::IniFormat);
                    databaseTables->tablesWind->setIniCodec("utf-8");
                    databaseTables->tablesPW = new QSettings(databaseTables->dataTablePath + "pw.ini",QSettings::IniFormat);
                    databaseTables->tablesPW->setIniCodec("utf-8");
                    databaseTables->tablesPV = new QSettings(databaseTables->dataTablePath + "pv.ini",QSettings::IniFormat);
                    databaseTables->tablesPV->setIniCodec("utf-8");
                    databaseTables->tablesBIASLIGHT = new QSettings(databaseTables->dataTablePath + "backgrundlight.ini",QSettings::IniFormat);
                    databaseTables->tablesBIASLIGHT->setIniCodec("utf-8");
                    databaseTables->tablesManual = new QSettings(databaseTables->dataTablePath + "manual.ini",QSettings::IniFormat);
                    databaseTables->tablesManual->setIniCodec("utf-8");
                    databaseTables->tablesRunway = new QSettings(databaseTables->dataTablePath + "runway.ini",QSettings::IniFormat);
                    databaseTables->tablesRunway->setIniCodec("utf-8");
                    databaseTables->tableWaringIfo = new QSettings(databaseTables->dataTablePath + "waring.ini",QSettings::IniFormat);
                    databaseTables->tableWaringIfo->setIniCodec("utf-8");
                    databaseTables->tableOtherSensorUser = new QSettings(databaseTables->dataTablePath + "outSensor.ini",QSettings::IniFormat);
                    databaseTables->tableOtherSensorUser->setIniCodec("utf-8");
                }
            }
            else
            {
                continue;
            }
        }
    }
    else
    {
        qDebug()<<"SC system config file losted;";
    }
    delete dataConfig;
    return 1;
}

/* awos 数据关系 2017.5.9
 * AwosAirpotData(QObject *parent) 机场数据结构
 * initAwosIniFile() 初始化awos所有数据
 */

AwosData::AwosData(QObject *)
{
    airport = new AwosAirport();
    runwayInfor = new AwosRunway();
    inUsedWay = new AwosInUsedRunway();
    sensorList = new AwosSensorList();
    telegram = new AwosTelegram();
}

int ProData::initAwosFile()
{
    awosDataModel->awosDataPath = m_strExeRoot +"data/Awosdata/";
    awosDataModel->airport->awosAirportPath = awosDataModel->awosDataPath + "airport.ini";
    awosDataModel->airport->awosAirportSet = new QSettings(awosDataModel->airport->awosAirportPath,QSettings::IniFormat);
    awosDataModel->airport->awosAirportSet->setIniCodec("utf-8");
    awosDataModel->runwayInfor->awosRunWayPath = awosDataModel->awosDataPath + "runways.ini";
    awosDataModel->runwayInfor->awosRunWaySet = new QSettings(awosDataModel->runwayInfor->awosRunWayPath,QSettings::IniFormat);
    awosDataModel->runwayInfor->awosRunWaySet->setIniCodec("utf-8");
    awosDataModel->inUsedWay->awosRunwayAreasPath = awosDataModel->awosDataPath + "usedway.ini";
    awosDataModel->inUsedWay->awosRunwayAreasSet = new QSettings(awosDataModel->inUsedWay->awosRunwayAreasPath,QSettings::IniFormat);
    awosDataModel->inUsedWay->awosRunwayAreasSet->setIniCodec("utf-8");
    awosDataModel->sensorList->awosSensorListPath = awosDataModel->awosDataPath + "sensorList.ini";
    awosDataModel->sensorList->awosSensorListSet = new QSettings(awosDataModel->sensorList->awosSensorListPath,QSettings::IniFormat);
    awosDataModel->sensorList->awosSensorListSet->setIniCodec("utf-8");
    awosDataModel->telegram->awosTelegrmPath = awosDataModel->awosDataPath + "telegram.ini";
    awosDataModel->telegram->awosTelegrmSet = new QSettings(awosDataModel->telegram->awosTelegrmPath,QSettings::IniFormat);
    awosDataModel->telegram->awosTelegrmSet->setIniCodec("utf-8");
    return 1;
}

AwosInUsedRunway::AwosInUsedRunway(QObject * ){}
AwosAirport::AwosAirport(QObject * ){}
Warings::Warings(QObject *){}
Database::Database(QObject *){}
UserData::UserData(QObject *){}
AwosTelegram::AwosTelegram(QObject *){}
AwosRunway::AwosRunway(QObject *){}
AwosSensorList::AwosSensorList(QObject *){}
