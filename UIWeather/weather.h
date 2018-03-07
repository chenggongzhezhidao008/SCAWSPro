#ifndef WEATHER_H
#define WEATHER_H

#include <QObject>

class Weather : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int runFlag READ runFlag WRITE setRunFlag NOTIFY runFlagChanged)
    Q_PROPERTY(int airportId READ airportId WRITE setAirportId NOTIFY airportIdChanged)
    Q_PROPERTY(int runWayId READ runWayId WRITE setRunWayId NOTIFY runWayIdChanged)
    Q_PROPERTY(int weatherId READ getweatherId WRITE setweatherId NOTIFY weatherIdChanged)
    Q_PROPERTY(QString runwayName READ runwayName WRITE setRunwayName NOTIFY runwayNameChanged)
    Q_PROPERTY(QString runwayUsed READ runwayUsed WRITE setRunwayUsed NOTIFY runwayUsedChanged)

public:
    explicit Weather(QObject *parent = 0);

    int runFlag() const { return this->m_flag; }
    int airportId() const { return this->m_airportId; }
    int runWayId() const { return this->m_runwayId; }
    int getweatherId() const { return this->m_weatherId; }
    QString runwayName() const { return this->m_runWayStr; }
    QString runwayUsed() const { return this->m_usedStr; }
    QString getLocation() const { return this->m_location; }

signals:
    void runFlagChanged();
    void airportIdChanged();
    void runWayIdChanged();
    void weatherIdChanged();
    void runwayNameChanged();
    void runwayUsedChanged();

public slots:
    void setRunFlag(int flag);
    void setAirportId(int airportId);
    void setRunWayId(int runwayId);
    void setweatherId(int weatherId);
    void setRunwayName(QString runWayName);
    void setRunwayUsed(QString usedStr);
    void setLocation(QString loca);
    void setweatherValue(QString weather);

private:
    int m_flag;
    int m_airportId;
    int m_runwayId;
    int m_weatherId;
    QString m_weatherValue;
    void initStartValue();

    QString m_runWayStr;
    QString m_usedStr;
    QString m_location;
    void initLocation();

};

#endif // WEATHER_H
