#ifndef AWOSMAINFRAM_H
#define AWOSMAINFRAM_H

#include <QWidget>
#include <QListWidget>
#include <QMouseEvent>
#include <QPoint>
#include <QDebug> //调试

#include <QStateMachine>
#include <QState>
#include <QSignalTransition>
#include <QPropertyAnimation>

//==========****
#include <QPainter>
#include <QPaintEvent>


typedef QMap<QString,QString> DataMap;
typedef QMap<QString,DataMap> SensorMap;

namespace Ui {
class AwosMainFram;
}

class AwosMainFram : public QWidget
{
    Q_OBJECT

public:
    explicit AwosMainFram(QWidget *parent = 0);
    ~AwosMainFram();
    void setAwosSize(int width,int height);//设置界面大小尺寸
    void initUpdateUIButton();

public slots:
    void windStatus(SensorMap senMap); //风的状态
    void humiTempStatus(SensorMap senMap); //温湿度状态
    void rvrStatus(SensorMap senMap); //能见度和跑到视程状态
    void cloudStatus(SensorMap senMap); //云状态
    void atmospherePressStatus(SensorMap senMap); //大气压状态
    void rainStatus(SensorMap senMap); //降雨量状态
    void phenomenaWeatherStatus(SensorMap senMap); //（PW）天气现象状态
    void prevailingVisibilityStatus(SensorMap senMap);//(PV)主导能见度状态
    void manualInputDataStatus(SensorMap senMap);//人工输入数据

    void humiTempData(SensorMap senMap); //温湿度數值
    //==============*****
    //状态部分数据
    void windState(bool connect);
    void humiTempState(bool connect);
    void rvrState(bool connect);
    void cloudState(bool connect);
    void atmospherePressState(bool connect);
    void rainState(bool connect);
    void phenomenaWeatherState(bool connect);
    void prevailingVisibilityState(bool connect);

protected:
    //以下三个事件使Awos界面可移动
    void mousePressEvent(QMouseEvent *e);
    void mouseMoveEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);
    bool eventFilter(QObject *obj, QEvent *event);//过滤掉不要的一些事件
    void paintEvent(QPaintEvent *event);//做界面眉

signals:
    void editSubUi(bool edit);
    //test
    void yes(bool ok);

private slots:
    void on_pushButton_clicked();
    //test
private:
    Ui::AwosMainFram *ui;
    QPoint point;//保存鼠标按下的点全局位置坐标与局部坐标的差向量
    bool mousePressed;//保存鼠标按下状态

};

#endif // AWOSMAINFRAM_H
