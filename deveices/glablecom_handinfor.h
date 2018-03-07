#ifndef GLABLECOM_HANDINFOR_H
#define GLABLECOM_HANDINFOR_H

#include <QWidget>
#include <QPainter>
#include <QPaintEvent>
#include <QMouseEvent>
#include <QDebug>
#include <QLineEdit>
#include <QVector>
#include <QAction>
#include <QMenu>
#include <QAction>

typedef QMap<int,QString> InforMap;
typedef QVector<QAction *> ActionS;

class glableHandInfor : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(int subWidth READ getSubWidth WRITE setSubWidth NOTIFY subWidthChanged)
    Q_PROPERTY(int subHeight READ getSubHeight WRITE setSubHeight NOTIFY subHeightChanged)
    Q_PROPERTY(InforMap dataMap READ getDataMap WRITE setDataMap NOTIFY dataMapChanged)
    Q_PROPERTY(QStringList actionName READ getActionName WRITE setActionName NOTIFY actionNameChanged)

public:
    explicit glableHandInfor(QWidget *parent = 0);
    int getSubWidth() const { return m_width; }
    int getSubHeight() const { return m_height; }
    InforMap getDataMap() const { return m_DataMap; }
    int returnDataIndex() const { return m_index; }
    QStringList getActionName() const { return m_namelist;}
    void _set_data_cell_width(int w);

protected:
    void paintEvent(QPaintEvent *e);
    void mousePressEvent(QMouseEvent *e);

signals:
    void subWidthChanged();
    void subHeightChanged();
    void dataMapChanged();
    void actionNameChanged();
    void menuOption(QString option);

public slots:
    void setSubWidth(int value);
    void setSubHeight(int value);
    void setDataMap(InforMap data);
    void setActionName(QStringList actionName);

private slots:
    void menuOptionSlot();

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
    void initsetcontextMenupolicy();
    QMenu *menu;
    void initCustomMenus();
    QStringList m_namelist;
    ActionS actionList;
    void createActionContrls();

    int m_cell_w;
    void _init_cell_width();
};

#endif // GLABLECOM_HANDINFOR_H













