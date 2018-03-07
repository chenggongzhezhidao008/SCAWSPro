#ifndef TELEGRAMCFG_H
#define TELEGRAMCFG_H

#include <QWidget>
#include <QPaintEvent>
#include <QPainter>
#include <QLineEdit>
#include <QComboBox>
#include <QDebug>
#include <QMap>
#include <QQueue>

typedef QMap <int,QString> SerialWarMap;
typedef QQueue<QString> MeaagseQueue;
typedef QMap <int,QString> TelgramForm;

class TelegramCFG : public QWidget
{
    Q_OBJECT

public:
    explicit TelegramCFG(QWidget *parent = 0);

protected:
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);

    void initAFTNParavmeter();
    void setAFTNParavmeter();

    bool eventFilter(QObject *obj, QEvent *event);

signals:
     void AFTNConfigSet(MeaagseQueue queue);

public slots:

private slots:
    void editAFTNValues();
    void separatorSlot(QString str);
    void flowSequenceSlot(QString str);
    void sendHeadSlot(QString str);
    void sendRaerSlot(QString str);
    void receiveHeadSlot(QString str);
    void receiveRaerSlot(QString str);
    void AFTNTelegramSlot(QString str);

private:
    SerialWarMap AFTNInitValues;

    TelgramForm flowSequenceMap;
    TelgramForm separatorMap;
    TelgramForm sendHeadMap;
    TelgramForm sendRaerMap;
    TelgramForm receiveHeadMap;
    TelgramForm receiveRaerMap;
    TelgramForm AFTNTelegramMap;
    void initaAllFormValues();

    QLineEdit *AFTNAddress;
    QLineEdit *cresrt;
    QLineEdit *signalChannel;
    QLineEdit *remoteAddress;
    void initLineEditContrls();
    void setGeometryEditContrls();
    void setEditContrlsShow(bool show);
    void setEditContrlsInitValue();
    void setEditContrlsBackgroundColor();
    void initEditContrlsEditFinishSignalsConnectons();
    void installEditsEventFilter();

    QComboBox *flowSequence;
    QComboBox *separator;
    QComboBox *sendHead;
    QComboBox *sendRaer;
    QComboBox *receiveHead;
    QComboBox *receiveRaer;
    QComboBox *AFTNTelegram;
    void initComBoxContrls();
    void setComBoxGeometry();
    void setComBoxInitValues();
    void setComBoxBackGroundColor();
    void initComBoxCurrentSignalConnections();
    void installComBoxEventFilter();

    void updateAFTNValues();
    bool m_metarSetConfirm;
    bool m_metarSetCancel;
    bool releaseDo;
    void initButtonBool();

    int wSize;
    int hSize;
    void initSize();

};

#endif // TELEGRAMCFG_H
