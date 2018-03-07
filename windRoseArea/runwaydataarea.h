#ifndef RUNWAYDATAAREA_H
#define RUNWAYDATAAREA_H

#include <Qtimer>
#include <QWidget>
#include <QPainter>
#include <QPaintEvent>

#include "UiSensorRvr/rvrsensoruot.h"

class RunWayDataArea : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(int runFlag READ runFlag WRITE setRunFlag NOTIFY runFlagChanged)
    Q_PROPERTY(int airportId READ airportId WRITE setAirportId NOTIFY airportIdChanged)
    Q_PROPERTY(int runWayId READ runWayId WRITE setRunWayId NOTIFY runWayIdChanged)
    Q_PROPERTY(int windId READ windId WRITE setWindId NOTIFY windIdChanged)
    Q_PROPERTY(int humitempId READ humitempId WRITE setHumitempId NOTIFY humitempIdChanged)
    Q_PROPERTY(QString runwayName READ runwayName WRITE setRunwayName NOTIFY runwayNameChanged)
    Q_PROPERTY(QString runwayUsed READ runwayUsed WRITE setRunwayUsed NOTIFY runwayUsedChanged)

    //数据
    Q_PROPERTY(QString zOneSpeed READ zOneSpeed WRITE setZOneSpeed NOTIFY zOneSpeedChanged)
    Q_PROPERTY(QString zOneAngle READ zOneAngle WRITE setZOneAngle NOTIFY zOneAngleChanged)
    Q_PROPERTY(QString zTenSpeed READ zTenSpeed WRITE setZTenSpeed NOTIFY zTenSpeedChanged)
    Q_PROPERTY(QString zTenAngle READ zTenAngle WRITE setZTenAngle NOTIFY zTenAngleChanged)

    Q_PROPERTY(QString cOneSpeed READ cOneSpeed WRITE setCOneSpeed NOTIFY cOneSpeedChanged)
    Q_PROPERTY(QString cOneAngle READ cOneAngle WRITE setCOneAngle NOTIFY cOneAngleChanged)
    Q_PROPERTY(QString cTenSpeed READ cTenSpeed WRITE setCTenSpeed NOTIFY cTenSpeedChanged)
    Q_PROPERTY(QString cTenAngle READ cTenAngle WRITE setCTenAngle NOTIFY cTenAngleChanged)

    Q_PROPERTY(QString temp READ temp WRITE setTemp NOTIFY tempChanged)
    Q_PROPERTY(QString humi READ humi WRITE setHumi NOTIFY humiChanged)
    Q_PROPERTY(QString dew READ dew WRITE setDew NOTIFY dewChanged)
    Q_PROPERTY(QString rain READ rain WRITE setRain NOTIFY rainChanged)


public:
    explicit RunWayDataArea(QWidget *parent = 0);
    int runFlag() const { return this->m_flag; }
    int airportId() const { return this->m_airportId; }
    int runWayId() const { return this->m_runwayId; }
    int windId() const { return this->m_windId; }
    int humitempId() const { return this->m_humitempId; }
    QString runwayName() const { return this->m_runWayStr; }
    QString runwayUsed() const { return this->m_usedStr; }

    QString  zOneSpeed() const {return this->m_zoneSpeed ;}
    QString  zOneAngle() const {return this->m_zoneAngle ;}
    QString  zTenSpeed() const {return this->m_ztenSpeed ;}
    QString  zTenAngle() const {return this->m_ztenAngle ;}
    QString  cOneSpeed() const {return this->m_coneSpeed ;}
    QString  cOneAngle() const {return this->m_coneAngle ;}
    QString  cTenSpeed() const {return this->m_ctenSpeed ;}
    QString  cTenAngle() const {return this->m_ctenAngle ;}

    QString temp() const { return this->m_tempValue; }
    QString humi() const { return this->m_humiValue; }
    QString dew() const { return this->m_dewValue; }
    QString rain() const { return this->m_rainValue; }
    QString getLocation() const { return this->m_location;}

signals:
    void runFlagChanged();
    void airportIdChanged();
    void runWayIdChanged();
    void windIdChanged();
    void humitempIdChanged();
    void runwayNameChanged();
    void runwayUsedChanged();

    //数据信号
    void zOneSpeedChanged();
    void zOneAngleChanged();
    void zTenSpeedChanged();
    void zTenAngleChanged();
    void cOneSpeedChanged();
    void cOneAngleChanged();
    void cTenSpeedChanged();
    void cTenAngleChanged();

    void tempChanged();
    void humiChanged();
    void dewChanged();
    void rainChanged();


protected:
    void paintEvent(QPaintEvent *event);
    bool eventFilter(QObject *obj, QEvent *event);

public slots:
    void showSubContrl();
    void setRunFlag(int flag);
    void setAirportId(int airportId);
    void setRunWayId(int runwayId);
    void setWindId(int windId);
    void setHumitempId(int humitempId);
    void setRunwayName(QString runWayName);
    void setRunwayUsed(QString usedStr);

    void setZOneSpeed(QString speed);
    void setZOneAngle(QString angle);
    void setZTenSpeed(QString speed);
    void setZTenAngle(QString angle);
    void setCOneSpeed(QString speed);
    void setCOneAngle(QString angle);
    void setCTenSpeed(QString speed);
    void setCTenAngle(QString angle);

    void setTemp(QString temp);
    void setHumi(QString humi);
    void setDew(QString dew);
    void setRain(QString rain);

    void setZeroData();

    void setLocation(QString loca);

private:
    RvrSensorUot * m_temp;
    RvrSensorUot * m_hum;
    RvrSensorUot * m_dew;
    RvrSensorUot * m_rain;

    RvrSensorUot * m_TNoneSpeed;
    RvrSensorUot * m_TNoneAngle;
    RvrSensorUot * m_TNtenSpeed;
    RvrSensorUot * m_TNtenAngle;

    RvrSensorUot * m_MNoneSpeed;
    RvrSensorUot * m_MNoneAngle;
    RvrSensorUot * m_MNtenSpeed;
    RvrSensorUot * m_MNtenAngle;


    //各个参数
    int m_flag;
    int m_airportId;
    int m_runwayId;
    int m_windId;
    int m_visId;
    int m_humitempId;
    QString m_runWayStr;
    QString m_usedStr;

    //数据参数
    QString m_zoneSpeed ;
    QString m_zoneAngle ;
    QString m_ztenSpeed ;
    QString m_ztenAngle ;
    QString m_coneSpeed ;
    QString m_coneAngle ;
    QString m_ctenSpeed ;
    QString m_ctenAngle ;

    QString m_tempValue;
    QString m_humiValue;
    QString m_dewValue;
    QString m_rainValue;

    QTimer *zeroTimer;
    int setp;
    void initZeroTimer();

    QString m_location;
    void initLOcation();
};

#endif // RUNWAYDATAAREA_H
