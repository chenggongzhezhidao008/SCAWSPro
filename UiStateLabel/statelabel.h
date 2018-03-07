#ifndef STATELABEL_H
#define STATELABEL_H

#include <QWidget>
#include <QPaintEvent>
#include <QPainter>

class StateLabel : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(int sensorId READ sensorId WRITE setSensorId NOTIFY sensorIdChanged)
    Q_PROPERTY(int comId READ comId WRITE setComId NOTIFY comIdChanged)
    Q_PROPERTY(QString comName READ comName WRITE setComName NOTIFY comNameChanged)
    Q_PROPERTY(QString state READ state WRITE setState NOTIFY stateChanged)
    Q_PROPERTY(int  fontSize READ fontSize WRITE setFontSize NOTIFY fontSizeChanged)
//    Q_PROPERTY(QString data READ data WRITE setData NOTIFY dataChanged)
//    Q_PROPERTY(QString dataColor READ dataColor WRITE setDataColor NOTIFY dataColorChanged)

public:
    explicit StateLabel(QWidget *parent = 0);

    //控件所属传感器id
    int sensorId() const { return m_sensorId; }
    void setSensorId(int senId);

    //控件id
    int comId() const { return m_comId; }
    void setComId(int comId);

    //控件名称
    QString comName() const { return m_comName ; }
    void setComName(QString comName);

    //状态
    QString state() const { return this->m_state; }
    void setState( QString state);

    //字体
    int fontSize() const { return this->m_fontSize; }
    void setFontSize(int size);

    //数据label
//    QString data() const { return this->m_data; }
//    void setData(QString data);

//    //数据颜色
//    QString dataColor() const { return this->m_dataColor; }
//    void setDataColor(QString colorHexStr);

signals:
    void sensorIdChanged();
    void comIdChanged();
    void comNameChanged();
    void stateChanged();
    void fontSizeChanged();
//    void dataChanged();
//    void dataColorChanged();

private:
//    QPainter *painter;
    int m_sensorId;
    int m_comId;
    QString m_comName;
    QString m_state;
    int m_fontSize;
//    QString m_data;
//    QString m_dataColor;

protected:
    void paintEvent(QPaintEvent *event);
};

#endif // STATELABEL_H
