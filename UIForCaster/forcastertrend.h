#ifndef FORCASTERTREND_H
#define FORCASTERTREND_H

#include <QWidget>
#include <QComboBox>
#include <QLineEdit>
#include <QPushButton>
#include "UIForCaster/trendUI.h"

class ForCasterTrend : public QWidget
{
    Q_OBJECT
public:
    explicit ForCasterTrend(QWidget *parent = 0);

protected:
    void paintEvent(QPaintEvent *e);

signals:
    void sendMetarTrend(QString trend);// 发送趋势报部分电报内容信号

public slots:
    void setNoTrendMetarCtx(QString Str); // 显示未加趋势报的Metar报

private slots:
    void auto_updateCtxSlot(QString str);
    void updateCtxSlot();
    void sendTrendSlot();

private:
    TrendUI *trend;
    void  inittren();
    void  updateSize();
    int x,y;
    void  initXY();

    QStringList list;
    QComboBox  *selectBox;
    void initBoxOption();

    QLineEdit *trendEidt;
    void initTrend();

    QPushButton *update;
    QPushButton *send;
    void initButton();

    QString m_ctx;
};

#endif // FORCASTERTREND_H
