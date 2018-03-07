#ifndef DEALCENTER3616_H
#define DEALCENTER3616_H


#include "UI3616/ui_power.h"
#include "UI3616/ui_sensorcard.h"
#include "UI3616/ui_network.h"

#include <QWidget>
#include <QPainter>
#include <QPaintEvent>
#include <QMap>
typedef QString Descrpit;
typedef QMap<Descrpit,Ui_powerCard *>   powerMAP;
typedef QMap<Descrpit,Ui_sensorCard *>  sensorMAP;
typedef QMap<Descrpit,Ui_NetworkCard *> networkMAP;

class DealCenter3616 : public QWidget
{
    Q_OBJECT
public:
    explicit DealCenter3616(QWidget *parent = 0);

protected:
    void paintEvent(QPaintEvent *event);

signals:

public slots:

private:
    powerMAP   powerList;
    sensorMAP  sensorList;
    networkMAP networkList;

    void init_subui_obj();
    void init_subui_geomerty();

    int m_width;
    int m_heigh;
    void m_init_size();
};

#endif // DEALCENTER3616_H
