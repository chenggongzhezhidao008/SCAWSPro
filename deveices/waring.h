#ifndef WARINGSHOW_H
#define WARINGSHOW_H

#include "systemWaring/waringlog.h"
#include <QWidget>
#include <QPainter>
#include <QPaintEvent>
#include <QMap>
#include <QDebug>

typedef QString InforName;
typedef QString InforCtx;
typedef QMap<InforName,InforCtx> InforData;

class WaringShow : public QWidget
{
    Q_OBJECT

public:
    explicit WaringShow(QWidget *parent = 0);


protected:
    void paintEvent(QPaintEvent *e);

public slots:
    void AFFIX9NewMessageSendUp(QString dCtx,InforData data);

signals:


private:
    InforData m_basiLight;
    QString m_grade,m_adValue;
    void initValue();
    QStringList findAppointKeyValues(InforData dataPart, QString key);

    WaringLogShow *warShow;
    void m_init_waring_show();
    void m_init_waring_geomerty();

    int m_width;
    int m_height;
    void m_init_size();
};

#endif // WARINGSHOW_H
