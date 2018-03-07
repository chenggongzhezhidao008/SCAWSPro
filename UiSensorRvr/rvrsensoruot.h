#ifndef RVRSENSORUOT_H
#define RVRSENSORUOT_H

#include <QWidget>
#include <QPainter>
#include <QMouseEvent>
#include <QTimer>
#include <QMouseEvent>
#include <QDebug>


class RvrSensorUot : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(int sensorId READ sensorId WRITE setSensorId NOTIFY sensorIdChanged)
    Q_PROPERTY(int fontSize READ fontSize WRITE setFontSize NOTIFY fontSizeChanged)
    Q_PROPERTY(int flag READ flag WRITE setFlag NOTIFY flagChanged)
    Q_PROPERTY(QString showContext READ showContext WRITE setShowContext NOTIFY showContextChanged)
    Q_PROPERTY(bool Waring READ Waring WRITE setWaring NOTIFY WaringChanged)
    Q_PROPERTY(bool enable READ enable WRITE setEnable NOTIFY enableChanged)
    Q_PROPERTY(QString dataName READ dataName WRITE setDataName NOTIFY dataNameChanged)
    Q_PROPERTY(QString unitString READ unitString WRITE setUnitString NOTIFY unitStringChanged)
    Q_PROPERTY(QString timestring READ timestring WRITE setTimestring NOTIFY timestringChanged)
    Q_PROPERTY(QString daynight READ daynight WRITE setDaynight NOTIFY daynightChanged)

    Q_PROPERTY(int timeSize READ getTimeSize WRITE setTimeSize NOTIFY TimeSizeChanged)
    Q_PROPERTY(int dataNameSize READ getdataNameSize WRITE setDataNameSize NOTIFY dataNameSizeChanged)

public:
    explicit RvrSensorUot(QWidget *parent = 0);
    int sensorId() const { return m_id;}
    void setSensorId(int id);

    //设置字体的大小
    int fontSize() const { return m_fontSize;}
    void setFontSize(int size);

    //UI控件标识
    int flag() const { return m_flag;}
    void setFlag(int flag);

    //设置使能控件
    bool enable() const {return this->m_enable;}
    void setEnable(bool able);

    //显示的数据名称
    QString dataName() const { return m_dataName;}
    void  setDataName(QString name);


    //读写颜色告警
    bool Waring() const { return this->m_Waring; }
    void setWaring(bool waringFalge);

    //读写文本内容
    QString showContext() const { return this->m_Text;}
    void setShowContext(QString text);

    //设置日夜模式
    QString daynight()  const { return this->daynightflag;}
    void setDaynight(QString flag);

    //设置单位
    QString unitString() const { return this->m_unit;}
    void setUnitString(QString unit);

    //设置时间
    QString timestring() const { return this->m_time;}
    void setTimestring(QString time);

    int getTimeSize() const { return this->m_timeSize;}
    void setTimeSize(int size);

    int getdataNameSize() const { return this->m_dataNameSize;}
    void setDataNameSize(int size);

    void initSize();//初始化尺寸

signals:
    void flagChanged();
    void fontSizeChanged();
    void sensorIdChanged();
    void WaringChanged();
    void showContextChanged();
    void daynightChanged();
    void unitStringChanged();
    void timestringChanged();
    void dataNameChanged();
    void enableChanged();
    void TimeSizeChanged();
    void dataNameSizeChanged();

public slots:

private slots:
    void waringContrl();

private:
    int m_flag;//UI控件id
    int m_id;//传感器id
    int m_fontSize;//字体大小

    //保存label输出框的宽高最小值。
    int m_width;
    int m_high;
    bool m_Waring;//光告警
    QString m_Text;
    QString daynightflag;//保存日夜模式

    //使能控件
    bool m_enable;

    //显示的数据名称
    QString m_dataName;

    //告警控制
    QTimer *waringTimer;

    //单位 和 时间字符串
    QString m_unit;
    QString m_time;

    QPoint point;//保存鼠标按下的点全局位置坐标与局部坐标的差向量
    bool mousePressed;//保存鼠标按下状态

    int m_timeSize;
    int m_dataNameSize;

protected:
    void paintEvent(QPaintEvent *event);//绘制事件
    void drawWaring(QPainter *painter);
    void drawRVRArea(QPainter *painter);
    void drawRVRContext(QPainter *painter);//绘制rvr显示区域里面的文字内容
    void drawRVRValue(QPainter *painter); //绘制RVR数据值

    //以下三个事件使风表盘界面可移动
    void mousePressEvent(QMouseEvent *e);
    void mouseMoveEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);
};

#endif // RVRSENSORUOT_H
