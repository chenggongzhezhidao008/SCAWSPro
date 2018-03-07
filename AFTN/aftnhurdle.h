#ifndef AFTNHURDLE_H
#define AFTNHURDLE_H

#include <QWidget>
#include <QPainter>
#include <QPaintEvent>
#include <QTextEdit>
#include <QMouseEvent>

class AFTNHurdle : public QWidget
{
    Q_OBJECT
public:
    explicit AFTNHurdle(QWidget *parent = 0);

protected:
    void paintEvent(QPaintEvent *e);
    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);

signals:

public slots:

private:
    QTextEdit *telegramOptionHint;
    QTextEdit *AFTNInformation;
    void initShowContrl();
    void initShowContrlOnliyRead();
    void initShowcontrlSetstyle();
    void setShowContrlGeomerty();

    int contrlWidth;
    int contrlHeight;
    void initContrlSize();

    bool ackClickBool;
    bool sendClickAgainBool;
    bool comfiredBool;
    bool sendedBool;
    bool setupSendFunctionBool;
    void initMinButtonBoolValue();

    bool releaseBool;
    void initReleaseBool();

};

#endif // AFTNHURDLE_H
