#ifndef HIDEPUSHBUTTON_H
#define HIDEPUSHBUTTON_H

#include <QWidget>
#include <QTimer>
#include <QMouseEvent>
#include <QPainter>
#include <QPaintEvent>
#include <QEvent>

//********
// used to move Main's Sub Controls location.
// this HidePushbutton widget is hide
// used to send signal with bool value when clicked this widget for three times.
//********
class HidePushbutton : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(bool signalFlag READ signalFlag WRITE setSignalFlag NOTIFY signalFlagChanged)

public:
    explicit HidePushbutton(QWidget *parent = 0);
    bool signalFlag() const { return m_updateFlag;}
    void setSignalFlag(bool update = false);

signals:
    void removeFilter(bool flag);// remove UI Filter event
    void signalFlagChanged();

protected:
    //点击事件3下
    void mousePressEvent(QMouseEvent *e);
    void paintEvent(QPaintEvent *event);
    bool event(QEvent *event);

private:
    QTimer *clearTimer;
    int count;
    bool flag;
    bool m_updateFlag;//保存信号发送出去携带的bool值

public slots:

private slots:
     void clear();
};

#endif // HIDEPUSHBUTTON_H
