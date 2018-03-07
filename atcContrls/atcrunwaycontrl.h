#ifndef ATCRUNWAYCONTRL_H
#define ATCRUNWAYCONTRL_H

#include <QWidget>
#include <QPainter>
#include <QPaintEvent>

class AtcRunWayContrl : public QWidget
{
    Q_OBJECT
public:
    explicit AtcRunWayContrl(QWidget *parent = 0);

protected:
    void paintEvent(QPaintEvent *event);

signals:


public slots:


private:

};

#endif // ATCRUNWAYCONTRL_H
