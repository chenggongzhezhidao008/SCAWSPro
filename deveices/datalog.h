#ifndef DATALOG_H
#define DATALOG_H

#include <QWidget>
#include <QPainter>
#include <QPaintEvent>
#include <QMap>
#include <QDebug>
#include "systemLog/logshow.h"


class DataLog : public QWidget
{
    Q_OBJECT

public:
    explicit DataLog(QWidget *parent = 0);

protected:
    void paintEvent(QPaintEvent *e);

public slots:
    void add_log_record(QString logCtx,QString optioner);

signals:


private:
    LogShow *_m_log;
    void _m_init_log();
    void _m_set_log_geometry();

    int _m_width;
    int _m_height;
    void _m_init_LogSize();

};
#endif // DATALOG_H
