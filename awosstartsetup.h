#ifndef AWOSSTARTSETUP_H
#define AWOSSTARTSETUP_H

#include "awoscomm.h"
#include <QMap>
#include <QTimer>
#include <QObject>
#include <QWidget>
#include <QStringList>
#include <QSound>
typedef QString InforName;
typedef QString InforCtx;
typedef QMap<QString,bool> WaringTepy;
typedef QMap<InforName,InforCtx> InforData;
typedef QMap<QString,QString> userMap;

class AwosStartSetup : public QObject
{
    Q_OBJECT
public:
    explicit AwosStartSetup(QObject *parent = 0);
    int startLogin();

private:
    //setup functions
    void initSetupInfo();//init system setup data
    void setupZmq();//init communicate
    void setupRemote4G();//init remote 4G
    void setupMessageParse();//setup message parse
    void initAwosUIObject();//init AwosUI object
    void setMainUI(QVariant ** mainUi);//set main ui object
    int  loadAwosUiFile(); //init awos syustem ui
    void initMessageComplex(); //init Message Data complex
    void init4GMessageSendSignal(); //init 4G message data send signal
    void initZmqMessageSendSignal(); //init internet message data send signal
    void initCommunicateStateUieditDataparseSignals(); //init communication ,state,ui edit,data parse signals and connections
    void initDatabaseObj(); //init database store form
    void initLogin(); //init login object
    void initLoginConnect(); //init login connect signal and slots
    void initAllSensorDataTables(); //init tables of database
    void initSensorDataStoreSignals(); //init sensor data store siganls
    void setupAwosSystemUI();//Awos system UI setup
    void initScaleSubContrlConnection();// init sub Contrl size
    void initWaringConnection(); //init minawos waring show and deal connection
    void optionContrlShowOrCloseConnection();// wind rose contrl data contrl run way contrl
    void initMessagesSendConnection();//init message send connections
    void initTelegramRealTimeSystemDatas(); // init telegram  init datas
    void initTelegramSystemDataConnection(); //init telegram  real data
    void initDeviceCFGConnection();
    void initTestPortCFGConnection();
    void init36CFGConnection();// init 3616 self config connection
    void initAFFIX9Message();// init affix 9 obj
    void initAffix9MessagesCommandConnetion();//send to 36
    void initHeartbeatContrlConnect();// init heartbeat contrls.
    void updateAllSystemInformations();// 首次刷新界面的各个数据列表
    void initTrendMetarOption();
    void allotUserPower();// 分配用户权限
    void _init_user_Manage();//用户编辑
    void init_rvrPolluteCfg();

private slots:
    void initStartSystem();
    void scaleSubContrls();
    void heartbeatContrl(QString str);
    void rebootZmqChick();

    // user options slots
    void _set_options_(QString data);

    // 首次刷新各个采集卡的配置情况
    void updataAllSensorDatas(QString type);

signals:
    void loginPassSate(QString pass);
    void updateSub();

    //Waring message send signal
    void waringMessageList(QStringList waringNotDealList);
    void waringMessageStr(SensorMap senMap);
    void updateTelegramRealTimeData(realDataMap datamap,QString affixOption);

    void setupZmqThread();
    void setupZmqComm(QString ip, int reciPort, int sendPort);
    void rebootZmq();

    // 预报员接受的趋势报内容
    void noTrendMetarCtxSignal(QString ctxStr);

public slots:
    // ui edit
    //void editSubUI(bool edit);

    // awos system message data bind awos sub contrl
    void awosWindData(SensorMap senMap); //awos wind datd
    void awosHumiTempData(SensorMap senMap); //awos hum and temp data
    void awosRvrData(SensorMap senMap); //awos is and rvr data
    void awosCloudData(SensorMap senMap); //awos cloud data
    void awosAtmospherePressData(SensorMap senMap); //awos phomene data
    void awosRainData(SensorMap senMap); //awos rain data
    void awosPhenomenaWeatherData(SensorMap senMap); //awos （PW）wheather data
    void awosPrevailingVisibilityData(SensorMap senMap);//awos ((PV)pv data
    void awosManualInputDataData(SensorMap senMap);//awos humen data

    //awos system real time data store
    void windDataStore(SensorMap senMap); //wind data store
    void humiTempDataStore(SensorMap senMap); //hum and temp data store
    void rvrDataStore(SensorMap senMap); //vis and rvr data store
    void cloudDataStore(SensorMap senMap); //cloud data store
    void atmospherePressDataStore(SensorMap senMap); //phomene data store
    void rainDataStore(SensorMap senMap); //rain data store
    void phenomenaWeatherDataStore(SensorMap senMap); //（PW）wheather data store
    void prevailingVisibilityDataStore(SensorMap senMap);//(PV)pv data store
    void BIASLIGHTDataSignalDataStore(SensorMap senMap);//BIASLIGHTD data store
    void manualInputDataDataStore(SensorMap senMap);//humen data store

    //awos system real time waring data store
    void waringDatastore(SensorMap senMap);

    //awos system user data search
    void userDataSearch(QString option,LoginQueue info);
    void initSetupTimer(bool falg);

    //waring list due
    void addWaringMap(SensorMap senMap);

    //close or open contrls
    void openOrcloseContrls( bool flag );

    //message send slots

    // 1 . AFTN set slot
    void AFTNSetSlot(MeaagseQueue queue);

    // 2 . send metar context slot
    void sendMetarTrandRequestSlot(MeaagseQueue queue);

    // ForCaster Trend
    void showForCasterTrendUI(QString trendStr);

private:
    QTimer *setupTimer;
    int setp;
    int heartbeatNumber;
    void initSetpValue();

    int i;//test used
    //data waring
    QSound *voideMor;
    QSound *voideRvr;
    void initVocies();
    void awosWaringVoice(WaringTepy waring);
    WaringTepy m_waringBool;
    WorkStation * minAwos;

    int currentShowRunWayID;
    int currentwindareaFlag;
    int currentdataAreaFlag;

    // telegram datas
    realDataMap telegramData;

    // logined user information
    QString _name,_password,_grade;
    void _init_User_Infromations();
    void _set_User_Infromations(QString _nameStr,
                                QString _passwordStr,
                                QString _gradeStr);
};

#endif // AWOSSTARTSETUP_H
