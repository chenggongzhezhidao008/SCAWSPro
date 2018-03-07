#ifndef AWOSSENSORCLOUD_H
#define AWOSSENSORCLOUD_H

#include <QPainter>
#include <QPaintEvent>
#include <QWidget>

class AwosSensorCloud : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(int airportId READ airportId WRITE setAirportId NOTIFY airportIdChanged)
    Q_PROPERTY(int runFlag READ runFlag WRITE setRunFlag NOTIFY runFlagChanged)
    Q_PROPERTY(int runWayId READ runWayId WRITE setRunWayId NOTIFY runWayIdChanged)
    Q_PROPERTY(int cloudId READ getCloudId WRITE setCloudId NOTIFY cloudIdChanged)
    Q_PROPERTY(QString runwayName READ runwayName WRITE setRunwayName NOTIFY runwayNameChanged)
    Q_PROPERTY(QString runwayUsed READ runwayUsed WRITE setRunwayUsed NOTIFY runwayUsedChanged)

    Q_PROPERTY(QString firstlay READ getFirstlay WRITE setFirstlay NOTIFY firstlayChanged)
    Q_PROPERTY(QString secondlay READ getSecondlay WRITE setSecondlay NOTIFY secondlayChanged)
    Q_PROPERTY(QString thirdlay READ getThirdlay WRITE setThirdlay NOTIFY thirdlayChanged)

public:
    explicit AwosSensorCloud(QWidget *parent = 0);

    int runFlag() const { return this->m_flag; }
    int airportId() const { return this->m_airportId; }
    int runWayId() const { return this->m_runwayId; }
    int getCloudId() const { return this->m_cloudId; }
    QString runwayName() const { return this->m_runWayStr; }
    QString runwayUsed() const { return this->m_usedStr; }

    QString getFirstlay() const { return this->m_firstlay; }
    QString getSecondlay() const { return this->m_secondlay; }
    QString getThirdlay() const { return this->m_thirdlay; }
    QString getLocation() const { return this->m_location; }


public slots:
    void setRunFlag(int flag);
    void setAirportId(int airportId);
    void setRunWayId(int runwayId);
    void setCloudId(int cloudId);
    void setRunwayName(QString runWayName);
    void setRunwayUsed(QString usedStr);

    void setFirstlay(QString firstlay);
    void setSecondlay(QString secondlay);
    void setThirdlay(QString thirdlay);
    void setLocation(QString loca);

signals:
    void runFlagChanged();
    void airportIdChanged();
    void runWayIdChanged();
    void cloudIdChanged();
    void runwayNameChanged();
    void runwayUsedChanged();

    void firstlayChanged();
    void secondlayChanged();
    void thirdlayChanged();

protected:
    void paintEvent(QPaintEvent *event);

private:
    int m_flag;
    int m_airportId;
    int m_runwayId;
    int m_cloudId;

    QString m_runWayStr;
    QString m_usedStr;

    QString m_firstlay;
    QString m_secondlay;
    QString m_thirdlay;
    void initCloudHeight();

    QString m_location;
    void initLocation();
};

#endif // AWOSSENSORCLOUD_H
