#ifndef UI_SENSORCARD_H
#define UI_SENSORCARD_H

#include <QWidget>
#include <QPainter>
#include <QPaintEvent>

class Ui_sensorCard : public QWidget
{
    Q_OBJECT
public:
    explicit Ui_sensorCard(QWidget *parent = 0);

protected:
    void paintEvent(QPaintEvent *event);

signals:

public slots:

};

#endif // UI_SENSORCARD_H
