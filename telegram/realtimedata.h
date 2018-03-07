#ifndef REALTIMEDATA_H
#define REALTIMEDATA_H

#include <QDebug>
#include <QWidget>
#include <QMap>
#include <QString>
#include <QTime>
#include <QStringList>
#include <QLineEdit>
#include <QPainter>
#include <QPaintEvent>

typedef QString realDataName;
typedef QString realDataValue;
typedef QMap <realDataName,realDataValue> realDataMap;
typedef QMap <int,QString> SerialWarMap;


class RealTimeData : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(QString titleName READ getTitleName WRITE setTitleName NOTIFY titleNameChanged)
    Q_PROPERTY(QTime updateTime READ getUpdateTime WRITE setUpdateTime NOTIFY updateTimeChanged)
    Q_PROPERTY(realDataMap realData READ getrealData WRITE setRealData NOTIFY realDataChanged)
    Q_PROPERTY(SerialWarMap subNameList READ getsubNameList WRITE setSubNameMap NOTIFY subNameListChanged)


public:
    explicit RealTimeData(QWidget *parent = 0);
    QString  getTitleName() const { return this->m_titleName; }
    QTime  getUpdateTime() const { return this->m_updateTime; }
    realDataMap  getrealData() const { return this->m_realDataMap; }
    SerialWarMap getsubNameList() const { return this->m_subDataNameList; }

signals:
    void titleNameChanged();
    void updateTimeChanged();
    void realDataChanged();
    void subNameListChanged();

public slots:
    void setTitleName(QString titleName);
    void setUpdateTime(QTime updateTime);
    void setRealData(realDataMap realData);
    void setSubNameMap(SerialWarMap subNameList);
    void updateSubName(QString affixstr);
    void updateAllContrlsSize();

protected:
    void paintEvent(QPaintEvent *event);

private:
    QString m_titleName;
    QTime m_updateTime;
    realDataMap m_realDataMap;
    SerialWarMap m_subDataNameList;
    void initRealNameDataList();
    bool assignment(QString option,realDataMap newDataMap = realDataMap());
    QStringList m_dataNameStrList;
    void initAllDataContrls();
    void setAllContrlsReadOnly();
    void setAllContrlsValue();
    void initSubTitles();

    // SHOW  DATA OBJECTS
    QLineEdit  *groupLeftAngle;
    QLineEdit  *groupLeftSpeed1;
    QLineEdit  *groupLeftSpeed2;
    QLineEdit  *groupLeftAngleMin;
    QLineEdit  *groupLeftAngleMax;
    QLineEdit  *groupMIDIAngle;
    QLineEdit  *groupMIDISpeed1;
    QLineEdit  *groupMIDISpeed2;
    QLineEdit  *groupMIDIAngleMin;
    QLineEdit  *groupMIDIAngleMax;
    QLineEdit  *groupRightAngle;
    QLineEdit  *groupRightSpeed1;
    QLineEdit  *groupRightSpeed2;
    QLineEdit  *groupRightAngleMin;
    QLineEdit  *groupRightAngleMax;
    QLineEdit  *groupVisTenAvg;
    QLineEdit  *groupVisTenMin;
    QLineEdit  *groupVisTenDirection;
    QLineEdit  *groupLeftRVRTenAvgValue;
    QLineEdit  *groupLeftRVRTendency;
    QLineEdit  *groupMIDIRVRTenAvgValue;
    QLineEdit  *groupMIDIRVRTendency;
    QLineEdit  *groupRightRVRTenAvgValue;
    QLineEdit  *groupRightRVRTendency;
    QLineEdit  *group1CloudCount;
    QLineEdit  *group1CloudHight;
    QLineEdit  *group2CloudCount;
    QLineEdit  *group2CloudHight;
    QLineEdit  *group3CloudCount;
    QLineEdit  *group3CloudHight;
    QLineEdit  *groupLeftTem;
    QLineEdit  *groupLeftDew;
    QLineEdit  *groupLeftHum;
    QLineEdit  *groupRightTem;
    QLineEdit  *groupRightDew;
    QLineEdit  *groupRightHum;
    QLineEdit  *groupPress;
    QLineEdit  *groupCurrentWeather;
    QLineEdit  *groupCloseTimeWeather;

    QString cloudLoca;
    QString m_upd_t;
    void _m_init_update_time();

public slots:
    void  initLocation(QString loca);
};

#endif // REALTIMEDATA_H
