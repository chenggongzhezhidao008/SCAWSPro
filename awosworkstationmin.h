#ifndef WORKSTATION_H
#define WORKSTATION_H
#include "telegram/telesubdatamod.h"
#include "telegram/realtimedata.h"
#include "telegram/telectx.h"
#include "telegram/telepopfram.h"
#include "telegram/teleconfig.h"
#include "deveices/deveicestate.h"
#include "deveices/datalog.h"
#include "deveices/waring.h"
#include "deveices/installcfg.h"
#include "atcContrls/atcreport.h"
#include "atcContrls/atcmain.h"
#include "AFTN/telegramcfg.h"
#include "locaConfig/workestationcfg.h"
#include "UIMainWar/waringshow.h"

#include <QWidget>
#include <QListWidget>
#include <QMouseEvent>
#include <QPoint>
#include <QStateMachine>
#include <QState>
#include <QSignalTransition>
#include <QPropertyAnimation>
#include <QPainter>
#include <QPaintEvent>
#include <QTime>
#include <QTimer>
#include <QDateTime>
#include <QMap>
#include <QString>
#include <QLineEdit>
#include <QTextEdit>
#include <QComboBox>
#include <QQueue>
#include <QStack>
#include <QMessageBox>
#include <QVector>
#include <QDebug>
#include <QSettings>

typedef QStack <QString> METARStack;
typedef QStack <QString> SPACIStack;
typedef QQueue<QString> MeaagseQueue;
typedef QMap <int,QString> SerialWarMap;
typedef QMap <int,int> IndexPair;
typedef QMap<QString,QString> DataMap;
typedef QMap<QString,DataMap> SensorMap;
typedef QMap<int,bool> FunctionMap;
typedef QMap <int,QString> metarForm;
typedef QString realDataName;
typedef QString realDataValue;
typedef QMap <realDataName,realDataValue> realDataMap;
typedef QVector< TelegramPop*> TelegramHintPop;
typedef QMap<int,QString> TelegramCtx;

typedef QString InforName;
typedef QString InforCtx;
typedef QMap<InforName,InforCtx> InforData;


namespace Ui {
class WorkStation;//AwosWorkStationMin
}

class WorkStation : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(QString QNFValue READ getQNFValue WRITE setQNFValue NOTIFY QNFValueChanged)//****

public:
    explicit WorkStation(QWidget *parent = 0);
    ~WorkStation();
    void setAwosSize(int width,int height);// 设置界面大小尺寸
    bool getMinShow() const;
    void setMinShow(bool value);

    QString getQNFValue() const { return this->m_qnf;} //****

signals:

    /// \brief sacleSubContrl
    void sacleSubContrl();

    /// \brief openOrClosedContrls
    /// \param flag
    void openOrClosedContrls(bool flag);

    /// \brief AFTNConfigSet
    /// \param queue
    void AFTNConfigSet(MeaagseQueue queue);

    /// \brief observer send Metar to forcaster signal
    /// \param queue
    void sendMetarTrendReqeust(MeaagseQueue queue);

    /// \brief sendTrendQuery signal
    /// \param trendRequest
    void sendOkMetarSignal(QString MetarStr);

    /// \brief waringShowSignal
    /// \param title
    /// \param context
    void waringShowSignal(QString title,QString context);

    /// \brief QNFValueChanged
    void QNFValueChanged();

    // test port signals
    void airBackInforSignal(SensorMap dataMap);

    /// \brief runWayBackInforSignal
    /// \param dataMap
    void runWayBackInforSignal(SensorMap dataMap);

    /// \brief matchBackInforSignal
    /// \param dataMap
    void matchBackInforSignal(SensorMap dataMap);

    //3616 自身配置文档V10.
    void Configure3616Signal(SensorMap senMap);
    void sensorStatusSignal(SensorMap senMap);
    void sensorLIBsSignal(SensorMap senMap);
    void serialCardParamersSignal(SensorMap senMap);

    // affix 9 messages option signals
    void Affix9MessageSignals(QString opt);

    void backRequeryAFFIX9menberSignal(QString query,InforData menber);

    void AFFIX9NewMessageSendUp(QString dCtx,InforData data);

    // ATC DATA CNNECTIONS SGNALS
    void AtcDataSignal(QString location,QString value);

    void enbaleCavokCheck(bool able);

    /// \brief addWaring
    /// \param Ctx
    void addWaring(QString Ctx);

    void pollute_Show(); //rvr 测污补偿

    void ExternSensorInfoListSignale(SensorMap data);

public slots:
    // set metar report values
    void setTelegramReportValuesSlot(realDataMap datamap,QString affixOption);// metar 报文的参照数据入口处

    // ask telegram
    void telegramAskSubSlot(SensorMap telegramData);

    // pop send telegram
    void popTelegramSendSlot(TelegramCtx Ctx);

    //show receive telegram
    void telegramShowSubSlot(SensorMap telegramData);

    // query telegram
    void automaticMetarTelegramData();
    void automaticSpaciTelegramData();

    //quer report
    void snedReportMetarTelegramData();
    void snedReportSpaciTelegramData();

    // Metar and Spacai Report
    void updateMetarReport();
    void updateSpaciReport();

    // send Metar Report and Spaci Report
    void metarReportsender(QString ctx);
    void spaciReportsender(QString ctx);

    // Deveice partment
    void dusSupplyModlesSlot(SensorMap dataMap);
    void allSensorsInformationSlot(SensorMap dataMap);
    void setQNFValue(QString value);
    void setTreandMetar(QString trend);
    void _set_user_typeStr(QString type);

    // set run way and sensors setiings
    void set_runWays_setting(QSettings *&runwayInfor);

    // set run way and sensors setiings
    void set_usedWay_setting(QSettings *&usedRunWay);

    // set run way and sensors setiings
    void set_sensors_setting(QSettings *&sensor);

    // set run way and sensors setiings
    void set_telegram_setting(QSettings *&telegramSensor);


private slots:
    void functionSelectDo(int count,int index);// left buuton count = count ，select button index = index
    void metarSelectDo(int count,int index);// metar select page
    void configSelectDo(int count,int index);// config select page
    void oneSecondUpdate();

    // metar report calsses selected
    void metarClassesSlot(QString str);
    void spaciClassesSlot(QString str);
    void metarAddressesDeal(QString address);
    void spaciAddressesDeal(QString address);
    void metCodeShow();
    void spaciCodeShow();
    QString MetarReportTranslateContext(SerialWarMap telegramCtx);
    QString SpaciReportTranslateContext(SerialWarMap telegramCtx);
    SerialWarMap getMetarControlsText();
    QString getTrendMetarStr();
    SerialWarMap getMetarReportControlsText();
    SerialWarMap getSpaciControlsText();
    SerialWarMap getSpaciReportControlsText();
    QString constituteMetarContext(SerialWarMap serialMap);
    QString constituteSpaciContext(SerialWarMap serialMap);

    // metar report deal
    QString removeFeild(QString str);

    // metar report options
    void updateMetar();
    void sendMetarAskTrend();
    void modifyMetar();
    void sendMetar();

    // spaci report options
    void updateSpaci();
    void modifySpaci();
    void sendSpaci();

    // last telegram buffer store
    void showLastSpaciReport();
    void showLastMetarReport();

    // waring message
    void waringShowSlot(QString title,QString context);

    // ATC
    void atcSelectDo(int count,int index);


protected:

    // 以下三个事件使Awos界面可移动
    void mousePressEvent(QMouseEvent *e);
    void mouseMoveEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);

    // relase mouse to update ui
    bool releaseDo;

    // max ui not do move
    bool moveUI;

    // 过滤掉不要的一些事件
    bool eventFilter(QObject *obj, QEvent *event);

    // 绘制函数
    void paintEvent(QPaintEvent *event);
    void PressDraw(QPainter* painter);
    void scaleButtomClose(QPainter* painter);
    void scaleButtomOpen(QPainter* painter);
    void showOrCloseTelegramCFG(bool show);
    void showOrCloseAFTNContrls(bool show);
    void showOrCloseLocaCFGContrl(bool show);
    void showOrCloseMetarContrls(bool show);
    void showOrCloseSpaciContrls(bool show);
    void showOrCloseMetarReportContrl(bool show);
    void showOrCloseSpacialReportContrl(bool show);
    void showOrCloseDeveiceContrl(bool show);
    void showOrCloseInfomationContrl(bool show);
    void showOrCloseLogContrl(bool show);
    void showOrCloseWaringContrl(bool show);
    void showOrCloseMainWaringContrl(bool show);

    bool teleCFGBool;
    bool metarSetBool;
    bool locaCFgBool;
    bool metarBool;
    bool spaciBool;
    bool metarReportBool;
    bool spacialReportBool;
    bool deveiceBool;
    bool informationBool;
    bool logBool;
    bool waringBool;
    bool mainWarBool;

    void updateSize();

    // ATC begin
    bool atcMetarReportBool;
    void initMetarReportBool();
    void showOrCloseAtcMetarReport(bool show);
    bool atcAtcMainBool;
    void initAtcMainBool();
    void showOrCloseAtcMain(bool show);

private:
    Ui::WorkStation *ui;     //AwosWorkStationMin
    QPoint point;            //保存鼠标按下的点全局位置坐标与局部坐标的差向量
    bool mousePressed;      //保存鼠标按下状态
    bool m_fullScreen;
    QTimer *oneSecondTimer;
    void initMetar();

    //QStringList m_waringNotDealList;
    FunctionMap m_metar;
    FunctionMap m_configPage;

    bool m_scaleUI;
    bool m_firstFunction;
    bool m_secondFunction;
    bool m_thirdFunction;
    bool m_fourFunction;
    bool m_fiveFunction;

    // metar ui update button effect
    bool m_metOne;
    bool m_metTwo;
    bool m_metThree;
    bool m_metFour;
    bool m_metFive;

    // deceive config ui update button effect
    bool m_mserver;
    bool m_mCollect;
    bool m_mServerConfig;
    bool m_mCollectConfig;
    bool m_mDataConfig;
    bool m_mLocaConfig;
    FunctionMap funcMap;

public:
    teleSubDataModCtl *MetarEcodecContrl;

private:
    QLineEdit *metarSenAddresses;
    QComboBox *metarClasses;

    QTextEdit *metarContext;
    QTextEdit *metarCtxConfirm;
    QTextEdit *Met_metarWaringInform;// METAR 报部分的告警处理
    QTextEdit *Met_spacilWaringInform;
    SerialWarMap metarContextMap;
    SerialWarMap spaciContextMap;

    bool m_metUpdate;
    bool m_cavokCheck;
    bool m_cavok;
    bool m_metModify;
    bool m_metTrend;
    bool m_metSend;
    bool met_modifyFlag;
    bool m_metarComfire;
    bool m_spacilComfire;
    bool m_clickLastMetar;
    bool m_clickLastSpaci;

    // Metar Report
    teleSubDataModCtl *MetarReportEcodecContrl;

    // SPACI  Report
    teleSubDataModCtl *SpaciEcodecContrl;
    QLineEdit *spaciSenAddresses;
    QComboBox *spaciClasses;
    QTextEdit *Spaci_metarWaringInform;// 报部分的告警处理
    QTextEdit *Spaci_spacilWaringInform;
    QTextEdit *spaciContext;
    QTextEdit *spaciCtxConfirm;

    bool m_spaciUpdate;
    bool m_spaciModify;
    bool m_spaciSend;
    bool spaci_modifyFlag;
    // Spaci Report
    teleSubDataModCtl *SpaciReportEcodecContrl;
    // realData
    RealTimeData *_metar_Realdata_contrl;
    RealTimeData *_spaci_Realdata_contrl;
    RealTimeData *_metar_Report_Realdata_contrl;
    RealTimeData *_spacial_Report_Realdata_contrl;

    TelegramContextDealUI *MetarReportTelegramContextUI;
    TelegramContextDealUI *SpaciReportTelegramContextUI;
    void initTelegramOptionConnections();

    // 电报配置
    TeleConfig *teleCFG;
    void _m_init_telegram_cfg();
    void _m_set_telegram_cfg_geometry();
    void _m_install_teleDFG();

    // 2 . AFTN
    TelegramCFG *aftnCFG;
    void initAFTNCFG();
    void setAFTNCFGGeomerty();
    void initAFTNCFGSignalConnection();
    void installAftnCFGEventFilter();

    // 2 . loca CFG
    WorkeStationCFG *locaCFG;
    void initLocaCFG();
    void setLocaCFGGeomerty();
    void initLocaCFGSignalConnection();
    void installLocaCFGEventFilter();

    // metar context variables
    QString Met_rankStr;
    QString Spaci_rankStr;
    QString AddressStr;
    QString metarContextStr;
    QString spaciContextStr;

    // Metar and Spaci report stack buff
    METARStack metraStackBuff;
    SPACIStack spaciStackBuff;

    // ********* DEVEICE **********
    deveiceStateControl *statue; // deveice Statue
    void initDeveiceSate();
    void setDeveiceGeometrySize();
    void installDeveiceEventFilter();
    void showOrCloseDeveice(bool option);
    void setDeveiceValues();

    DataLog *log;
    void initLogObj();
    void setLogGeomerty();
    void installLogEventFilter();
    void showOrCloseLog(bool option);

    WaringShow *waring;
    void initWaringObj();
    void setWaringGeomerty();
    void installWaringEventFilter();
    void showOrCloseWaring(bool option);

    InstallCFG *install; // deveice Config
    void initInstallCFG();
    void setInstallGeomerty();
    void installInstallFilter();
    void showOrCloseInstall(bool option);
    void initBackInstallConnections();
    void init36selfCFGConnection();
    void initCFGAffix9MessageOptionsSignals();

    TelegramHintPop popVec; // telegram show

    //*********** ATC *************
    FunctionMap m_atcPage;
    void init_m_atcPage();

    ATCREPORT *metReport;
    void initAtcMetarReport();
    void setAtcMetarReportGeometry();
    void installMetReportEventFilter();

    ATCMAIN *atcMain;
    void initAtcMainObj();
    void setAtcMainGeometry();
    void installAtcMainEventFilter();
    void initAtcMainDataConnections();

    QString m_qnf;
    void initQNFValue();

    QString _m_user_type;
    void  _init_grade();

    WarShow *_m_war;
    void _m_init_war_Value();
    void _m_set_geometry();
    void showOrclosedMainWar(bool show);

    QSettings * m_runwayInfor;
    QSettings * m_usedRunWay;
    QSettings * m_sensor;
    QSettings * m_telegramSensor;
    void init_config_settings();
};

#endif // WORKSTATION_H
