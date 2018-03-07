#ifndef LogInforCtx_H
#define LogInforCtx_H

#include <QWidget>
#include <QPainter>
#include <QPaintEvent>
#include <QMouseEvent>
#include <QDebug>
#include <QLineEdit>
typedef QMap<int,QString> InforMap;

class LogInforCtx : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(int subWidth READ getSubWidth WRITE setSubWidth NOTIFY subWidthChanged)
    Q_PROPERTY(int subHeight READ getSubHeight WRITE setSubHeight NOTIFY subHeightChanged)
    Q_PROPERTY(InforMap dataMap READ getDataMap WRITE setDataMap NOTIFY dataMapChanged)

public:
    explicit LogInforCtx(QWidget *parent = 0);
    int getSubWidth() const { return m_width; }
    int getSubHeight() const { return m_height; }
    InforMap getDataMap() const { return m_DataMap; }
    int returnDataIndex() const { return m_index; }
    void _set_data_cell_width(int w);

protected:
    void paintEvent(QPaintEvent *e);
    void mousePressEvent(QMouseEvent *e);
    void mouseDoubleClickEvent(QMouseEvent *e);

signals:
    void subWidthChanged();
    void subHeightChanged();
    void dataMapChanged();
    void doubleClickSignal(int index);

public slots:
    void setSubWidth(int value);
    void setSubHeight(int value);
    void setDataMap(InforMap data);

private slots:

private:
    int m_width;
    int m_height;
    void initValues();

    InforMap m_DataMap;
    int m_num;
    void initNumValue();

    //标记选中背景索引
    int m_index;
    void initIndexValue();

    int m_cell_w;
    void _init_cell_width();
};

#endif // LogInforCtx_H













