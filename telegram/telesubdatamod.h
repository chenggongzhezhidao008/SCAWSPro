#ifndef TELEGRAMSUBDATAMODIFITYCONTRL_H
#define TELEGRAMSUBDATAMODIFITYCONTRL_H

#include <QWidget>
#include <QTime>
#include <QMap>
#include <QString>
#include <QStringList>
#include <QLineEdit>
#include <QPainter>
#include <QPaintEvent>
#include <QComboBox>
#include <QDebug>
#include <QMessageBox>
#include "part6TeleCodes/telegramcodes.h"

typedef QString realDataName;
typedef QString realDataValue;
typedef QMap <realDataName,realDataValue> realDataMap;


typedef QMap <int,QString> SerialWarMap;
typedef QMap <QString,QString> TrendMetar;
typedef QMap <QString,QString> telegramCFG;

class teleSubDataModCtl : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(QString telegramName READ getTelegramName WRITE setTelegramName NOTIFY telegramNameChanged)
    Q_PROPERTY(QTime updateTime READ getUpdateTime WRITE setUpdateTime NOTIFY updateTimeChanged)
    Q_PROPERTY(QString toSendTelegramHaveTime READ getToSendTelegramHaveTime WRITE setToSendTelegramHaveTime NOTIFY toSendTelegramHaveTimeChanged)
    Q_PROPERTY(bool encodeTelegramStyle READ getencodeTelegramStyle WRITE setEncodeTelegramStyle NOTIFY encodeTelegramStyleChanged)

public:
    explicit teleSubDataModCtl(QWidget *parent = 0);
    QString getTelegramName() const { return this->m_telegramName; }
    QTime getUpdateTime() const { return this->m_updateTime; }
    QString getToSendTelegramHaveTime() const { return this->m_haveTime; }
    bool getencodeTelegramStyle()  const { return this->m_encodTelegramStyle; }

protected:
    void paintEvent(QPaintEvent *event);
    void setAllContrlsGeometry();
    void setAllComboxContrlsGeometry();

signals:
    void telegramNameChanged();
    void updateTimeChanged();
    void toSendTelegramHaveTimeChanged();
    void encodeTelegramStyleChanged();

public slots:
    void setTelegramName(QString telegramName);
    void setUpdateTime(QTime updateTime);
    void setToSendTelegramHaveTime(QString toSendTelegramHaveTime);
    void setEncodeTelegramStyle(bool encodcStyle);

    void headMetarSlot(QString str);
    void windMetarSlot(QString str);
    void visMetarSlot(QString str);
    void RVRMetarSlot(QString str);
    void weatherMetarSlot(QString str);
    void cloudHightMetarSlot(QString str);
    void tempHumMetarSlot(QString str);
    void pressMetarSlot(QString str);
    void closWeatherMetarSlot(QString str);
    void wsMetarSlot(QString str);
    void motneMetarSlot(QString str);
    void trendMetarSlot(QString str);
    void metarOptionSelet(QString nameStr,QString optionStr);
    void ComboxCtlsSelecetSlot(QString affixstr);

    // 观测员：更新编写每个气象因素电报内容
    void updateSubTelegramCtx(realDataMap systemTelegramTtx);

    // 将预报员发来的趋势更新到观测员界面
    void updateSubTelegramTrendCtx(QString trendCtx);

    // 预报员：更新预报员的每个气象要素电报内容
    void _update_Forcaster_Sub_Telegram_Ctx(QString _Metar_Ctx);
    // 请求编报内容
    void setEnableCavokSlot(bool flag);
    SerialWarMap getTelegramCtx();
    TrendMetar getTrendRequestMetarCtx();

    // set user grade
    void _set_user_type(QString _user_type_Str);

private:
    QString m_telegramName;
    QTime m_updateTime;
    QString m_haveTime;

    SerialWarMap telegramLabelName;
    void initTelegramnLable();

    QLineEdit *headEdit;
    QLineEdit *windEdit;
    QLineEdit *visEdit;
    QLineEdit *RVREdit;
    QLineEdit *weatherEdit;
    QLineEdit *cloudHightEdit;
    QLineEdit *tempHumEdit;
    QLineEdit *pressEdit;
    QLineEdit *closeWeatherEdit;
    QLineEdit *MOTNEEdit;
    QLineEdit *TRENDEdit;
    QLineEdit *RemarkEdit;

    void newAllSubContrls();
    void setAllContrlsOnliyRead();
    void initAllEditLineValue();

    QComboBox *headBox;
    QComboBox *windBox;
    QComboBox *visBox;
    QComboBox *RVRBox;
    QComboBox *weatherBox;
    QComboBox *cloudHightBox;
    QComboBox *tempHumBox;
    QComboBox *pressBox;
    QComboBox *closeWeatherBox;
    QComboBox *MOTNEBox; //道面状况
    QComboBox *TRENDBox; //趋势
    QComboBox *WsBox; // 备注

    void newAllComboxContrl();
    void setAllComboxContrlsValue();
    void initComboxConnections();

    telegramCFG comBoxCFG;

    QStringList windItemList;
    QStringList visItemList;
    QStringList RVRItemList;
    QStringList weatherItemList;
    QStringList cloudHightItemList;
    QStringList tempHumItemList;
    QStringList pressItemList;
    QStringList closeWeatherItemList;
    void initItemsValue();




    SerialWarMap telegramSubOptions;
    void initTelegramSubOptions();

    bool headManulEditBool;
    bool windManulEditBool;
    bool visManulEditBool;
    bool RVRManulEditBool;
    bool weatherManulEditBool;
    bool cloudHightManulEditBool;
    bool tempHumManulEditBool;
    bool pressManulEditBool;
    bool closeWeatherManulEditBool;
    bool MOTNEManulEditBool;
    bool TRENDManulEditBool;
    bool RemarManulEditBool;
    void initManualEdit();

    // encodec style  :  manual = true(default),system = false;
    bool m_encodTelegramStyle;

    // telegram deal
    QString removeFeild(QString str);

    // init start telegram Sub Value
    SerialWarMap m_MStartVlaue;
    void initTeleStartCtx();

    // Telegram Codes deal
    TelegramCodes *teleCodecDeal;
    void initTeleCodecDeal();

    QString m_weatherStr;
    void initWeather();

    bool  m_cavokCheick;
    void  initCavokChieck();

    // user grade
    QString _user_type;
    void _init_user_grade_type();
};

#endif // TELEGRAMSUBDATAMODIFITYCONTRL_H
