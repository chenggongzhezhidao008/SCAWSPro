#ifndef WINDROSEAREA_H
#define WINDROSEAREA_H

#include "UiSensorRvr/rvrsensoruot.h"
#include "UiSensorWind/windmeter.h"

#include <QWidget>
#include <QPainter>
#include <QPaintEvent>
#include <QPaintEngine>
#include <QPropertyAnimation>
#include <QDebug>
#include <QMap>
#include <QTimer>
typedef QMap<QString,bool> WaringTepy;

class WindRoseArea : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(int airportId READ airportId WRITE setAirportId NOTIFY airportIdChanged)
    Q_PROPERTY(int runFlag READ runFlag WRITE setRunFlag NOTIFY runFlagChanged)
    Q_PROPERTY(int runWayId READ runWayId WRITE setRunWayId NOTIFY runWayIdChanged)
    Q_PROPERTY(int windId READ windId WRITE setWindId NOTIFY windIdChanged)
    Q_PROPERTY(int visId READ visId WRITE setVisId NOTIFY visIdChanged)
    Q_PROPERTY(int cloudId READ cloudId WRITE setCloudId)
    Q_PROPERTY(QString runwayName READ runwayName WRITE setRunwayName NOTIFY runwayNameChanged)
    Q_PROPERTY(QString runwayUsed READ runwayUsed WRITE setRunwayUsed NOTIFY runwayUsedChanged)


    Q_PROPERTY(QString currentWindSpeed READ currentWindSpeed WRITE setCurrentWindSpeed NOTIFY currentWindSpeedChanged)
    Q_PROPERTY(int currentWindAngle READ currentWindAngle WRITE setCurrentWindAngle NOTIFY currentWindAngleChanged)
    Q_PROPERTY(int tenWindMinAngle READ tenWindMinAngle WRITE setTenWindMinAngle NOTIFY tenWindMinAngleChanged)
    Q_PROPERTY(int tenWindMaxAngle READ tenWindMaxAngle WRITE setTenWindMaxAngle NOTIFY tenWindMaxAngleChanged)
    Q_PROPERTY(int windPointAngle READ windPointAngle WRITE setWindPointAngle NOTIFY windPointAngleChanged)
    Q_PROPERTY(QString zfeng10 READ zfeng10 WRITE setZfeng10 NOTIFY zfeng10Changed)

    Q_PROPERTY(QString morValue READ morValue WRITE setMorValue NOTIFY morValueChanged)
    Q_PROPERTY(QString rvrValue READ rvrValue WRITE setRvrValue NOTIFY rvrValueChanged)
    Q_PROPERTY(QString CLDBaseHight READ getCLDBaseHight WRITE setCLDBaseHight NOTIFY CLDBaseHightChanged)

    Q_PROPERTY(int morMax READ morMax WRITE setMorMax NOTIFY morMaxChanged)
    Q_PROPERTY(int rvrMax READ rvrMax WRITE setRvrMax NOTIFY rvrMaxChanged)
    Q_PROPERTY(int morMin READ morMin WRITE setMorMin NOTIFY morMinChanged)
    Q_PROPERTY(int rvrMin READ rvrMin WRITE setRvrMin NOTIFY rvrMinChanged)

    Q_PROPERTY(WaringTepy waringBool READ waringBool WRITE setWaringBool NOTIFY waringBoolChanged)


public:
    explicit WindRoseArea(QWidget *parent = 0);
    int runFlag() const { return this->m_flag; }
    int airportId() const { return this->m_airportId; }
    int runWayId() const { return this->m_runwayId; }
    int windId() const { return this->m_windId; }
    int visId() const { return this->m_visId; }
    int cloudId() const { return this->m_cloudId; }
    QString runwayName() const { return this->m_runWayStr; }
    QString runwayUsed() const { return this->m_usedStr; }

    QString currentWindSpeed() const {return this->m_currentSpeed;}
    int currentWindAngle() const {return this->m_currentAngle;}
    int tenWindMinAngle() const {return this->m_tenMinAngle;}
    int tenWindMaxAngle() const {return this->m_tenMaxAngle;}
    int windPointAngle() const {return this->m_pointAngle;}
    QString  zfeng10() const { return this->m_zfeng10;}

    QString morValue() const { return this->m_morValue; }
    QString rvrValue() const { return this->m_rvrValue; }
    QString getCLDBaseHight() const { return this->m_CloudBhight;}

    int morMax() const { return this->m_morMax; }
    int rvrMax() const { return this->m_rvrMax; }
    int morMin() const { return this->m_morMin; }
    int rvrMin() const { return this->m_rvrMin; }
    WaringTepy waringBool() const { return this->m_waringBool;}

    QString getLocation() const { return this->m_location;}

    void setEnablecloudCtl(bool openFlag);


public slots:
    void showSubContrl();
    void setRunFlag(int flag);
    void setAirportId(int airportId);
    void setRunWayId(int runwayId);
    void setWindId(int windId);
    void setVisId(int visId);
    void setCloudId(int cloudId);
    void setRunwayName(QString runWayName);
    void setRunwayUsed(QString usedStr);

    void setCurrentWindSpeed(QString currentSpeed);
    void setCurrentWindAngle(int currentAngle);
    void setTenWindMinAngle(int tenMinAngle);
    void setTenWindMaxAngle(int tenMaxAngle);
    void setWindPointAngle(int pointAngle);
    void setZfeng10(QString speed);

    void setMorValue(QString mor);
    void setRvrValue(QString rvr);
    void setCLDBaseHight(QString cloudHight);

    void setMorMax(int mor);
    void setRvrMax(int rvr);
    void setMorMin(int mor);
    void setRvrMin(int rvr);

    void setWaringBool(WaringTepy waring);

    void  setLocation(QString loca);

signals:
    void runFlagChanged();
    void airportIdChanged();
    void runWayIdChanged();
    void windIdChanged();
    void visIdChanged();
    void humitempIdChanged();
    void runwayNameChanged();
    void runwayUsedChanged();

    void currentWindSpeedChanged();
    void currentWindAngleChanged();
    void tenWindMinAngleChanged();
    void tenWindMaxAngleChanged();
    void windPointAngleChanged();
    void zfeng10Changed();

    void morValueChanged();
    void rvrValueChanged();
    void CLDBaseHightChanged();

    void  morMaxChanged();
    void  rvrMaxChanged();
    void  morMinChanged();
    void  rvrMinChanged();

    void  waringBoolChanged();

protected:
    void paintEvent(QPaintEvent *event);
    bool eventFilter(QObject *obj, QEvent *event);

private slots:
    void setZeroData();

private:
    RvrSensorUot *m_rvr;
    RvrSensorUot *m_mor;
    RvrSensorUot *m_CloudBase;
    RvrSensorUot *m_gust;
    WindMeter    *m_wind;
    bool m_updateSubContrl;
    void  initAllContrls();

    //各个参数
    int m_flag;
    int m_airportId;
    int m_runwayId;
    int m_windId;
    int m_visId;
    int m_cloudId;
    int m_humitempId;
    QString m_runWayStr;
    QString m_usedStr;

    QString m_currentSpeed;
    int m_currentAngle;
    int m_tenMinAngle;
    int m_tenMaxAngle;
    QPropertyAnimation *windAnimation;
    int m_pointAngle;
    int m_tempAngle;
    QString m_zfeng10;

    QString m_morValue;
    QString m_rvrValue;
    QString m_CloudBhight;
    void setInitValue();

    int m_morMax;
    int m_rvrMax;
    int m_morMin;
    int m_rvrMin;

    WaringTepy m_waringBool;

    QTimer *zeroTimer;
    int setp;
    void initZeroTimer();

    QString m_location;
    void initLocation();
};

#endif // WINDROSEAREA_H
