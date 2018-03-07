#ifndef ATCMAINACK_H
#define ATCMAINACK_H

#include <QWidget>
#include <QPaintEvent>
#include <QPainter>
#include <QMouseEvent>
#include <QDebug>

class atcMainACK : public QWidget
{
    Q_OBJECT
public:
    explicit atcMainACK(QWidget *parent = 0);

protected:
    void paintEvent(QPaintEvent *e);
    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);

signals:

public slots:

private:
    bool m_releaseBool;
    void iniReleaseBoolValue();

    bool ackClickBool;
    void initAckvalue();
};

#endif // ATCMAINACK_H
