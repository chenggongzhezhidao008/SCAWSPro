#ifndef TEMPSENSORSHOW_H
#define TEMPSENSORSHOW_H

#include <QWidget>
#include <QPainter>
#include <QMouseEvent>
#include <QDebug>

class TempSensorShow : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(int sensorId READ sensorId WRITE setSensorId NOTIFY sensorIdChanged)
    Q_PROPERTY(int flag READ flag WRITE setFlag NOTIFY flagChanged)
    Q_PROPERTY(float tempValue READ tempValue WRITE setTempValue NOTIFY tempValueChanged)
    Q_PROPERTY(float waringValue READ waringValue WRITE setWaringValue NOTIFY waringValueChanged)
    Q_PROPERTY(QString dayNight READ dayNight WRITE setDayNight NOTIFY dayNightChanged)
    Q_PROPERTY(float lastTemperatureValue READ lastTemperatureValue WRITE setLastTemperatureValue NOTIFY lastTemperatureValueChanged)

public:
    explicit TempSensorShow(QWidget *parent = 0);
    //UI控件标识
    int flag() const { return m_flag;}
    void setFlag(int flag);

    int sensorId() const { return m_id;}
    void setSensorId(int id);

    float tempValue() const { return m_temp;}
    float waringValue() const { return m_waring;}
    QString dayNight() const {return m_dayNight;}

    void setTempValue(float temp);
    void setWaringValue(float waring);
    void setDayNight(QString model);

    float lastTemperatureValue() const { return m_lastTemperature;}
    void  setLastTemperatureValue(float temperature);

signals:
    void flagChanged();
    void sensorIdChanged();
    void tempValueChanged();
    void waringValueChanged();
    void dayNightChanged();
    void lastTemperatureValueChanged();

protected:
    void paintEvent(QPaintEvent *event);
    void drawBackground(QPainter *painter);
    void drawScale(QPainter *painter);
    void drawScaleLine(QPainter *painter);
    void drawPlusOrMinus(QPainter *painter);
    void drawScaleValue(QPainter *painter);

    //以下三个事件使风表盘界面可移动
    void mousePressEvent(QMouseEvent *e);
    void mouseMoveEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);

private:
//    QPainter *painter;
    int m_flag;//UI控件id
    int m_id;
    float m_temp;
    float m_waring;
    float m_lastTemperature;
    QString m_dayNight;

    //刻度值
    qreal scale;

    QPoint point;//保存鼠标按下的点全局位置坐标与局部坐标的差向量
    bool mousePressed;//保存鼠标按下状态

};

#endif // TEMPSENSORSHOW_H
