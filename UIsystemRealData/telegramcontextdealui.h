#ifndef TELEGRAMCONTEXTDEALUI_H
#define TELEGRAMCONTEXTDEALUI_H

#include <QWidget>
#include <QPainter>
#include <QPaintEvent>
#include <QTextEdit>
#include <QString>
#include <QStringList>
#include <QMouseEvent>
#include <QDebug>
typedef QMap <int,QString> SerialWarMap;

class TelegramContextDealUI : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(QString telegramName READ getTelegramName WRITE setTelegramName NOTIFY telegramNameChanged)
    Q_PROPERTY(QString telegramContextStr READ getTelegramContextStr WRITE setTelegramContextStr NOTIFY telegramContextStrChanged)
    Q_PROPERTY(QStringList MetarWaringList READ getMetarWaringList WRITE setMetarWaringList NOTIFY MetarWaringListChanged)
    Q_PROPERTY(QStringList SpacaiWaringList READ getSpacaiWaringList WRITE setSpacaiWaringList NOTIFY SpacaiWaringListChanged)

public:
    explicit TelegramContextDealUI(QWidget *parent = 0);
    QString getTelegramName() const { return this->m_contextNameStr; }
    QString getTelegramContextStr() const { return this->m_telegramCtx;}
    QStringList getMetarWaringList() const { return this->m_MetarWaringList;}
    QStringList getSpacaiWaringList() const { return this->m_SapciWaringList;}

protected:
    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);

    void paintEvent(QPaintEvent *event);

signals:
    void telegramNameChanged();
    void telegramContextStrChanged();
    void MetarWaringListChanged();
    void SpacaiWaringListChanged();

    void queryUpdateTelegramCotext();
    void sendTelegramContext(QString telegramContext);

public slots:
    void setTelegramName(QString telegramName);
    void setTelegramContextStr(QString telegramStr);
    void setMetarWaringList(QStringList waringList);
    void setSpacaiWaringList(QStringList waringList);
    void setAllContrlGeometry();

private slots:
    void updateTelegram();
    void comfirmTelegram();
    QString removeFeild(QString str);
    QString constituteMetarContext(SerialWarMap serialMap);
    void sendTelegram();
    void metarComfirm();
    void spacComfirm();

private:
    QString m_contextNameStr;

    QTextEdit *m_telegramContext;
    QTextEdit *Met_metarWaringInform;
    QTextEdit *Met_spacilWaringInform;

    void initAllContrls();
    void setAllContrlsReadOnly();

    QString m_telegramCtx;
    QStringList m_MetarWaringList;
    QStringList m_SapciWaringList;

    void setAllContrlsValue();

    // event bool

    bool m_Update;
    bool m_Comfirm;
    bool m_send;
    bool m_metComfirm;
    bool m_spacComfirm;
    bool releaseDo;

    bool met_modifytTelegramFlag;

    bool sizeFirstUpdate;// 第一次更新
};

#endif // TELEGRAMCONTEXTDEALUI_H
