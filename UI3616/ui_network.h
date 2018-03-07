#ifndef Ui_NetworkCard_H
#define Ui_NetworkCard_H

#include <QWidget>
#include <QPainter>
#include <QPaintEvent>


class Ui_NetworkCard : public QWidget
{
    Q_OBJECT
public:
    explicit Ui_NetworkCard(QWidget *parent = 0);
protected:
    void paintEvent(QPaintEvent *event);

signals:

public slots:

};

#endif // Ui_NetworkCard_H
