#ifndef USERWARING_H
#define USERWARING_H

#include <QWidget>
#include <QPainter>
#include <QPaintEvent>

class UserWaring : public QWidget
{
    Q_OBJECT
public:
    explicit UserWaring(QWidget *parent = 0);
    
protected:
    void paintEvent(QPaintEvent *event);

signals:

public slots:

};

#endif // USERWARING_H
