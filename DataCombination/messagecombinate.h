#ifndef MESSAGECOMBINATE_H
#define MESSAGECOMBINATE_H

#include <QObject>

class MessageCombinate : public QObject
{
    Q_OBJECT
public:
    explicit MessageCombinate(QObject *parent = 0);

private:
     void headCombination();//消息头域组装

signals:

public slots:

};

#endif // MESSAGECOMBINATE_H
