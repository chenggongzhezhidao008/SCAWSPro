#ifndef ATCROSECONTRL_H
#define ATCROSECONTRL_H

#include <QWidget>
#include <QPainter>
#include <QPaintEvent>

class ATCRoseContrl : public QWidget
{
    Q_OBJECT
public:
    explicit ATCRoseContrl(QWidget *parent = 0);

protected:
    void paintEvent(QPaintEvent *event);

signals:

public slots:

private:

};

#endif // ATCROSECONTRL_H
