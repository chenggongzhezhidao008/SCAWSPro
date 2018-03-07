#ifndef Ui_powerCard_H
#define Ui_powerCard_H

#include <QWidget>
#include <QPainter>
#include <QPaintEvent>
#include <QLinearGradient>
#include <QPoint>

class Ui_powerCard : public QWidget
{
    Q_OBJECT
public:
    explicit Ui_powerCard(QWidget *parent = 0);

protected:
    void paintEvent(QPaintEvent *event);

signals:

public slots:

};

#endif // Ui_powerCard_H
