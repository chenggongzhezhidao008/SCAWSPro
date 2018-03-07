#ifndef SUBRUNCFG_H
#define SUBRUNCFG_H

#include <QWidget>
#include <QPainter>
#include <QPaintEvent>

class SubRunCFG : public QWidget
{
    Q_OBJECT
public:
    explicit SubRunCFG(QWidget *parent = 0);

protected:
    void paintEvent(QPaintEvent *e);

signals:

public slots:

};

#endif // SUBRUNCFG_H
