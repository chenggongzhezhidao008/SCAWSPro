#ifndef HUMIDSENSOROUT_H
#define HUMIDSENSOROUT_H

#include <QWidget>
#include <QPainter>
#include <QMouseEvent>
#include <QDebug>

class HumidSensorOut : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(int sensorId READ sensorId WRITE setSensorId NOTIFY sensorIdChanged)
    Q_PROPERTY(int flag READ flag WRITE setFlag NOTIFY flagChanged)
    Q_PROPERTY(float humidity READ humidity WRITE setHumidity NOTIFY humidityChanged)
    Q_PROPERTY(float waring READ waring WRITE setWaring NOTIFY waringChanged)
    Q_PROPERTY(QString dayNigth READ dayNigth WRITE setDayNigth NOTIFY dayNigthChanged)
    Q_PROPERTY(float lastHumidityValue READ lastHumidityValue WRITE setLastHumidityValue NOTIFY lastHumidityValueChanged)

public:
    explicit HumidSensorOut(QWidget *parent = 0);
    void initHumidityUI();//初始化湿度界面

    //最近的一次湿度数据取值
    float lastHumidityValue() const { return m_lastHumidity;}
    void setLastHumidityValue(float humidity);

    //UI控件标识
    int flag() const { return m_flag;}
    void setFlag(int flag);

    int sensorId() const { return m_id;}
    void setSensorId(int id);

    float humidity() const { return this->m_humidityValue;}
    void setHumidity(float humidity);//湿度

    float waring() const { return this->m_waringValue; }
    void setWaring(float waring);//告警

    QString dayNigth() const { return this->m_dayNightModel;}
    void setDayNigth(QString model);//白天黑夜模式


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

signals:
    void flagChanged();
    void sensorIdChanged();
    void humidityChanged();
    void waringChanged();
    void dayNigthChanged();
    void lastHumidityValueChanged();

public slots:

private:
    int m_flag;//UI控件id
    int m_id;
    int m_humidUIWidth;
    int m_humidUIHeight;
    float m_lastHumidity;
    float m_humidityValue;
    float m_waringValue;
    QString m_dayNightModel;

    QPoint point;//保存鼠标按下的点全局位置坐标与局部坐标的差向量
    bool mousePressed;//保存鼠标按下状态
};

#endif // HUMIDSENSOROUT_H
