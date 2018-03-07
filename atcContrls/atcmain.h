#ifndef ATCMAIN_H
#define ATCMAIN_H

#include <QWidget>
#include "UiSensorRunWay/runway.h"
//#include "UiSensorWind/windmeter.h"
#include "atcContrls/atcmainwindrose.h"
#include "atcContrls/atcmainack.h"
#include "AFTN/aftnhurdle.h"

class ATCMAIN : public QWidget
{
    Q_OBJECT
public:
    explicit ATCMAIN(QWidget *parent = 0);
    void setShowOutGeometry();

protected:
    bool eventFilter(QObject *obj, QEvent *event);

signals:

public slots:
    void setDataValue(QString wind,QString value);

private:
    RunWay  *runway;
    ATCMainWindRose *meterOne;
    ATCMainWindRose *meterTwo;
    ATCMainWindRose *meterThree;
    void inintContrls();
    void setContrlsGeometry();
    void installContrlsEventFilter();
    void setWindRoseValue(ATCMainWindRose *& rose,QString Value);

    atcMainACK *ack;
    void initAckObj();
    void installAckEventFilter();
    void setAckGeometry();

    AFTNHurdle *telegram;
    void initTeleObj();
    void installTeleEventFilter();
    void setTelegramGeometry();
};

#endif // ATCMAIN_H
