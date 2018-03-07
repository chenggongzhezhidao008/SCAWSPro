#ifndef TELEGRAMCODES_H
#define TELEGRAMCODES_H

#include <QObject>
#include <QString>
#include <QStringList>
#include <QDebug>
#include <QMap>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef QMap<QString,QString> PWStrength;
typedef QMap<QString,QString> CloudCode;

class TelegramCodes : public QObject
{
    Q_OBJECT
public:
    explicit TelegramCodes(QObject *parent = 0);
    QString getWindCodec( QString tenAvgAngle
                         ,QString tenAvgSpeed
                         ,QString tenMinAngle
                         ,QString tenMaxAngle
                         ,QString SHwindSpeed);

    QString getMorCodes( //QString tenAvgMor
                          QString rowVis
                         ,QString tenAvgRVR
                         ,QString sensor_Vis10m);

    QString getRvrCodes( QString tenAvgRvr
                        ,QString tenMinRvr
                        ,QString tenMaxRvr
                        ,QString tenAvgVis
                        ,QString runWayNUmber
                        ,QString rvrTrend);

    QString getWeatherCodes(QString weather);

    QString getCloudCodes(QString isSkyClear
                          ,QString isVerVis
//                          ,QString verVisE5
                          ,QString cloudBase
//                          ,QString cloudBaseE5
                          ,QString ch1Ins30
                          ,QString ch2Ins30
                          ,QString ch3Ins30
                          ,QString amount1_30
                          ,QString amount2_30
                          ,QString amount3_30);

    QString getTempretrueDewCodes(QString tempretrue
                                  ,QString dew);
    QString getPressCodes(QString QNHPress);
    QString getCAVOKCodes(/*QString morVlaue*/
                          /*,*/
                           QString visValue
//                          ,QString isSkyClear// 不用此条件（原因：有云有可能也不影响飞行）
                          // 使用云teleCode 分析 代替上述条件
                          ,QString teleCloudCodec
                          ,QString weather);
signals:
    void returnCavokCode(QString cavokStr);

public slots:
    void checkCavok(QString visValue
                    ,QString teleCloudCodec
                    ,QString weather);

private:
    QString windAngleTranslate(QString angleStr);
    QString windSpeedTranslate(QString speedStr);
    QString windGustSpeedTranslate(QString speedStr);
    QString morTranslate(QString morStr);
    QString rvrTranslate(QString rvr);
    int rvrValueTranslate(QString teleDataCtx);
    QString threeCodc(QString amount);
    QString getCloudHight(QString cloudHight);
};

#endif // TELEGRAMCODES_H
