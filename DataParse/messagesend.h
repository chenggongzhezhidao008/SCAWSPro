#ifndef MESSAGESEND_H
#define MESSAGESEND_H

#include <QObject>
#include <QMap>
#include <QString>
#include <QVariant>

#include <QQueue>

typedef QString DataName;
typedef QString DataValue;
typedef QMap<DataName,DataValue> DataContext;
typedef QQueue<QString> SC_COMMD;
class MessageSend : public QObject
{
    Q_OBJECT
public:
    explicit MessageSend(QObject *parent = 0);

signals:
    void sendMessage(QByteArray message);

public slots:
    void dataUnit3616MessageDue(QString headName,SC_COMMD commd);
    void cloudMessageDue(QString headName,DataContext context); //云数据处理
    void humiTempMessageDue(QString headName,DataContext context); //温湿度数据处理
    void atmospherePressMessageDue(QString headName,DataContext context); //大气压数据处理
    void rainMessageDue(QString headName,DataContext context); //降雨量数据处理
    void rvrMessageDue(QString headName,DataContext context); //能见度和跑到视程数据处理
    //...LMCFG
    //...PWDCFG
    void windMessageDue(QString headName,DataContext context);//风数据处理
    //...PWCFG
    //...RUNWAYLIGHTCFG
    //...AFTNCFG

    //void prevailingVisibilityMessageDue(QString headName,DataContext context);//(PV)主导能见度数据处理
    //void manualInputDataMessageDue(QString headName,DataContext context);//人工输入数据处理
    //void phenomenaWeatherMessageDue(QString headName,DataContext context); //（PW）天气现象数据处理
private:
    void addMessageHead(QString version,QString sequenceNum,QString messageTime,QString messageType,
                        QString equipmentId,QString  locationOrStatusTrargetId,SC_COMMD commd/*DataContext context*/);
};

#endif // MESSAGESEND_H
