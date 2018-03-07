#ifndef AFFIX9CONFIRMWIND_H
#define AFFIX9CONFIRMWIND_H

#include <QWidget>
#include <QPainter>
#include <QPaintEvent>
#include <QMouseEvent>
#include <QPoint>
#include <QDebug>
#include <QMap>
#include <QComboBox>

typedef QString DataStr;
typedef QMap<int,DataStr> TMap;
typedef QMap<QString,QString> ValueCmmu;

typedef QString InforName;
typedef QString InforCtx;
typedef QMap<InforName,InforCtx> InforData;

class AFFIX9ConfirmWind : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(QStringList U36Id READ getU36Id WRITE setU36Id NOTIFY U36IdChanged)

public:
    explicit AFFIX9ConfirmWind(QWidget *parent = 0);
    QStringList getU36Id  ()const{
        return this->m_36ID;
    }

signals:
    void U36IdChanged();
    void closeCommuSet(QString Str);

protected:
    void paintEvent(QPaintEvent *e);
    void mousePressEvent(QMouseEvent *e);
    void mouseMoveEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);

public slots:
    void setU36Id(QStringList id);
    void setCommData(InforData data,QString index);
    void showDefultValue(QString str);

private slots:

private:
    QComboBox *B_Unit36;
    QComboBox *B_cards;
    QComboBox *B_Bate;
    QComboBox *B_Bits;
    QComboBox *B_CRC;
    QComboBox *B_StopBit;

    void initComboxcontrl();
    void setComboxItems();
    void setComboxGeometry();
    void setComboxStyleSheet();

    int s_width;
    int s_height;
    void initUIsize();

    bool leftClick;
    QPoint leftPos;
    void initleftClickValue();

    bool cancle;
    bool confirm;
    bool release;
    void initClickBoolValue();

    TMap title;
    void initTitleStr();

    ValueCmmu Bate;
    ValueCmmu Bits;
    ValueCmmu CRC;
    ValueCmmu StopBit;
    ValueCmmu m_Bate;
    ValueCmmu m_Bits;
    ValueCmmu m_CRC;
    ValueCmmu m_StopBit;
    void initCommunicateValue();

    QStringList m_36ID;
    void init36Id();

    QString getCommunicate();

    InforData m_CommuData;
};

#endif // AFFIX9CONFIRMWIND_H
