#ifndef TREND_H
#define TREND_H

#include <QWidget>
#include <QTime>
#include <QMap>
#include <QString>
#include <QStringList>
#include <QLineEdit>
#include <QPainter>
#include <QPaintEvent>
#include <QComboBox>
#include <QDebug>
#include <QMessageBox>

typedef QString realDataName;
typedef QString realDataValue;
typedef QMap <realDataName,realDataValue> realDataMap;
typedef QMap <int,QString> SerialWarMap;
typedef QMap <QString,QString> telegramCFG;

class TrendUI : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(QTime updateTime READ getUpdateTime WRITE setUpdateTime NOTIFY updateTimeChanged)
    Q_PROPERTY(QString toSendTelegramHaveTime READ getToSendTelegramHaveTime WRITE setToSendTelegramHaveTime NOTIFY toSendTelegramHaveTimeChanged)

public:
    explicit TrendUI(QWidget *parent = 0);
    QTime getUpdateTime() const { return this->m_updateTime; }
    QString getToSendTelegramHaveTime() const { return this->m_haveTime; }

protected:
    void paintEvent(QPaintEvent *event);
    void setAllContrlsGeometry();

signals:
    void updateTimeChanged();
    void toSendTelegramHaveTimeChanged();

public slots:
    void setUpdateTime(QTime updateTime);
    void setToSendTelegramHaveTime(QString toSendTelegramHaveTime);
    void setMetarCtx(QString Str);
    void setTrendCtx(QString ctx);
    // 请求编报内容
    telegramCFG getTelegramCtx();

private:
    QTime m_updateTime;
    QString m_haveTime;

    SerialWarMap telegramLabelName;
    void initTelegramnLable();

    QLineEdit *headEdit;
    QLineEdit *windEdit;
    QLineEdit *visEdit;
    QLineEdit *RVREdit;
    QLineEdit *weatherEdit;
    QLineEdit *cloudHightEdit;
    QLineEdit *tempHumEdit;
    QLineEdit *pressEdit;
    QLineEdit *closeWeatherEdit;
    QLineEdit *MOTNEEdit;
    QLineEdit *TRENDEdit;
    QLineEdit *RemarkEdit;

    void newAllSubContrls();
    void setAllContrlsOnliyRead();
    void setMetarCodec();

    // init start telegram Sub Value
    telegramCFG m_MetarCodec;
    void initTeleStartCtx();
};

#endif // TELEGRAMSUBDATAMODIFITYCONTRL_H
