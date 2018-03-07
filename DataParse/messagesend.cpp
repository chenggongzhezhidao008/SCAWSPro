#include "messagesend.h"
#include <QByteArray>
#include <QDebug>
#include <QString>

MessageSend::MessageSend(QObject *parent) :
    QObject(parent)
{

}

void MessageSend::addMessageHead(QString version,QString sequenceNum,QString messageTime,QString messageType,
                                 QString equipmentId,QString  locationOrStatusTrargetId,SC_COMMD commd/*DataContext context*/)
{
    char messageStart[] = {0x01};
    char textStart[] = {0x02};
    char textEnd[] = {0x03};
    char transferEnd[] = {0x04};
    char interval[] = {0x7c};
    QByteArray SOH(messageStart,1);
    QByteArray STX(textStart,1);
    QByteArray ETX(textEnd,1);
    QByteArray EOT(transferEnd,1);
    QByteArray intervalbyte(interval,1);

    QByteArray versionByte = version.toLatin1();
    QByteArray sequenceNumByte = sequenceNum.toLatin1();
    QByteArray messageTimeByte = messageTime.toLatin1();
    QByteArray messageTypeByte = messageType.toLatin1();
    QByteArray equipmentIdByte = equipmentId.toLatin1();
    QByteArray locationOrStatusTrargetIdByte = locationOrStatusTrargetId.toLatin1();

    int leng = commd.length();
    QString commdstr;
    QByteArray data;
    QStringList dataunitList;
    QByteArray dataUnit;
    for(int q = 0;q < leng;q++){
        commdstr.clear();
        data.clear();
        dataunitList.clear();
        commdstr = commd.dequeue();
        dataunitList = commdstr.split(":");
        qDebug()<<QString("dataunitList %1:").arg(q)<<dataunitList;
        for(int d = 0;d < dataunitList.length(); d++){
            if(d == 0){
                data = dataunitList.value(d).toLatin1();
            }
            else{
                data = data + intervalbyte + dataunitList.value(d).toLatin1();
            }
        }
        qDebug()<<QString("data filed %1:").arg(q)<<data;
        qDebug()<<QString("data HEX %1:").arg(q)<<data.toHex();
        dataUnit = dataUnit + STX + data + ETX;
    }
    QByteArray MessageBytes = SOH + versionByte
            + intervalbyte + sequenceNumByte
            + intervalbyte + messageTimeByte
            + intervalbyte + messageTypeByte
            + intervalbyte + equipmentIdByte
            + intervalbyte + locationOrStatusTrargetIdByte
            + ETX + dataUnit
            + EOT;
    emit sendMessage(MessageBytes);
}
