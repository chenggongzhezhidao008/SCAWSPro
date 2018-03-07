#ifndef TELEGRAMPOP_H
#define TELEGRAMPOP_H

#include <QWidget>
#include <QLineEdit>
#include <QLabel>
#include <QPainter>
#include <QPaintEvent>

#include <QVector>
typedef QVector<QLineEdit*>  TelegramUpdate;

#include <QMap>
#include <QString>
#include <QTextEdit>

typedef QMap<int,QString> TelegramCtx;
typedef QMap<int,QString> TelegramLabelList;

class TelegramPop : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(TelegramCtx ctxMap READ getCtxMap WRITE setCtxMap NOTIFY ctxMapChanged)

public:
    explicit TelegramPop(QWidget *parent = 0);
    TelegramCtx getCtxMap() const { return m_ctx;}

public slots:
    void setCtxMap(TelegramCtx ctx);

protected:
    void paintEvent(QPaintEvent *event);

    void mousePressEvent(QMouseEvent *e);

    void mouseReleaseEvent(QMouseEvent *e);

signals:
    void ctxMapChanged();

    void popTelegramSendSignal(TelegramCtx Ctx);

private slots:
    void updateSize();

    void modifypopTelegram();

    void sendpopTelegram();

    void dealChangCtx();

private:
    bool m_sendTelegram;
    bool m_updateTelegram;

    bool m_releaseDo;

    // Vecter
    TelegramUpdate telegramNameUpdateList;
    TelegramUpdate telegramContextList;

    // Data
    TelegramCtx m_telegramCtx;
    TelegramLabelList m_NameList;
    void initNameList();

    int widthSize,heightSize;

    QTextEdit *ContextEdit;

    void initCotextEdit();
    bool updateBool;

    QString removeFeild(QString str);
    void updateTelegramContextStr();

    TelegramCtx m_ctx;
};

#endif // TELEGRAMPOP_H
